#include "includes.h"

#ifndef STRUCTS_H
#define STRUCTS_H

struct parameters_t {
        float value;              //actual sensor value
        float setPoint;           //where value should be
        bool status;              //is this within our range?
        unsigned long startzeit; //start time of pump
        unsigned long laufzeit;   //calculated end time of pump
        unsigned long lastRun;    //last runtime of pump
        unsigned long delay;       //how much delay since last run
        unsigned int runtimePerUnit; //how long does it take to pump one "unit" of fluid
        float unitsToPump;        //how many units should we pump
        bool clearToPump;         //are we cleared to pump
        bool active;              //should we pump?
};






extern parameters_t ph;
extern parameters_t redox;


#endif
