#ifndef CLDT_CLOCK_SYNC_H
#define CLDT_CLOCK_SYNC_H

#include <stdbool.h>
#include <stdint.h>

#include "cldt/cldt_status.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_CLOCK_SYNC_WINDOW 16U

typedef struct {
    uint64_t request_local_us;
    uint64_t request_gateway_us;
    uint64_t response_gateway_us;
    uint64_t response_local_us;
} cldt_sync_exchange_t;

typedef struct {
    int64_t offset_us;
    int32_t drift_ppm;
    uint32_t uncertainty_us;
    uint32_t accepted_samples;
    uint32_t rejected_samples;
    uint32_t next_slot;
    cldt_sync_exchange_t window[CLDT_CLOCK_SYNC_WINDOW];
    bool valid;
} cldt_clock_sync_t;

void cldt_clock_sync_reset(cldt_clock_sync_t *state);

/* Adds one complete four-timestamp exchange; the implementation owns filtering. */
cldt_status_t cldt_clock_sync_observe(
    cldt_clock_sync_t *state,
    const cldt_sync_exchange_t *exchange);

/* Maps local monotonic time without modifying either device clock. */
cldt_status_t cldt_clock_sync_map_to_gateway(
    const cldt_clock_sync_t *state,
    uint64_t local_time_us,
    uint64_t *gateway_time_us,
    uint32_t *uncertainty_us);

#ifdef __cplusplus
}
#endif

#endif
