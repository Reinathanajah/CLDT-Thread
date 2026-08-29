#include "esp_log.h"

static const char *TAG = "cldt_gateway";

void app_main(void)
{
    ESP_LOGW(TAG,
             "Research scaffold only: gateway runtime, provisioning, Thread "
             "bridge, backhaul, and policy guard are not implemented.");

    /*
     * IMPLEMENTATION ORDER:
     * 1. Prove provisioning storage and physical erase behavior without a run.
     * 2. Bring up the upstream RCP and Thread border router with no project policy.
     * 3. Add bounded Thread bridging and append-only observation publication.
     * 4. Add local policy guard, then only one expiring bulk-rate action.
     * 5. Compare SMP and unicore only after identical-build evidence exists.
     * Keep this entry point thin: construct runtime, call init/start, and let the
     * supervisor own failure handling. It must never become an ad-hoc demo flow.
     */
}
