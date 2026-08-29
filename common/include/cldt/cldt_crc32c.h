#ifndef CLDT_CRC32C_H
#define CLDT_CRC32C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// Platform-adaptive CRC-32C (Castagnoli).
// ESP32: uses ROM LUT via esp_rom_crc32_le.
// Host: uses software table.
uint32_t cldt_crc32c(uint32_t seed, const void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif
