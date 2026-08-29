#ifndef CLDT_METRICS_H
#define CLDT_METRICS_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "cldt/cldt_status.h"
#include "cldt/cldt_types.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * All counters refer to unique logical work items identified by run, node,
 * boot, and sequence. A transport retry is trace detail, not another sent
 * item. Aggregate counters are useful only after the item-identity audit below;
 * equal totals alone cannot prove that one item was not counted twice while
 * another item disappeared.
 */
typedef struct {
    uint64_t released[CLDT_TRAFFIC_COUNT];
    uint64_t admitted[CLDT_TRAFFIC_COUNT];
    uint64_t sent[CLDT_TRAFFIC_COUNT];
    uint64_t acknowledged[CLDT_TRAFFIC_COUNT];
    uint64_t on_time_acknowledged[CLDT_TRAFFIC_COUNT];
    uint64_t deadline_missed[CLDT_TRAFFIC_COUNT];
    uint64_t expired[CLDT_TRAFFIC_COUNT];
    uint64_t coalesced[CLDT_TRAFFIC_COUNT];
    uint64_t rejected[CLDT_TRAFFIC_COUNT];
    uint64_t dropped[CLDT_TRAFFIC_COUNT];
    uint64_t duplicated[CLDT_TRAFFIC_COUNT];
    uint64_t response_time_sum_us[CLDT_TRAFFIC_COUNT];
    uint64_t lateness_sum_us[CLDT_TRAFFIC_COUNT];
    uint32_t queue_high_water;
    uint32_t pool_exhaustions;
    uint64_t measurement_duration_us;
    uint64_t energy_uj;
} cldt_metrics_t;

/*
 * Reconciliation is a computed report, not a mutable metric. A class is
 * consistent only when every released work item is terminal or explicitly
 * unresolved at the snapshot boundary.
 */
typedef struct {
    uint64_t terminal[CLDT_TRAFFIC_COUNT];
    uint64_t unresolved[CLDT_TRAFFIC_COUNT];
    bool consistent[CLDT_TRAFFIC_COUNT];
} cldt_reconciliation_t;

/*
 * Result of auditing raw work-item lifecycles by full logical identity. This
 * is deliberately separate from aggregate reconciliation so reports cannot
 * mistake balanced counter corruption for complete evidence.
 */
typedef struct {
    uint64_t logical_items;
    uint64_t duplicate_releases;
    uint64_t duplicate_terminals;
    uint64_t terminal_without_release;
    uint64_t unresolved_items;
    bool consistent;
} cldt_item_audit_t;

void cldt_metrics_reset(cldt_metrics_t *metrics);

cldt_status_t cldt_metrics_record_trace(
    cldt_metrics_t *metrics,
    const cldt_trace_record_t *record);

/*
 * Calculates per-class aggregate conservation without modifying metrics. This
 * is a necessary check, not proof of per-item uniqueness. The caller must also
 * require a consistent cldt_item_audit_t and archive unresolved work rather
 * than discarding it before computing rates.
 */
cldt_status_t cldt_metrics_reconcile(
    const cldt_metrics_t *metrics,
    cldt_reconciliation_t *output);

/*
 * Audits work-item lifecycles in a trace sorted lexicographically by run_id,
 * node_id, boot_id, sequence, and local_time_us. The function skips non-item
 * events and never reorders caller-owned storage. Sorting belongs to the host
 * analysis/recorder boundary because embedded targets must not allocate an
 * unbounded identity table. A reportable run requires this audit and aggregate
 * reconciliation to pass.
 */
cldt_status_t cldt_metrics_audit_sorted_trace(
    const cldt_trace_record_t *records,
    size_t record_count,
    cldt_item_audit_t *output);

#ifdef __cplusplus
}
#endif

#endif
