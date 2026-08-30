#ifndef CLDT_CRC32C_H
#define CLDT_CRC32C_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Planned platform-neutral CRC-32C (Castagnoli) contract. The scaffold returns
 * a placeholder value until fixed known-answer vectors are implemented. Do not
 * substitute esp_rom_crc32_le without proving the polynomial and seed/final-XOR
 * conventions match CRC-32C on every target.
 */
uint32_t cldt_crc32c(uint32_t seed, const void *buf, size_t len);

#ifdef __cplusplus
}
#endif

#endif
