#include "pch.h"
#include "math.h"

#include "constants.h"
#include "structures.h"

void PID_CALC(pid_reg *a, float b) { // * oznacza do tej funkcji nie chcemy przesylac calej struktury tylko odnosnik do miejsca w pamieci
  
     a->eps = a->Kp * b;


    a->integ += a->Ki * 0.5 * (a->eps + a->eps_prev) * Ts;
    if (a->integ > a->max) a->integ = a->max;
    if (a->integ < a->min) a->integ = a->min;

    a->dif = a->Kd * (a->eps - a->eps_prev) * Fs;

    a->out = a->eps + a->integ + a->dif;
    a->eps_prev = a->eps;

    if (a->out > a->max)  a->out = a->max;
    if (a->out < a->min)  a->out = a->min;
};