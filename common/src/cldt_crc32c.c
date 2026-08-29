#include "cldt/cldt_crc32c.h"

#ifdef ESP_PLATFORM
#include <esp_rom_crc.h>

// On ESP32 (S3 and C6): esp_rom_crc32_le uses ROM-resident software LUT, NOT hardware CRC
// esp_rom_crc32_le takes (~seed) as first arg because it uses inverted convention
uint32_t cldt_crc32c(uint32_t seed, const uint8_t *data, size_t length) {
    return ~esp_rom_crc32_le(~seed, data, length);
}
#else
uint32_t cldt_crc32c(uint32_t seed, const uint8_t *data, size_t length) {
    // TODO: CRC-32C (Castagnoli) polynomial: 0x1EDC6F41
    // TODO: Full 256-entry lookup table needed for byte-at-a-time computation
    // TODO: Algorithm: crc = ~seed; for each byte: crc = table[(crc ^ byte) & 0xFF] ^ (crc >> 8); return ~crc
    // TODO: Table generation: for each i in 0..255: crc=i, for 8 bits: if crc&1 then crc=(crc>>1)^0x82F63B78 else crc>>=1; table[i]=crc
    // TODO: 0x82F63B78 is the bit-reversed form of the Castagnoli polynomial 0x1EDC6F41
    // TODO: First 4 entries for verification: table[0]=0x00000000, table[1]=0xF26B8303, table[2]=0xE13B70F7, table[3]=0x1350F3F4
    // TODO: On ESP32 (S3 and C6): esp_rom_crc32_le uses ROM-resident software LUT, NOT hardware CRC
    // TODO: esp_rom_crc32_le takes (~seed) as first arg because it uses inverted convention
    // TODO: For host builds: generate table at compile time or use static const array
    // TODO: Wire protocol uses CRC-32C at CLDT_WIRE_CRC32C_OFFSET (byte 52), computed over bytes 0-51

    (void)seed;
    (void)data;
    (void)length;
    return 0;
}
#endif
