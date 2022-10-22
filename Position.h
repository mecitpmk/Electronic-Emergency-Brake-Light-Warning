#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define POS_ARR_LENGTH 10


class Position
{
    public:
        float posArr[ POS_ARR_LENGTH ] = { 0.0f };
        uint8_t idx           = 0;
        float current_pos     = 0.0f;
        float last_pos        = 0.0f;

        Position(){};

        void updatePos( float position ); 
        float getRateOfChange( float dt );  // getSpeed
};