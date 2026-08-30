#include "power_probe.h"
#include "esp_err.h"

esp_err_t cldt_power_probe_init(const cldt_power_probe_config_t* config) {
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /*
     * DEFERRED INSTRUMENT CONTRACT:
     * No power monitor is part of the six-week core build. Select and admit an
     * instrument only after the primary fidelity-gate experiment is operational.
     * The implementation must document shunt value, range, resolution, sample
     * cadence, calibration evidence, saturation handling, and uncertainty before
     * it may emit CLDT_EVENT_POWER_SAMPLE records.
     *
     * If an I2C monitor is later admitted on the XIAO ESP32-C6 carrier, the
     * provisional board pins are D4/SDA (GPIO22) and D5/SCL (GPIO23). Confirm the
     * actual board revision and instrument datasheet before wiring.
     */
    (void)config;
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_power_probe_sample(cldt_power_sample_t* output) {
    if (output == NULL) {
        return ESP_ERR_INVALID_ARG;
    }

    /* TODO: emit samples only from a calibrated, admitted instrument. */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_power_probe_reset_energy(uint64_t run_start_us) {
    (void)run_start_us;
    /* TODO: reset the admitted instrument's integration state. */
    return ESP_ERR_NOT_SUPPORTED;
}

esp_err_t cldt_power_probe_stop(void) {
    /* TODO: release resources after a power instrument is admitted. */
    return ESP_ERR_NOT_SUPPORTED;
}
