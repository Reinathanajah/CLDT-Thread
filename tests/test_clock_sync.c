#include <stdio.h>

#include "cldt/cldt_clock_sync.h"

int main(void)
{
    /*
     * IMPLEMENTATION TODO:
     * 1. Use synthetic four-timestamp exchanges with a known offset and drift.
     *    Assert that the estimate remains invalid until the documented minimum
     *    sample rule is met, then maps local time within its reported uncertainty.
     * 2. Add asymmetric-delay and high-round-trip samples. Verify that the chosen
     *    filter either rejects them or expands uncertainty; it must not return a
     *    deceptively precise one-way time.
     * 3. Test timestamp ordering faults, arithmetic near integer boundaries,
     *    boot/reset behavior, drift over a long interval, and output pointers
     *    remaining unchanged on error.
     * 4. The success criterion is honest uncertainty propagation, not merely a
     *    small offset on an ideal synthetic clock.
     */
    fprintf(stderr, "SKIP: clock-sync tests have not been implemented.\n");
    return 77;
}
