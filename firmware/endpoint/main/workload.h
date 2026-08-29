#ifndef CLDT_ENDPOINT_WORKLOAD_H
#define CLDT_ENDPOINT_WORKLOAD_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"

#include "cldt/cldt_types.h"
#include "deadline_queue.h"

#ifdef __cplusplus
extern "C" {
#endif

#define CLDT_ENDPOINT_MAX_STREAMS 8U

typedef struct {
    uint32_t stream_id;
    cldt_traffic_class_t traffic_class;
    uint32_t period_ms;
    uint32_t phase_ms;
    uint32_t jitter_ms;
    uint32_t deadline_ms;
    uint16_t payload_bytes;
    uint16_t burst_packets;
    uint16_t maximum_rate_pps;
} cldt_stream_config_t;

typedef struct {
    cldt_deadline_queue_t *queue;
    cldt_stream_config_t streams[CLDT_ENDPOINT_MAX_STREAMS];
    size_t stream_count;
    cldt_policy_t active_policy;
    TaskHandle_t producer_task;
    TimerHandle_t release_timer;
    uint32_t random_state;
    bool running;
} cldt_workload_t;

esp_err_t cldt_workload_init(
    cldt_workload_t *workload,
    cldt_deadline_queue_t *queue,
    const cldt_stream_config_t *streams,
    size_t stream_count,
    uint32_t seed);

/* Starts release timers only after the run digest is accepted. */
esp_err_t cldt_workload_start(cldt_workload_t *workload, uint64_t run_start_local_us);

/* Applies a prevalidated immutable policy snapshot at a release boundary. */
esp_err_t cldt_workload_apply_policy(
    cldt_workload_t *workload,
    const cldt_policy_t *policy);

/* ISR entry: capture no payload and wake only the producer task. */
void cldt_workload_event_isr(void *context);

esp_err_t cldt_workload_stop(cldt_workload_t *workload);

#ifdef __cplusplus
}
#endif

#endif
