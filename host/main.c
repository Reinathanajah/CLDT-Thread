#include <stdio.h>
#include <stdlib.h>

#include "coordinator.h"

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    fprintf(stderr,
            "CLDT host scaffold: implement manifest loading, recording, "
            "modeling, and fidelity-gated coordination before use.\n");

    /*
     * IMPLEMENTATION TODO:
     * 1. Accept exactly one manifest path and one optional results-root path;
     *    print a short usage error for every other argument shape.
     * 2. Read with a bounded size, validate the JSON schema, and refuse a
     *    state == "template" manifest before any network connection is made.
     * 3. Resolve the manifest's named control profile from a versioned local
     *    registry, verify its canonical digest, and reject absent or mismatched
     *    profile/calibration identities before opening a broker connection.
     * 4. Create the immutable run directory, install signal handling that only
     *    requests a stop, initialize the coordinator with both config and
     *    resolved profile, and enter its event loop.
     * 5. Return a nonzero status for invalid, interrupted, or failed runs. A
     *    successful process exit is not evidence that a result is valid.
     */
    return EXIT_FAILURE;
}
