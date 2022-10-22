#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define SPEED_ARR_LENGTH 10


class Speed
{
    public:
        float speedArr[ SPEED_ARR_LENGTH ] = { 0.0f };
        uint8_t idx         = 0;
        float current_speed = 0.0f;
        float last_speed    = 0.0f;

        Speed(){};

        void updateSpeed( float speed );
        
        float getRateOfChange( float dt );

        float getPosition( float dt );
};

