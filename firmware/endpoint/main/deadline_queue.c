#include "deadline_queue.h"

cldt_status_t cldt_deadline_queue_init(
    cldt_deadline_queue_t *queue,
    uint16_t capacity)
{
    if (queue == NULL || capacity == 0 || capacity > CLDT_ENDPOINT_MAX_POOL_SLOTS) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    queue->capacity = capacity;
    queue->queued = 0;
    queue->high_water = 0;
    queue->rejected = 0;
    queue->expired = 0;
    queue->coalesced = 0;
    queue->pool_exhaustions = 0;

    for (uint16_t i = 0; i < CLDT_ENDPOINT_MAX_POOL_SLOTS; i++) {
        queue->slots[i].state = CLDT_SLOT_FREE;
        queue->order[i] = 0;
    }

    return CLDT_OK;
}

cldt_status_t cldt_deadline_queue_acquire(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t **slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    for (uint16_t i = 0; i < queue->capacity; i++) {
        if (queue->slots[i].state == CLDT_SLOT_FREE) {
            queue->slots[i].state = CLDT_SLOT_PRODUCER_OWNED;
            *slot = &queue->slots[i];
            return CLDT_OK;
        }
    }

    queue->pool_exhaustions++;
    *slot = NULL;
    return CLDT_ERR_NO_SPACE;
}

cldt_status_t cldt_deadline_queue_commit(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot,
    uint64_t now_local_us)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    if (slot->state != CLDT_SLOT_PRODUCER_OWNED) {
        return CLDT_ERR_WRONG_STATE;
    }

    if (slot->meta.deadline_local_us <= now_local_us) {
        queue->rejected++;
        slot->state = CLDT_SLOT_FREE;
        return CLDT_ERR_EXPIRED;
    }

    // TODO: Reserve capacity by traffic class
    // TODO: Coalesce logic with existing queued messages
    // TODO: Telemetry deduplication

    if (queue->queued >= queue->capacity) {
        queue->rejected++;
        slot->state = CLDT_SLOT_FREE;
        return CLDT_ERR_NO_SPACE;
    }

    uint16_t slot_idx = slot - queue->slots;
    uint16_t insert_idx = queue->queued;

    // Binary search for deadline_local_us to find insertion point (EDF)
    int16_t left = 0;
    int16_t right = queue->queued - 1;
    while (left <= right) {
        int16_t mid = left + (right - left) / 2;
        if (queue->slots[queue->order[mid]].meta.deadline_local_us > slot->meta.deadline_local_us) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    insert_idx = left;

    // Shift elements to make space
    for (int16_t i = queue->queued - 1; i >= (int16_t)insert_idx; i--) {
        queue->order[i + 1] = queue->order[i];
    }

    queue->order[insert_idx] = slot_idx;
    queue->queued++;
    if (queue->queued > queue->high_water) {
        queue->high_water = queue->queued;
    }

    slot->state = CLDT_SLOT_QUEUED;
    return CLDT_OK;
}

cldt_status_t cldt_deadline_queue_pop(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    cldt_message_slot_t **slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    // TODO: Pre-pop expiry sweep

    if (queue->queued == 0) {
        *slot = NULL;
        return CLDT_ERR_NOT_READY;
    }

    // Basic earliest-deadline pop (first element in order array)
    uint16_t pop_idx = queue->order[0];

    // TODO: Advanced tie-breaking between equal deadlines

    *slot = &queue->slots[pop_idx];

    for (uint16_t i = 0; i < queue->queued - 1; i++) {
        queue->order[i] = queue->order[i + 1];
    }

    queue->queued--;
    (*slot)->state = CLDT_SLOT_TRANSPORT_OWNED;

    return CLDT_OK;
}

cldt_status_t cldt_deadline_queue_release(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    // TODO: Clear slot metadata completely to prevent leakage

    slot->state = CLDT_SLOT_FREE;
    return CLDT_OK;
}

cldt_status_t cldt_deadline_queue_expire(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    uint16_t *expired_slots)
{
    if (queue == NULL || expired_slots == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    uint16_t expired_count = 0;
    uint16_t write_idx = 0;

    for (uint16_t i = 0; i < queue->queued; i++) {
        uint16_t slot_idx = queue->order[i];
        if (queue->slots[slot_idx].meta.deadline_local_us <= now_local_us) {
            queue->slots[slot_idx].state = CLDT_SLOT_FREE;
            expired_count++;
            queue->expired++;
        } else {
            queue->order[write_idx++] = slot_idx;
        }
    }

    queue->queued = write_idx;
    *expired_slots = expired_count;

    return CLDT_OK;
}
