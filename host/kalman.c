#include "kalman.h"
#include <string.h>

#define CLDT_KALMAN_INIT_VARIANCE 1000.0f

static void mat5_multiply(float out[5][5], const float a[5][5], const float b[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            out[i][j] = 0.0f;
            for (int k = 0; k < 5; ++k) {
                out[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}

static void mat5_transpose(float out[5][5], const float a[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            out[i][j] = a[j][i];
        }
    }
}

static void mat5_add(float out[5][5], const float a[5][5], const float b[5][5]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            out[i][j] = a[i][j] + b[i][j];
        }
    }
}

static void mat5_vec5_multiply(float out[5], const float a[5][5], const float v[5]) {
    for (int i = 0; i < 5; ++i) {
        out[i] = 0.0f;
        for (int j = 0; j < 5; ++j) {
            out[i] += a[i][j] * v[j];
        }
    }
}

static void vec5_sub(float out[5], const float a[5], const float b[5]) {
    for (int i = 0; i < 5; ++i) {
        out[i] = a[i] - b[i];
    }
}

static bool mat5_inverse(float out[5][5], const float in[5][5]) {
    // TODO: implement Gauss-Jordan 5x5 inverse
    return false;
}

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

    memcpy(kf->F, F, sizeof(kf->F));
    memcpy(kf->H, H, sizeof(kf->H));
    memcpy(kf->Q, Q, sizeof(kf->Q));
    memcpy(kf->R, R, sizeof(kf->R));
    kf->initialized = true;

    return CLDT_OK;
}

cldt_status_t cldt_kalman_predict(cldt_kalman_t *kf) {
    if (!kf || !kf->initialized) return CLDT_ERR_WRONG_STATE;

    float x_pred[5];
    mat5_vec5_multiply(x_pred, kf->F, kf->x);
    memcpy(kf->x, x_pred, sizeof(kf->x));

    float F_T[5][5];
    float FP[5][5];
    float FPF_T[5][5];

    mat5_transpose(F_T, kf->F);
    mat5_multiply(FP, kf->F, kf->P);
    mat5_multiply(FPF_T, FP, F_T);
    mat5_add(kf->P, FPF_T, kf->Q);

    return CLDT_OK;
}

cldt_status_t cldt_kalman_update(cldt_kalman_t *kf, const float z[5]) {
    if (!kf || !kf->initialized || !z) return CLDT_ERR_WRONG_STATE;

    float Hx[5];
    float y[5];
    mat5_vec5_multiply(Hx, kf->H, kf->x);
    vec5_sub(y, z, Hx);

    float H_T[5][5];
    float HP[5][5];
    float HPH_T[5][5];
    float S[5][5];

    mat5_transpose(H_T, kf->H);
    mat5_multiply(HP, kf->H, kf->P);
    mat5_multiply(HPH_T, HP, H_T);
    mat5_add(S, HPH_T, kf->R);

    // TODO: Kalman gain K = P*H^T*S^{-1}
    // TODO: state update
    // TODO: covariance update
    
    return CLDT_OK;
}

float cldt_kalman_state_uncertainty(const cldt_kalman_t *kf, int state_index) {
    if (!kf || state_index < 0 || state_index >= 5) return -1.0f;
    return kf->P[state_index][state_index];
}
