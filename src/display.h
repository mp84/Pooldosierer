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
        INFO,
};

extern lcdMenu_e MENU;
extern LiquidCrystal_I2C lcd;


void setDisplay();

#endif
