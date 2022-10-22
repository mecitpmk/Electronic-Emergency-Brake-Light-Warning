#include "Position.h"



void Position::updatePos( float position )
{
    this->posArr[ this->idx ] = position;
    this->last_pos            = this->current_pos;
    this->current_pos         = position;
    if ( this->idx == POS_ARR_LENGTH-1 )
    {
        this->idx = 0;
    }
    else
    {
        this->idx++;
    }
}


float Position::getRateOfChange( float dt ) // decel.
{
    return  ( current_pos  - last_pos ) / dt;
}