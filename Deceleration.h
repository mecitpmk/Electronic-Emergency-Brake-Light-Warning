#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define DECEL_ARR_LENGTH 10

class Deceleration
{
    public:
        float decelArr[ DECEL_ARR_LENGTH ] = { 0.0f };
        uint8_t idx         = 0;
        float current_decel = 0.0f;
        float last_decel    = 0.0f;

        Deceleration(){};

        void updateDecel( float decel );
        
        float getRateOfChange( float dt );
        float getSpeed( float dt );

};