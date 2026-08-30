#include "cldt/cldt_crc32c.h"

uint32_t cldt_crc32c(uint32_t seed, const void *buf, size_t len)
{
    /*
     * IMPLEMENTATION TODO:
     * - implement reflected CRC-32C using polynomial 0x82F63B78;
     * - freeze the seed and final-XOR convention with fixed vectors;
     * - verify the same vectors on the host, ESP32-S3, and ESP32-C6;
     * - compute the wire CRC over the canonical header-plus-payload sequence;
     * - do not use the similarly named ROM IEEE CRC-32 routine as CRC-32C.
     */
    (void)seed;
    (void)buf;
    (void)len;
    return UINT32_C(0);
}
