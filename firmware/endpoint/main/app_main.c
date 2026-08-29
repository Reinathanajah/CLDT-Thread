#include "esp_log.h"

static const char *TAG = "cldt_endpoint";

void app_main(void)
{
    ESP_LOGW(TAG,
             "Research scaffold only: endpoint runtime, deadline queue, "
             "workload, Thread transport, and power probe are not implemented.");

    /*
     * IMPLEMENTATION ORDER:
     * 1. Keep networking disabled while proving local software-timer, ISR,
     *    queue ownership, fixed-pool exhaustion, expiry, and counter tests.
     * 2. Add Thread attachment only after those tests produce reconciled traces.
     * 3. Add command handling only after protocol known-answer and replay tests.
     * 4. Enable the optional power probe last and document its overhead.
     * This entry point should remain small: construct runtime, call init/start,
     * and hand lifecycle ownership to the supervisor. It is not a demo script.
     */
}
