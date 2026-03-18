#pragma once
#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    float Kp;
    float Ki;
    float Kd;

    float max;
    float min;

    float eps;
    float eps_prev;

    float integ;
    float dif;
    
    float out;

} pid_reg;


typedef struct {
    float A;
    float B;
    float C;

    float a;
    float b;

    float d;
    float q;

 

} vec;

#endif