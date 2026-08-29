#ifndef CLDT_GATEWAY_RUNTIME_H
#define CLDT_GATEWAY_RUNTIME_H

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/task.h"

#include "cldt/cldt_event_trace.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    CLDT_GATEWAY_BOOT = 0,
    CLDT_GATEWAY_PROVISIONING,
    CLDT_GATEWAY_FORMING_THREAD,
    CLDT_GATEWAY_IDLE,
    CLDT_GATEWAY_WARMUP,
    CLDT_GATEWAY_MEASURING,
    CLDT_GATEWAY_COOLDOWN,
    CLDT_GATEWAY_FALLBACK,
    CLDT_GATEWAY_FAULT
} cldt_gateway_state_t;

typedef struct {
    cldt_node_id_t node_id;
    cldt_gateway_state_t state;
    cldt_run_id_t active_run_id;
    cldt_policy_t active_policy;
    QueueHandle_t thread_rx_queue;
    QueueHandle_t observation_queue;
    QueueHandle_t command_queue;
    EventGroupHandle_t events;
    TaskHandle_t supervisor_task;
    TaskHandle_t aggregator_task;
    TaskHandle_t publisher_task;
    portMUX_TYPE policy_spinlock;
    bool started;
} cldt_gateway_runtime_t;

/*
 * Initializes caller-owned state and all static RTOS objects. No task may run
 * and no radio may start before this function succeeds completely.
 */
esp_err_t cldt_gateway_runtime_init(cldt_gateway_runtime_t *runtime);

/* Starts tasks only after provisioning, RCP, Thread, and backhaul are ready. */
esp_err_t cldt_gateway_runtime_start(cldt_gateway_runtime_t *runtime);

/* Requests bounded shutdown at a run boundary; it must not delete live tasks. */
esp_err_t cldt_gateway_runtime_request_stop(cldt_gateway_runtime_t *runtime);

#ifdef __cplusplus
}
#endif

#endif
