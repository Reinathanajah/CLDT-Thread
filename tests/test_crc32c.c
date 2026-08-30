#include <stdio.h>

#include "cldt/cldt_crc32c.h"

int main(void)
{
    /*
     * IMPLEMENTATION TODO:
     * 1. Freeze standard CRC-32C known-answer vectors, including empty input and
     *    "123456789", with the exact seed and final-XOR convention.
     * 2. Test incremental versus single-buffer updates, zero length, unaligned
     *    input, binary zero bytes, and the canonical header-plus-payload wire
     *    integrity sequence.
     * 3. Run identical vectors on the host, ESP32-S3, and ESP32-C6. A platform
     *    helper with the IEEE polynomial must fail the Castagnoli vector.
     * 4. Do not enable frame acceptance until this test is no longer skipped.
     */
    fprintf(stderr, "SKIP: CRC-32C tests have not been implemented.\n");
    return 77;
}
