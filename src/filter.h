#include "includes.h"

#ifndef FILTER_H
#define FILTER_H

enum filter_mode_e {
        FM_AUTO,
        FM_PERM_ON,
        FM_PERM_OFF,
};

extern filter_mode_e FMODE;

enum filter_status_e {
        CHECKMODE,
        FS_CHECK_FILTER,
        STARTUP,
        SHUTDOWN,
        FS_CHECK_PH,
        FS_PUMP_PH,
        FS_CHECK_REDOX,
        FS_PUMP_REDOX,
        FS_AUTO_ON, //hb_blue
        FS_AUTO_OFF,//hb_yellow
        FS_PERM_ON, //hb_green
        FS_PERM_OFF,
        FS_ERROR, //falsh_red
};

extern filter_status_e FSTATUS;



struct filter_s {
        bool active;              //are we filtering
        bool remote;              //remote value for FS_AUTO mode
        bool readyForDosing;      //all parameters good for dosing
        unsigned long startupTime; //when did we try to start filter
        unsigned long grantedStartupTime; //how long should we try to get pressure
        unsigned long startTime;  //filter start time


        unsigned long delayAfterStartup;
};

extern filter_s filter;

#endif
