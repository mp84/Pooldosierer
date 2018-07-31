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
        FS_CHECK_FILTER,
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
        bool remote;              //remote value
        bool readyForDosing;      //all parameters good for dosing
        unsigned long startTime;  //filter start time
};

extern filter_s filter;



void setFilter();

#endif
