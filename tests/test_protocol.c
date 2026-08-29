#include <stdio.h>

#include "cldt/cldt_protocol.h"

int main(void)
{
    /*
     * IMPLEMENTATION TODO:
     * 1. Begin with fixed hexadecimal byte vectors for the smallest and largest
     *    legal frames. Assert every CLDT_WIRE_*_OFFSET, zero reserved bytes,
     *    network byte order, exact size, CRC-32C, and truncated authentication
     *    tag—not only encode/decode round trips, which can hide matching mistakes
     *    on both sides. Mutating either reserved byte must fail decoding.
     * 2. Add rejection cases one mutation at a time: wrong magic, unsupported
     *    version, header/payload length mismatch, truncation at every boundary,
     *    trailing bytes, CRC mutation, authentication mutation, and oversize data.
     * 3. Build one fixed CLDT_POLICY_WIRE_BYTES vector and assert every policy
     *    array/field offset plus equality between payload and metadata epochs.
     *    Test wrong run ID, duplicate epoch, older epoch, stale issue time, zero
     *    TTL, expired TTL, and boundary uncertainty. Verify the exact status,
     *    including CLDT_ERR_STALE and CLDT_ERR_WRONG_RUN, and confirm decoder
     *    output is not partially published.
     * 4. Keep test vectors in ordinary source data with a short derivation note.
     *    Do not connect Thread or MQTT until these host-only checks are green.
     */
    fprintf(stderr, "SKIP: protocol tests have not been implemented.\n");
    return 77;
}
