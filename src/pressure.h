#include "includes.h"

#ifndef PRESSURE_H
#define PRESSURE_H

struct pressure_t {
        float value;              //how much pressure do we have
        float setPoint;           //value for overpressure
        float min;                //minimum pressure
        bool status;              //is this within our range
        int cal0;                 //analog reading for 0bar
        int cal1;                 //analog reading for 1bar

};

extern pressure_t pressure;

void getPressure();

#endif
