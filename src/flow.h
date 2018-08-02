#include "includes.h"

#ifndef FLOW_H
#define FLOW_H

struct flow_t {
        float value;              //how much liquid flow do we have
        float setPoint;           //value for flowrate
        float calibration;        //how many pulses per second fot 1l per hour
        unsigned long lastMillis;
        float pulses;
        bool status;
};

extern flow_t flow;

void getFlow();
void incrementPulse();

#endif
