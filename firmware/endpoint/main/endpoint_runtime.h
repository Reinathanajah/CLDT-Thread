#ifndef CLDT_ENDPOINT_RUNTIME_H
#define CLDT_ENDPOINT_RUNTIME_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#include "cldt/cldt_clock_sync.h"
#include "cldt/cldt_event_trace.h"
#include "cldt/cldt_types.h"
#include "deadline_queue.h"
#include "power_probe.h"
#include "workload.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CLDT_ENDPOINT_BOOT = 0,
    CLDT_ENDPOINT_COMMISSIONING,
    CLDT_ENDPOINT_ATTACHED,
    CLDT_ENDPOINT_IDLE,
    CLDT_ENDPOINT_RUNNING,
    CLDT_ENDPOINT_FALLBACK,
    CLDT_ENDPOINT_FAULT
} cldt_endpoint_state_t;

typedef struct {
    cldt_node_id_t node_id;
    cldt_node_role_t role;
    cldt_endpoint_state_t state;
    cldt_run_id_t active_run_id;
    cldt_boot_id_t boot_id;
    cldt_sequence_t next_sequence;
    cldt_policy_epoch_t applied_epoch;
    cldt_policy_t safe_policy;
    cldt_policy_t active_policy;
    cldt_clock_sync_t clock_sync;
    cldt_deadline_queue_t deadline_queue;
    cldt_workload_t workload;
    cldt_event_trace_t trace;
    EventGroupHandle_t events;
    TaskHandle_t supervisor_task;
    TaskHandle_t transmitter_task;
    TaskHandle_t trace_task;
    TaskHandle_t power_task;
    bool started;
} cldt_endpoint_runtime_t;

esp_err_t cldt_endpoint_runtime_init(cldt_endpoint_runtime_t *runtime);
esp_err_t cldt_endpoint_runtime_start(cldt_endpoint_runtime_t *runtime);

/* Validates run, authentication, epoch, TTL, and local limits before apply. */
esp_err_t cldt_endpoint_runtime_receive_command(
    cldt_endpoint_runtime_t *runtime,
    const uint8_t *datagram,
    size_t datagram_bytes,
    uint64_t received_local_us);

esp_err_t cldt_endpoint_runtime_request_stop(cldt_endpoint_runtime_t *runtime);

#ifdef __cplusplus
}
#endif

#endif
