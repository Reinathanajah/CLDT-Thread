#include "kalman.h"
#include <string.h>

#define CLDT_KALMAN_INIT_VARIANCE 1000.0f

// TODO: Matrix helper signatures needed: mat5_multiply(out[5][5], a[5][5], b[5][5]), mat5_transpose, mat5_add, mat5_vec5_multiply, vec5_sub
// TODO: Gauss-Jordan 5x5 inverse: partial pivoting, scale pivot row, eliminate column, ~80 lines

cldt_status_t cldt_kalman_init(cldt_kalman_t *kf) {
    if (!kf) return CLDT_ERR_INVALID_ARGUMENT;

    memset(kf, 0, sizeof(cldt_kalman_t));
    for (int i = 0; i < 5; ++i) {
        kf->P[i][i] = CLDT_KALMAN_INIT_VARIANCE;
    }
    kf->initialized = false;
    return CLDT_OK;
}

cldt_status_t cldt_kalman_set_model(cldt_kalman_t *kf, const float F[5][5], const float H[5][5], const float Q[5][5], const float R[5][5]) {
    if (!kf || !F || !H || !Q || !R) return CLDT_ERR_INVALID_ARGUMENT;

    (void)kf;
    (void)F;
    (void)H;
    (void)Q;
    (void)R;

    // TODO: Q tuning: run pilot data with static network, compute empirical variance of prediction residuals
    // TODO: R tuning: collect readings while state is forced static, calculate empirical variance
    
    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_kalman_predict(cldt_kalman_t *kf) {
    if (!kf || !kf->initialized) return CLDT_ERR_WRONG_STATE;

    (void)kf;

    // TODO: Exact Kalman equations: x_pred = F*x, P_pred = F*P*F^T + Q
    // TODO: Measure update cost on the actual host build; do not infer real-time behavior from an operation-count estimate

    return CLDT_ERR_NOT_IMPLEMENTED;
}

cldt_status_t cldt_kalman_update(cldt_kalman_t *kf, const float z[5]) {
    if (!kf || !kf->initialized || !z) return CLDT_ERR_WRONG_STATE;

    (void)kf;
    (void)z;

    // TODO: Exact Kalman equations: y = z - H*x, S = H*P*H^T + R, K = P*H^T*S^{-1}, x = x + K*y, P = (I-K*H)*P

    return CLDT_ERR_NOT_IMPLEMENTED;
}

float cldt_kalman_state_uncertainty(const cldt_kalman_t *kf, int state_index) {
    if (!kf || state_index < 0 || state_index >= 5) return -1.0f;
    
    (void)kf;
    (void)state_index;

    // TODO: P diagonal gives per-state uncertainty: P[2][2] = critical_pdr variance for fidelity gate

    return -1.0f;
}
