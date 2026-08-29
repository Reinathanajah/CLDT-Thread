#ifndef CLDT_EVENT_TRACE_H
#define CLDT_EVENT_TRACE_H

#include <stddef.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    cldt_trace_record_t *records;
    size_t capacity;
    size_t read_index;
    size_t write_index;
    size_t count;
    uint64_t dropped_records;
} cldt_event_trace_t;

/* Uses caller-owned storage. Concurrency protection belongs to the adapter. */
cldt_status_t cldt_event_trace_init(
    cldt_event_trace_t *trace,
    cldt_trace_record_t *storage,
    size_t capacity);

cldt_status_t cldt_event_trace_push(
    cldt_event_trace_t *trace,
    const cldt_trace_record_t *record);

cldt_status_t cldt_event_trace_pop(
    cldt_event_trace_t *trace,
    cldt_trace_record_t *record);

#ifdef __cplusplus
}
#endif

#endif
