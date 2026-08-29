#ifndef CLDT_GATEWAY_THREAD_DIAGNOSTIC_H
#define CLDT_GATEWAY_THREAD_DIAGNOSTIC_H

#include <stdint.h>
#include <stdbool.h>
#include "cldt/cldt_status.h"

typedef struct {
    uint32_t tx_total;
    uint32_t tx_retry;
    uint32_t tx_err_cca;
    uint32_t tx_direct_max_retry_expiry;
    uint32_t rx_total;
    uint32_t rx_err_fcs;
    uint32_t rx_duplicated;
} cldt_mac_snapshot_t;

typedef struct {
    uint16_t parent_rloc16;
    uint8_t parent_link_quality_in;
    uint8_t parent_link_quality_out;
    uint32_t partition_id;
    uint8_t device_role;
    bool parent_changed;
    bool role_changed;
    bool partition_changed;
} cldt_thread_state_t;

typedef struct {
    cldt_mac_snapshot_t mac_delta;
    cldt_thread_state_t thread_state;
    uint64_t timestamp_us;
    uint32_t observation_count;
} cldt_cross_layer_observation_t;

cldt_status_t cldt_thread_diagnostic_init(void);
cldt_status_t cldt_thread_diagnostic_poll(cldt_cross_layer_observation_t *output);

#endif // CLDT_GATEWAY_THREAD_DIAGNOSTIC_H
