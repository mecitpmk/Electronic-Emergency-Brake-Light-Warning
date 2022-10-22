#include "Speed.h"


void Speed::updateSpeed( float speed )
{
    this->speedArr[ this->idx ] = speed;
    this->last_speed            = this->current_speed;
    this->current_speed         = speed;
    if ( this->idx == SPEED_ARR_LENGTH-1 )
    {
        this->idx = 0;
    }
    else
    {
        this->idx++;
    }
}


float Speed::getRateOfChange( float dt ) // getDeceleration
{
    return  ( current_speed - last_speed ) / dt;
}

float Speed::getPosition( float dt )
{
    return last_speed * dt;
}