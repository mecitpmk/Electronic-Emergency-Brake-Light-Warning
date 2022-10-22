#include "BrakePosition.h"


void BrakePosition::updateBrake( float brakePos )
{
    this->brakeArr[ this->idx ] = brakePos;
    this->last_brake            = this->current_brake;
    this->current_brake         = brakePos;
    if ( this->idx == BRAKE_ARR_LENGTH-1 )
    {
        this->idx = 0;
    }
    else
    {
        this->idx++;
    }
}


float BrakePosition::getRateOfChange( float dt )
{
    return  ( current_brake - last_brake ) / dt;
}

