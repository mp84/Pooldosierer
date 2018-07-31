#include "includes.h"

#ifndef CONFIG_H
#define CONFIG_H


#define PIN_BTN_UP 7
#define PIN_BTN_DN 3
#define PIN_BTN_OK 4
#define PIN_BTN_CN 5


#define PIN_PH_READ 99
#define PIN_CL_READ 99
#define PIN_PH_PUMP 99
#define PIN_CL_PUMP 99
#define PIN_FLOW 2
#define PIN_PRESSURE A0

#define PIN_FILTER 10

#define LCDADDR 0x27
#define LCDCHARS 20
#define LCDLINES 4

#define PIN_LED 6
#define LED_BRIGHTNESS 50
#define HB_DELAY 40

#define TYPEMATIC_DELAY 500

#define PRESSURE_MIN 0.3

#define DELAY_AFTER_START 120000UL          //delay after filter start

#define PH_DELAY 1000UL*60UL*60UL           //60 minutes
#define PH_TO_REDOX_DELAY 1000UL*60UL*10UL  //10 minutes

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0

#endif
