#ifndef CLDT_HOST_KALMAN_H
#define CLDT_HOST_KALMAN_H

#include <stdbool.h>
#include <stdint.h>
#include "cldt/cldt_status.h"

#define CLDT_KALMAN_DIM 5

typedef struct {
    float x[CLDT_KALMAN_DIM];                          // state estimate
    float P[CLDT_KALMAN_DIM][CLDT_KALMAN_DIM];         // estimate covariance
    float F[CLDT_KALMAN_DIM][CLDT_KALMAN_DIM];         // state transition
    float H[CLDT_KALMAN_DIM][CLDT_KALMAN_DIM];         // observation model
    float Q[CLDT_KALMAN_DIM][CLDT_KALMAN_DIM];         // process noise
    float R[CLDT_KALMAN_DIM][CLDT_KALMAN_DIM];         // measurement noise
    uint64_t last_update_us;
    uint32_t update_count;
    bool initialized;
} cldt_kalman_t;

cldt_status_t cldt_kalman_init(cldt_kalman_t *kf);
cldt_status_t cldt_kalman_set_model(cldt_kalman_t *kf, const float F[5][5], const float H[5][5], const float Q[5][5], const float R[5][5]);
cldt_status_t cldt_kalman_predict(cldt_kalman_t *kf);
cldt_status_t cldt_kalman_update(cldt_kalman_t *kf, const float z[5]);
float cldt_kalman_state_uncertainty(const cldt_kalman_t *kf, int state_index);

#endif // CLDT_HOST_KALMAN_H
