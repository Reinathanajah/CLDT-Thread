#ifndef CLDT_HOST_RUN_RECORDER_H
#define CLDT_HOST_RUN_RECORDER_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#include "cldt/cldt_status.h"
#include "experiment_config.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    /* event_stream is append-only. finalized prevents a second terminal status. */
    FILE *event_stream;
    char run_directory[260];
    uint64_t records_written;
    bool finalized;
} cldt_run_recorder_t;

/*
 * Creates a new run directory and fails if it already exists. The recorder owns
 * only files it creates for this run; it may never delete or rewrite a prior run.
 */
cldt_status_t cldt_run_recorder_open(
    cldt_run_recorder_t *recorder,
    const char *results_root,
    const cldt_experiment_config_t *config,
    const char *original_manifest,
    size_t original_manifest_bytes);

/* Appends one raw received record; parsing and model updates happen elsewhere. */
cldt_status_t cldt_run_recorder_append(
    cldt_run_recorder_t *recorder,
    const char *topic,
    const uint8_t *payload,
    size_t payload_bytes,
    uint64_t received_host_us);

/* Writes one immutable terminal status after counters and evidence are collected. */
cldt_status_t cldt_run_recorder_finalize(
    cldt_run_recorder_t *recorder,
    const char *status,
    const char *reason);

#ifdef __cplusplus
}
#endif

#endif
