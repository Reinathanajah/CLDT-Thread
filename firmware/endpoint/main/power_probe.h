#ifndef CLDT_ENDPOINT_POWER_PROBE_H
#define CLDT_ENDPOINT_POWER_PROBE_H

#include <stdbool.h>
#include <stdint.h>

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint64_t local_time_us;
    uint32_t bus_voltage_uv;
    int32_t current_ua;
    int64_t power_uw;
    uint64_t accumulated_energy_uj;
    uint32_t calibration_id;
    bool valid;
} cldt_power_sample_t;

typedef struct {
    uint8_t i2c_address;
    uint32_t shunt_resistance_uohm;
    uint32_t calibration_id;
    uint32_t sample_interval_ms;
} cldt_power_probe_config_t;

esp_err_t cldt_power_probe_init(const cldt_power_probe_config_t *config);

/* Reads one sample; integration uses actual adjacent timestamps, not nominal rate. */
esp_err_t cldt_power_probe_sample(cldt_power_sample_t *output);

esp_err_t cldt_power_probe_reset_energy(uint64_t run_start_local_us);

esp_err_t cldt_power_probe_stop(void);

#ifdef __cplusplus
}
#endif

#endif
