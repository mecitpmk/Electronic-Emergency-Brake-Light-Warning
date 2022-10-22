#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define BRAKE_ARR_LENGTH ( 10 )
#define MAX_BRAKE        ( float )(100.0f)


class BrakePosition
{
    public:
        float brakeArr[ BRAKE_ARR_LENGTH ] = { 0.0f };
        uint8_t idx             = 0;
        float current_brake     = 0.0f;
        float last_brake        = 0.0f;

        BrakePosition(){};

        void updateBrake( float brakePos ); 
        float getRateOfChange( float dt );  
        
};