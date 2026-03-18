#include "pch.h"
#include "math.h"

#include "constants.h"
#include "structures.h"

void PID_CALC(pid_reg *a, float b) {

    a->eps = a->Kp * b;

    a->integ += a->Ki * 0.5 * (a->eps + a->eps_prev) * Ts;
    if (a->integ > a->max) a->integ = a->max;
    if (a->integ < a->min) a->integ = a->min;

    a->dif = a->Kd * (a->eps - a->eps_prev) * Fs;

    a->out = a->eps + a->integ + a->dif;
    a->eps_prev = a->eps;

    if (a->out > a->max) a->out = a->max;
    if (a->out < a->min) a->out = a->min;

};

void ABC_ab(vec* vector) {

    vector->a = 0.33333333333 * (2.0 * vector->A - vector->B - vector->C);
    vector->b = 0.5773 * (vector->B - vector->C);

};

void ab_dq(vec* vector, float angle) {

    float c = cos(angle);
    float s = sin(angle);

    vector->d = vector->a * c + vector->b * s;
    vector->q = - vector->a * s + vector->b * c;
};

void dq_ab(vec* vector, float angle) {

    float c = cos(angle);
    float s = sin(angle);

    vector->a = vector->d * c - vector->q * s;
    vector->b = vector->d * s + vector->q * c;
};

void ab_ABC(vec* vector) {

    vector->A = vector->a;
    vector->B = 0.5 *(-vector->a + 1.7320508075  *vector->b);
    vector->C = 0.5 *(-vector->a - 1.7320508075 *vector->b);
};