#include "includes.h"

#ifndef PRESSURE_H
#define PRESSURE_H

struct pressure_t {
        float value;              //how much pressure do we have
        float setPoint;           //value for overpressure
        bool status;              //is this within our range

};

extern pressure_t pressure;

void getPressure();

#endif
