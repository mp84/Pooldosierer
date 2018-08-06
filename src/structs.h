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
        int calph4;                   //analog read at PH 4
        int claph7;                   //analog read at PH 7
        bool active;                  //is pumping active?
};


extern parameters_t redox;

#endif
