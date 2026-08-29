#ifndef CLDT_ENDPOINT_DEADLINE_QUEUE_H
#define CLDT_ENDPOINT_DEADLINE_QUEUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_ENDPOINT_MAX_POOL_SLOTS 128U

typedef enum {
    CLDT_SLOT_FREE = 0,
    CLDT_SLOT_PRODUCER_OWNED,
    CLDT_SLOT_QUEUED,
    CLDT_SLOT_TRANSPORT_OWNED
} cldt_slot_state_t;

typedef struct {
    /* Slot state is the ownership proof; no slot may have two owners at once. */
    cldt_slot_state_t state;
    cldt_frame_meta_t meta;
    uint16_t payload_bytes;
    uint8_t payload[CLDT_MAX_PAYLOAD_BYTES];
} cldt_message_slot_t;

typedef struct {
    /* order contains slot indices in deadline order; it is never a second payload store. */
    cldt_message_slot_t slots[CLDT_ENDPOINT_MAX_POOL_SLOTS];
    uint16_t order[CLDT_ENDPOINT_MAX_POOL_SLOTS];
    uint16_t capacity;
    uint16_t queued;
    uint16_t high_water;
    uint64_t rejected;
    uint64_t expired;
    uint64_t coalesced;
    uint64_t pool_exhaustions;
} cldt_deadline_queue_t;

/*
 * The queue has one task owner. ISRs notify the producer; they never call this
 * API. capacity must not exceed CLDT_ENDPOINT_MAX_POOL_SLOTS.
 */
cldt_status_t cldt_deadline_queue_init(
    cldt_deadline_queue_t *queue,
    uint16_t capacity);

/*
 * Transfers one free slot to the producer. The producer must fully initialize
 * metadata and payload before commit; it must release the slot on any local
 * generation failure instead of leaving a producer-owned leak.
 */
cldt_status_t cldt_deadline_queue_acquire(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t **slot);

/*
 * Transfers a completely initialized producer slot to the queue. The queue is
 * responsible for expiry and admission accounting after this call succeeds.
 */
cldt_status_t cldt_deadline_queue_commit(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot,
    uint64_t now_local_us);

/*
 * Transfers the next live slot to the transport task. A successful pop does not
 * imply delivery; transport must produce a terminal trace then release the slot.
 */
cldt_status_t cldt_deadline_queue_pop(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    cldt_message_slot_t **slot);

/* Returns a producer- or transport-owned slot to the pool after terminal trace. */
cldt_status_t cldt_deadline_queue_release(
    cldt_deadline_queue_t *queue,
    cldt_message_slot_t *slot);

/* Expires queued work and returns the number of slots released. */
cldt_status_t cldt_deadline_queue_expire(
    cldt_deadline_queue_t *queue,
    uint64_t now_local_us,
    uint16_t *expired_slots);

#ifdef __cplusplus
}
#endif

#endif
