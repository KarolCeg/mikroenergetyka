// dllmain.cpp : Definiuje punkt wejścia dla aplikacji DLL.
#include "pch.h"
#include "DllHeader.h"
#include "math.h"

#include "constants.h"
#include "structures.h"
#include "functions.h"
#include "global_var.h"

DLLEXPORT void plecsSetSizes(struct SimulationSizes* aSizes)
{
    aSizes->numInputs = 6; //number of inputs
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


    is.A = aState->inputs[2];
    is.B = aState->inputs[3];
    is.C = aState->inputs[4];

    float Udc = aState->inputs[5];


    static float rotor_flux_angle = 0.0;

    ABC_ab(&is); 
    ab_dq(&is,rotor_flux_angle);


    ///////////////////////////////////////////////////////////
    //SPEED CONTROLLER

    PID_CALC(&n_reg, (n_ref - n_meas));

    ///////////////////////////////////////////////////////////
    
     ///////////////////////////////////////////////////////////
    //id CONTROLLER

    PID_CALC(&isd_reg, (10.85 - is.d));

    ///////////////////////////////////////////////////////////
     ///////////////////////////////////////////////////////////
    //iq CONTROLLER

    PID_CALC(&isq_reg, (n_reg.out - is.q)); //tu ma wpisane d zamiast q

    ///////////////////////////////////////////////////////////
    
    //SET OUTPUT VALUES

    us.d = isd_reg.out;
    us.q = isq_reg.out;

    dq_ab(&us, rotor_flux_angle);
    ab_ABC(&us);

    aState->outputs[0] =  us.A/Udc + 0.5; //Output 1
    aState->outputs[1] =  us.B / Udc + 0.5; //Output 2
    aState->outputs[2] =  us.C / Udc + 0.5; //Output 3

};
