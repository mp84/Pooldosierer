#include "includes.h"

#ifndef DISPLAY_H
#define DISPLAY_H

extern unsigned long displayLastUpdate;
extern unsigned long displayUpdateCycle;

enum lcdMenu_e {
        // Welcome and homescreen
        WELCOME,
        WELCOME_UPDATE,
        HOME,
        HOME_UPDATE,

        //USER settings
        FILTERMODE,
        FILTERMODE_UPDATE,
        PHSET,
        PHSET_UPDATE,
        REDOXSET,
        REDOXSET_UPDATE,
        PRESSURESET,
        PRESSURESET_UPDATE,
        FLOWSET,
        FLOWSET_UPDATE,
        INFO,
        INFO_UPDATE,

        //CALIBRATION settings
        PH_CALIBRATION,
        PH_CALIBRATION_UPDATE,
        REDOX_CALIBRATION,
        REDOX_CALIBRATION_UPDATE,
        PRESSURE_CALIBRATION,
        PRESSURE_CALIBRATION_UPDATE,
        FLOW_CALIBRATION,
        FLOW_CALIBRATION_UPDATE,

        //DEBUG menu
        RAW_VALUES,
        RAW_VALUES_UPDATE,
        MANUALMODE,
        MANUALMODE_UPDATE,
        LEDTEST,
        LEDTEST_UPDATE,
};

extern lcdMenu_e MENU;
extern LiquidCrystal_I2C lcd;

extern byte arrowUp[];
extern byte arrowDn[];


void setDisplay();

#endif
