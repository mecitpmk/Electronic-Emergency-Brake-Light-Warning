#include "Car.h"



void Car::initAllc( float positions , float speeds , float brakePosition )
{
    this->position.updatePos( positions );
    this->speed.updateSpeed( speeds );
    this->brakePos.updateBrake( brakePosition );
    this->decel.updateDecel( PEDAL_DECEL_CORRELATION( brakePosition ) );
    
}


/*
    -> brakePosition in terms of %0-100
    -> sensorsRead in every 200ms = 0.2 sec  
    
    if  [ speed             is NegativeSlope ( Decreasing )
          deceleration      is PositiveSlope ( Increasing )
          brake Pedal Pos   is PositiveSlope ( Increasing )
        ]
        second Protection :
            if the driver press pedal position >= 50
                STATE     =>EMERGENCY
    OR
        IF THE BRAKE PEDAL POSITION MAXIMUM!
        STATE     => MAXIMUM EMERGENCY!
    ELSE
        STATE     => NO WARNING!

    

*/
void Car::readBrakePos( float brakePosition ) // 
{
    if ( brakePosition > 0.0f ) // if brake pedal has been pressed.
    {
        brakePos.updateBrake( brakePosition );
        decel.updateDecel( PEDAL_DECEL_CORRELATION( brakePosition ) );
        speed.updateSpeed( decel.getSpeed( FLOAT_SENSOR_READ_TIME ) );
        position.updatePos( speed.getPosition( FLOAT_SENSOR_READ_TIME ) );

        if ( 
             ( speed.getRateOfChange( FLOAT_SENSOR_READ_TIME )    < 0 ) &&
             ( decel.getRateOfChange( FLOAT_SENSOR_READ_TIME )    > 0 ) && 
             ( brakePos.getRateOfChange( FLOAT_SENSOR_READ_TIME ) > 0 )
           )
        {
            
            /*
                May the driver normally press the brake pedal.
                    So to prevent informative WARNING;
                    I put the EMERGENCY Brake Pedal Limit.
                    if the driver suddenly press the brake pedal EMERGENCY will be activated.
            */
            if ( brakePos.getRateOfChange( FLOAT_SENSOR_READ_TIME ) >= BRAKE_PEDAL_LIMIT )
            {
                eebl = EEBL::EMERGENCY;
            }
            
        }   
        else if ( brakePos.current_brake == MAX_BRAKE )
        {
            eebl = EEBL::MAX_EMERGENCY;
        }
        else
        {
            eebl = EEBL::NO_WARNING;
        }
    }
    else
    {
        eebl = EEBL::NO_WARNING;
    }
}



/*
    Calculate Package CRC for module 255.
        The reason: If the CRC wrong, Follower sends message over network and the Source car will transmit message again.

*/
static uint8_t calculateCRC( DriverWarning& warningsys )
{
    uint32_t tempCRC = 0;
    for ( uint8_t i = 0; i < ( sizeof( warningsys ) - sizeof( warningsys.crc ) ) ; i++ )
    {
        tempCRC += warningsys.u8_array[ i ];
    }
    return ( uint8_t )tempCRC;
}

/*
    After sensor read break Position, emergencyBreakControl mechanism will work.
        If the EEBL situation happened, whole necessary informations will be going to copy to the u8 array.
        Otherwise DO NOTHING.
*/
void Car::emergencyBreakControl()
{
    switch ( eebl )
    {

        case EEBL::MAX_EMERGENCY:
        case EEBL::EMERGENCY:
        {
            WarnerSystem.deceleration   = decel.current_decel;
            WarnerSystem.speed          = speed.current_speed;
            WarnerSystem.position       = position.current_pos;
            WarnerSystem.warning        = eebl;
            WarnerSystem.crc            = calculateCRC( WarnerSystem );
            sendDataOverNETWORK( WarnerSystem.u8_array, sizeof( WarnerSystem ) );
            break;
        }
            

        case EEBL::NO_WARNING:
        default:
        {
            break;
        }
            
    }
}