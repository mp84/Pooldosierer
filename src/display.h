#include "includes.h"

#ifndef DISPLAY_H
#define DISPLAY_H

extern unsigned long displayLastUpdate;
extern unsigned long displayUpdateCycle;

enum lcdMenu_e {
        WELCOME,
        STATUS,
        STATUS_UPDATE,
        PHSET,
        PHSET_UPDATE,
        REDOXSET,
        REDOXSET_UPDATE,
        FLOWSET,
        FLOWSET_UPDATE,
        PRESSURESET,
        PRESSURESET_UPDATE,
        MANUALMODE,
        MANUALMODE_UPDATE,
        FILTERMODE,
        FILTERMODE_UPDATE,
        LEDTEST,
        LEDTEST_UPDATE,
        PRESSURE_CALIBRATION,
        PRESSURE_CALIBRATION_UPDATE,
        FLOW_CALIBRATION,
        FLOW_CALIBRATION_UPDATE,
        PH_CALIBRATION,
        PH_CALIBRATION_UPDATE,
        REDOX_CALIBRATION,
        REDOX_CALIBRATION_UPDATE,
        INFO,
};

extern lcdMenu_e MENU;
extern LiquidCrystal_I2C lcd;

extern byte arrowUp[];
extern byte arrowDn[];


void setDisplay();

#endif
