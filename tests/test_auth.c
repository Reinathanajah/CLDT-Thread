#include <stdio.h>

#include "cldt/cldt_auth.h"

int main(void)
{
    /*
     * IMPLEMENTATION TODO:
     * 1. Use RFC 8439 known-answer material plus one project-specific fixed
     *    command vector with authority node ID 0, a fixed coordinator boot ID,
     *    the normative AAD byte order, and zero plaintext.
     * 2. Mutate every authenticated region, tag byte, run ID, epoch, and nonce
     *    byte independently and assert exact authentication failure status.
     *    A validly tagged but non-commissioned coordinator boot ID must produce
     *    CLDT_ERR_WRONG_AUTHORITY at the state-validation boundary.
     * 3. Verify one immutable command per epoch, strict epoch advance, and that
     *    retransmission reuses identical authenticated bytes rather than
     *    generating a different command under the same nonce.
     * 4. In the endpoint integration suite, verify persist-before-apply, reboot
     *    from a valid highest-epoch record, and safe fallback for missing,
     *    corrupt, or unwritable replay state. Boot identity must not substitute
     *    for that state.
     * 5. Run the same vector through the host and mbedTLS-backed targets before
     *    provisioning a command key or enabling remote actuation.
     */
    fprintf(stderr, "SKIP: authentication tests have not been implemented.\n");
    return 77;
}
