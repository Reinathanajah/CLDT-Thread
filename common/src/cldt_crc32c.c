#include "cldt/cldt_crc32c.h"

#ifdef ESP_PLATFORM
#include "esp_rom_crc.h"

uint32_t cldt_crc32c(uint32_t seed, const void *buf, size_t len) {
    return esp_rom_crc32_le(~seed, (const uint8_t *)buf, len);
}

#else

// TODO: implement full 256-entry table for performance
static const uint32_t cldt_crc32c_table[256] = {
    0x00000000, 0xF26B8303, 0xE13B70F7, 0x1350F3F4,
    0xC79A971F, 0x35F1141C, 0x26A1E7E8, 0xD4CA64EB,
    0x8AD958CF, 0x78B2DBCC, 0x6BE22838, 0x9989AB3B,
    0x4D43CFD0, 0xBF284CD3, 0xAC78BF27, 0x5E133C24
    // TODO: Fill remaining 240 entries
};

uint32_t cldt_crc32c(uint32_t seed, const void *buf, size_t len) {
    const uint8_t *p = (const uint8_t *)buf;
    uint32_t crc = ~seed;
    
    for (size_t i = 0; i < len; i++) {
        crc = cldt_crc32c_table[(crc ^ p[i]) & 0xFF] ^ (crc >> 8);
    }
    
    return ~crc;
}

#endif
