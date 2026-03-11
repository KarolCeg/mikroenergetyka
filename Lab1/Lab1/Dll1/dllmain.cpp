// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include "DllHeader.h"
#include "math.h"

#include "constants.h"
#include "structures.h"
#include "function.h"

#include "global_vars.h"


DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
    aSizes->numInputs = 2; //number of inputs
    aSizes->numOutputs = 3; //number of outputs
    aSizes->numStates = 0; //number of states
    aSizes->numParameters = 0; //number of parameters
};

DLLEXPORT void plecsOutput(struct SimulationState* aState)
{
    ///////////////////////////////////////////////////////////
    //READ INPUT VALUES

    float n_ref = aState->inputs[0];
    float n_meas = aState->inputs[1];


    ///////////////////////////////////////////////////////////
    //SPEED CONTROLLER

    PID_CALC(&n_reg, (n_ref - n_meas));

    ///////////////////////////////////////////////////////////
    //ANGLE GENERATOR

    

    float f = n_reg.out ;
 
    static float angle = 0.0;
    angle += TWO_Pi * f * Ts;
    if (angle >= TWO_Pi) angle -= TWO_Pi;
    if (angle <= -TWO_Pi) angle += TWO_Pi;

    ///////////////////////////////////////////////////////////
    //SCALAR CONTROL

    float m = fabs(0.02 * f) + 0.001;
    if (m > 1) m = 1;
    if (m < 0.001) m = 0.001;

    ///////////////////////////////////////////////////////////
    //SET OUTPUT VALUES

    aState->outputs[0] = 0.5 * m*sin(angle) + 0.5; //Output 1
    aState->outputs[1] = 0.5 * m*sin(angle- TWO_Pi3) + 0.5; //Output 2
    aState->outputs[2] = 0.5 * m*sin(angle+ TWO_Pi3) + 0.5; //Output 3

};