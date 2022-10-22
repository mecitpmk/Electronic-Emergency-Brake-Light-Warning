#pragma once
#include "BrakePosition.h"
#include "Deceleration.h"
#include "Speed.h"
#include "Position.h"
#include "Networkh.h"

#define SENSOR_READ_TIME        ( 200 ) // 200 ms
#define FLOAT_SENSOR_READ_TIME  ( float )( SENSOR_READ_TIME / 1000 ) // 0.2 sec
#define BRAKE_PEDAL_LIMIT       ( float )( 50.0f )                   // %50 Pedal Limit


#define PEDAL_DECEL_CORRELATION(brake) (float)( brake / 10 )  // %100 Pedal Press = 10 m/s^2 deceleration.



enum class EEBL : uint8_t
{
    NO_WARNING,
    EMERGENCY,
    MAX_EMERGENCY,
};


union DriverWarning
{
    struct
    {

        float           speed;          // in terms of km/h
        float           deceleration;   // in terms of m/s² 
        float           position;       // in terms of z = √x²+y²
        EEBL            warning;
        uint8_t crc;
    };

    uint8_t u8_array[ 1 ]; // Because of the structure length > u8_array , this array length = sizeof(structure)
};


class Car
{
    public:
        Deceleration  decel                 = Deceleration();
        BrakePosition brakePos              = BrakePosition();
        Speed         speed                 = Speed();
        Position      position              = Position();
        EEBL          eebl                  = EEBL::NO_WARNING;
        union DriverWarning WarnerSystem    = { 0 };

        Car(){};

        void initAllc( float positions , float speeds , float brakePosition );
        void readBrakePos( float brakePosition );
        void emergencyBreakControl();
        
};