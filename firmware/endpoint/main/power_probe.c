#include "power_probe.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "driver/i2c_master.h"
#include <stdbool.h>
#include <string.h>

#define I2C_MASTER_SCL_IO           7
#define I2C_MASTER_SDA_IO           6
#define I2C_MASTER_FREQ_HZ          400000

#define INA219_REG_CONFIG           0x00
#define INA219_REG_BUS_VOLTAGE      0x02
#define INA219_REG_CURRENT          0x04
#define INA219_REG_CALIBRATION      0x05

static const char *TAG = "POWER_PROBE";

static i2c_master_dev_handle_t s_ina219_dev;
static cldt_power_probe_config_t s_config;
static uint64_t s_accumulated_energy_uj;
static uint64_t s_prev_sample_us;
static bool s_initialized;

static i2c_master_bus_handle_t s_bus_handle;

esp_err_t cldt_power_probe_init(const cldt_power_probe_config_t* config) {
    if (config == NULL) {
        return ESP_ERR_INVALID_ARG;
    }
    
    s_config = *config;
    
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_NUM_0,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true,
    };
    
    esp_err_t ret = i2c_new_master_bus(&i2c_mst_config, &s_bus_handle);
    if (ret != ESP_OK) {
        return ret;
    }
    
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = s_config.i2c_address,
        .scl_speed_hz = I2C_MASTER_FREQ_HZ,
    };
    
    ret = i2c_master_bus_add_device(s_bus_handle, &dev_cfg, &s_ina219_dev);
    if (ret != ESP_OK) {
        return ret;
    }

    // TODO: Write INA219 calibration register (reg 0x05)
    // TODO: Set configuration register (reg 0x00)

    s_accumulated_energy_uj = 0;
    s_prev_sample_us = esp_timer_get_time();
    s_initialized = true;

    return ESP_OK;
}

esp_err_t cldt_power_probe_sample(cldt_power_sample_t* output) {
    if (!s_initialized || output == NULL) {
        return ESP_ERR_INVALID_STATE;
    }

    uint8_t reg_addr;
    uint8_t data[2];
    
    reg_addr = INA219_REG_BUS_VOLTAGE;
    esp_err_t ret = i2c_master_transmit_receive(s_ina219_dev, &reg_addr, 1, data, 2, -1);
    if (ret != ESP_OK) return ret;
    int16_t bus_voltage_raw = (data[0] << 8) | data[1];
    
    reg_addr = INA219_REG_CURRENT;
    ret = i2c_master_transmit_receive(s_ina219_dev, &reg_addr, 1, data, 2, -1);
    if (ret != ESP_OK) return ret;
    int16_t current_raw = (data[0] << 8) | data[1];

    // TODO: Application of conversion factors for bus_voltage_uv and current_ua
    // TODO: Saturation checks
    // TODO: Error trace events
    
    int32_t bus_voltage_uv = bus_voltage_raw * 4000; 
    int32_t current_ua = current_raw * 100;
    
    int64_t power_uw = ((int64_t)bus_voltage_uv * current_ua) / 1000000;
    
    uint64_t now = esp_timer_get_time();
    uint64_t delta_us = now - s_prev_sample_us;
    s_accumulated_energy_uj += (power_uw * delta_us) / 1000000;
    
    output->local_time_us = now;
    output->bus_voltage_uv = bus_voltage_uv;
    output->current_ua = current_ua;
    output->power_uw = power_uw;
    output->accumulated_energy_uj = s_accumulated_energy_uj;
    output->calibration_id = s_config.calibration_id;
    output->valid = true;
    
    s_prev_sample_us = now;
    
    return ESP_OK;
}

esp_err_t cldt_power_probe_reset_energy(uint64_t run_start_us) {
    s_accumulated_energy_uj = 0;
    s_prev_sample_us = run_start_us;
    return ESP_OK;
}

esp_err_t cldt_power_probe_stop(void) {
    s_initialized = false;
    // TODO: Read final sample
    // TODO: Release I2C resource
    return ESP_OK;
}
