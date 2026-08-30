#include "deadline_queue.h"

#include <string.h>

cldt_status_t cldt_deadline_queue_init(
    cldt_deadline_queue_t *queue,
    uint16_t capacity)
{
    if (queue == NULL || capacity == 0 || capacity > CLDT_ENDPOINT_MAX_POOL_SLOTS) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    memset(queue, 0, sizeof(*queue));
    queue->capacity = capacity;

    return CLDT_OK;
}

cldt_status_t cldt_deadline_queue_acquire(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t **slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    // TODO: Acquire: linear scan slots[0..capacity-1] for CLDT_SLOT_FREE, transition to PRODUCER_OWNED
    // TODO: Capacity reservation: reserve N slots for CLDT_TRAFFIC_CONTROL and CLDT_TRAFFIC_CRITICAL classes

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_deadline_queue_commit(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot,
    uint64_t now_local_us)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    (void)now_local_us;

    // TODO: Commit: validate PRODUCER_OWNED state, check already-expired, binary search insert into order[], update high_water
    // TODO: The EXACT algorithm (EDF = Earliest Deadline First, sorted by deadline_local_us)
    // TODO: Binary search: compare deadline_local_us in order[] array, find insertion point, memmove to shift
    // TODO: Local EDF ordering is not an end-to-end schedulability proof. Retain
    // queue, transport, radio, and acknowledgement timing evidence.
    // TODO: Admission control: when queue is full, reject the item with the LATEST deadline (either incoming or last in queue)
    // TODO: Coalescing: for CLDT_TRAFFIC_TELEMETRY, if a queued item has same source node, replace the older one

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_deadline_queue_pop(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    cldt_message_slot_t **slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    (void)now_local_us;

    // TODO: Pop: always take order[0] (earliest deadline), shift array left, transition to TRANSPORT_OWNED

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_deadline_queue_release(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot)
{
    if (queue == NULL || slot == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    // TODO: Release: require PRODUCER_OWNED or TRANSPORT_OWNED, clear metadata bytes to prevent info leakage, transition to FREE

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_deadline_queue_expire(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    uint16_t *expired_slots)
{
    if (queue == NULL || expired_slots == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    (void)now_local_us;

    // TODO: Expiry sweep: the queue-owning task traverses order[] once, removes
    // expired items, and compacts survivors without changing relative order.
    // TODO: A 10 ms esp_timer callback only notifies that owner; it never walks or mutates the queue

    return CLDT_ERR_NOT_IMPLEMENTED;
}
