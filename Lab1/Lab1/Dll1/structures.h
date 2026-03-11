#pragma once
#ifndef STRUCTURES.H
#define STRUCTURES.H

typedef struct {
    float Kp;
    float Ki;
    float Kd;
    
    float max;
    float min;

    float eps;

    float integ;
    float eps_prev;

    float dif;

    float out;

}pid_reg;

#endif