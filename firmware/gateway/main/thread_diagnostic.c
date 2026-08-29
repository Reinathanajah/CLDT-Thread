#include "thread_diagnostic.h"
#include "esp_openthread.h"
#include <openthread/instance.h>
#include <openthread/link.h>
#include <openthread/thread.h>
#include <stddef.h>

static cldt_mac_snapshot_t s_last_mac_snapshot = {0};
static uint16_t s_last_parent_rloc16 = 0xFFFF;
static uint8_t s_last_device_role = 0xFF;
static uint32_t s_last_partition_id = 0xFFFFFFFF;
static uint32_t s_observation_count = 0;

cldt_status_t cldt_thread_diagnostic_init(void)
{
    // TODO: implement thread-safety for initialization
    otInstance *instance = esp_openthread_get_instance();
    if (instance == NULL) {
        return CLDT_ERR_NOT_READY;
    }

    const otMacCounters *counters = otLinkGetCounters(instance);
    
    s_last_mac_snapshot.tx_total = counters->mTxTotal;
    s_last_mac_snapshot.tx_retry = counters->mTxRetry;
    s_last_mac_snapshot.tx_err_cca = counters->mTxErrCca;
    s_last_mac_snapshot.tx_direct_max_retry_expiry = counters->mTxDirectMaxRetryExpiry;
    s_last_mac_snapshot.rx_total = counters->mRxTotal;
    s_last_mac_snapshot.rx_err_fcs = counters->mRxErrFcs;
    s_last_mac_snapshot.rx_duplicated = counters->mRxDuplicated;

    // TODO: init parent info and role state variables here
    
    return CLDT_OK;
}

cldt_status_t cldt_thread_diagnostic_poll(cldt_cross_layer_observation_t *output)
{
    // TODO: implement thread-safety during poll
    // TODO: handle error cases from OT APIs appropriately for OT_ERROR cases
    
    if (output == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    otInstance *instance = esp_openthread_get_instance();
    if (instance == NULL) {
        return CLDT_ERR_INVALID_ARGUMENT;
    }

    const otMacCounters *counters = otLinkGetCounters(instance);
    
    output->mac_delta.tx_total = counters->mTxTotal - s_last_mac_snapshot.tx_total;
    output->mac_delta.tx_retry = counters->mTxRetry - s_last_mac_snapshot.tx_retry;
    output->mac_delta.tx_err_cca = counters->mTxErrCca - s_last_mac_snapshot.tx_err_cca;
    output->mac_delta.tx_direct_max_retry_expiry = counters->mTxDirectMaxRetryExpiry - s_last_mac_snapshot.tx_direct_max_retry_expiry;
    output->mac_delta.rx_total = counters->mRxTotal - s_last_mac_snapshot.rx_total;
    output->mac_delta.rx_err_fcs = counters->mRxErrFcs - s_last_mac_snapshot.rx_err_fcs;
    output->mac_delta.rx_duplicated = counters->mRxDuplicated - s_last_mac_snapshot.rx_duplicated;

    s_last_mac_snapshot.tx_total = counters->mTxTotal;
    s_last_mac_snapshot.tx_retry = counters->mTxRetry;
    s_last_mac_snapshot.tx_err_cca = counters->mTxErrCca;
    s_last_mac_snapshot.tx_direct_max_retry_expiry = counters->mTxDirectMaxRetryExpiry;
    s_last_mac_snapshot.rx_total = counters->mRxTotal;
    s_last_mac_snapshot.rx_err_fcs = counters->mRxErrFcs;
    s_last_mac_snapshot.rx_duplicated = counters->mRxDuplicated;

    otRouterInfo parent_info;
    otThreadGetParentInfo(instance, &parent_info);
    
    otLeaderData leader_data;
    otThreadGetLeaderData(instance, &leader_data);
    
    uint8_t current_role = otThreadGetDeviceRole(instance);

    output->thread_state.parent_rloc16 = parent_info.mRloc16;
    output->thread_state.parent_link_quality_in = parent_info.mLinkQualityIn;
    output->thread_state.parent_link_quality_out = parent_info.mLinkQualityOut;
    output->thread_state.partition_id = leader_data.mPartitionId;
    output->thread_state.device_role = current_role;

    output->thread_state.parent_changed = (parent_info.mRloc16 != s_last_parent_rloc16);
    output->thread_state.role_changed = (current_role != s_last_device_role);
    output->thread_state.partition_changed = (leader_data.mPartitionId != s_last_partition_id);

    s_last_parent_rloc16 = parent_info.mRloc16;
    s_last_device_role = current_role;
    s_last_partition_id = leader_data.mPartitionId;

    output->observation_count = s_observation_count++;
    
    // TODO: implement timestamp fetching to populate output->timestamp_us
    // TODO: package into trace records
    
    return CLDT_OK;
}
