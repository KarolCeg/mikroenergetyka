#pragma once
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void PID_CALC(pid_reg* a, float b);

void ABC_ab(vec* vector);



void ab_dq(vec* vector, float angle);

void dq_ab(vec* vector, float angle);

void ab_ABC(vec* vector);
#endif