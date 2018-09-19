#include "statemachine.h"

void statemachine() {

        if (    digitalRead(PIN_FILTER) == ON
                && (pressure.value >= pressure.min)
                && (flow.value >= flow.setPoint - 0.5)
                && (flow.value <=flow.setPoint + 0.5)) {

                filter.readyForDosing = TRUE;
        } else {
                filter.readyForDosing = FALSE;
        };



        switch (FSTATUS) {

        case FS_CHECK:

                if (FMODE == FM_AUTO) {
                        if(filter.remote == TRUE && digitalRead(PIN_FILTER == OFF)) {
                                FSTATUS = FS_STARTUP;
                        };

                        if(filter.remote == FALSE && digitalRead(PIN_FILTER == ON)) {
                                FSTATUS = FS_SHUTDOWN;
                        };
                };

                if(FMODE == FM_PERM_ON && digitalRead(PIN_FILTER == OFF)) {
                        FSTATUS = FS_STARTUP;
                };

                if(FMODE == FM_PERM_OFF && digitalRead(PIN_FILTER == ON)) {
                        FSTATUS = FS_SHUTDOWN;
                };





                break;

        case FS_STARTUP:

                LEDSTATE = HB_YELLOW;
                digitalWrite(PIN_FILTER, ON);
                lcd.backlight();
                filter.startupTime = millis();
                FSTATUS = FS_STARTING;
                break;

        case FS_STARTING:


                if(pressure.value > pressure.min && millis() - filter.startupTime > (filter.delayAfterStartup * 60UL * 1000UL) ) {
                        filter.startTime = millis();
                        filter.active = TRUE;
                        FSTATUS = FS_RUNNING;
                };

                if(millis() - filter.startupTime > (filter.grantedStartupTime * 60UL * 1000UL)) {
                        filter.active = FALSE;
                        FSTATUS = FS_ERROR;
                };

                break;

        case FS_RUNNING:

                LEDSTATE = HB_YELLOW;

                if(pressure.value < pressure.min) {
                        filter.active = FALSE;
                        FSTATUS = FS_CHECK;
                };

                if (filter.readyForDosing = TRUE) {
                        FSTATUS = FS_READY;
                };

                break;

        case FS_READY:

                if(FMODE == FM_AUTO) { LEDSTATE = HB_BLUE; };
                if(FMODE == FM_PERM_ON) { LEDSTATE = HB_GREEN; };

                if(filter.readyForDosing = TRUE) {
                        if(ph.value > ph.setPoint) { FSTATUS = FS_CHECK_PH; };
                        if(ph.value <= ph.setPoint) { FSTATUS = FS_CHECK_REDOX; };
                } else {
                        FSTATUS = FS_RUNNING;
                };


                break;

        case FS_SHUTDOWN:
                digitalWrite(PIN_PH_PUMP, OFF);
                digitalWrite(PIN_REDOX_PUMP, OFF);
                digitalWrite(PIN_FILTER, OFF);
                filter.active = FALSE;

                if(FMODE = FM_AUTO) { FSTATUS = FS_AUTO_OFF; };
                if(FMODE = FM_PERM_OFF) { FSTATUS = FS_PERM_OFF; };


        case FS_AUTO_OFF:
                lcd.noBacklight();
                LEDSTATE = HB_YELLOW;
                FSTATUS = FS_CHECK;
                break;

        case FS_PERM_OFF:
                lcd.noBacklight();
                LEDSTATE = HB_RED;
                FSTATUS = FS_CHECK;
                break;


        case FS_CHECK_PH:

                if(ph.value > ph.setPoint && millis() - ph.lastRun > ph.delay) {

                        ph.runtime    = ((ph.value - ph.setPoint) * 10) * ph.runtimePerUnit * 1000UL;
                        FSTATUS = FS_PUMP_PH;
                } else {
                        FSTATUS = FS_READY;
                }
                break;

        case FS_PUMP_PH:

                LEDSTATE = FLASHING_BLUE;

                if( digitalRead(PIN_PH_PUMP) == OFF ) {
                        ph.starttime = millis();
                        digitalWrite(PIN_PH_PUMP,ON);
                };

                if(millis() - ph.starttime > ph.runtime) {
                        digitalWrite(PIN_PH_PUMP,OFF);
                        ph.lastRun = millis();
                        FSTATUS = FS_CHECK;
                };

                if (filter.readyForDosing != TRUE) {
                        digitalWrite(PIN_PH_PUMP, OFF);
                        ph.lastRun = millis();
                        FSTATUS = FS_CHECK;
                };

                break;

        case FS_PUMP_REDOX:

                LEDSTATE = FLASHING_BLUE;
                break;

        case FS_ERROR:

                LEDSTATE = FLASHING_RED;
                FMODE = FM_PERM_OFF;
                break;
        };
};
