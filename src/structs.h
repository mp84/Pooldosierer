#include "includes.h"

#ifndef STRUCTS_H
#define STRUCTS_H

struct parameters_t {
        float value;                  //actual sensor value
        float setPoint;               //where value should be
        bool status;                  //is this within our range?
        unsigned long delay;          //how much delay after each dosing cycle
        unsigned long starttime;      //start time of pump
        unsigned long runtime;        //calculated end time of pump
        unsigned int runtimePerUnit;  //how long does it take to pump one "unit" of fluid
        unsigned long lastRun;        //last runtime of pump
        //  bool clearToPump;             //are we cleared to pump
        bool active;                  //is pumping active?
};

extern parameters_t ph;
extern parameters_t redox;

#endif
