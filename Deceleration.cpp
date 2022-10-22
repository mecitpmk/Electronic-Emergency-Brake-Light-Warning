#include "Deceleration.h"


void Deceleration::updateDecel( float decel )
{
    this->decelArr[ this->idx ] = decel;
    this->last_decel            = this->current_decel;
    this->current_decel         = decel;
    if ( this->idx == DECEL_ARR_LENGTH-1 )
    {
        this->idx = 0;
    }
    else
    {
        this->idx++;
    }
}


float Deceleration::getRateOfChange( float dt )
{
    return  ( current_decel - last_decel ) / dt;
}

float Deceleration::getSpeed( float dt )
{
    return current_decel * dt;
}
