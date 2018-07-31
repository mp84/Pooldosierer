#include "statemachine.h"

void statemachine() {

        switch (FSTATUS) {

        case FS_CHECK_FILTER:

                if (digitalRead(PIN_FILTER) == OFF) {
                        if (FMODE == FM_PERM_OFF) { FSTATUS = FS_PERM_OFF; };
                        if (FMODE == FM_AUTO) { FSTATUS = FS_AUTO_OFF; };
                };

                if (    digitalRead(PIN_FILTER) == ON
                        && (pressure.value >= PRESSURE_MIN)
                        && (flow.value >= flow.setPoint - 0.5)
                        && (flow.value <=flow.setPoint + 0.5)
                        && (millis() - filter.startTime > DELAY_AFTER_START)) {

                        filter.readyForDosing = TRUE;

                        if (FMODE == FM_AUTO)    { FSTATUS = FS_AUTO_ON; };
                        if (FMODE == FM_PERM_ON) { FSTATUS = FS_PERM_ON; };
                } else {
                        filter.readyForDosing = FALSE;
                        LEDSTATE = HB_YELLOW;
                };

                break;

        case FS_AUTO_ON:

                LEDSTATE = HB_BLUE;
                FSTATUS = FS_CHECK_PH;
                break;

        case FS_PERM_ON:

                LEDSTATE = HB_GREEN;
                FSTATUS = FS_CHECK_PH;
                break;

        case FS_AUTO_OFF:

                LEDSTATE = HB_YELLOW;
                FSTATUS = FS_CHECK_FILTER;
                break;

        case FS_PERM_OFF:

                LEDSTATE = HB_RED;
                FSTATUS = FS_CHECK_FILTER;
                break;


        case FS_CHECK_PH:

                if(ph.value > ph.setPoint && millis() - ph.lastRun > PH_DELAY) {

                        ph.unitsToPump = (ph.value - ph.setPoint) * 10;
                        ph.laufzeit    = (ph.runtimePerUnit * ph.unitsToPump) * 1000UL;
                        FSTATUS = FS_PUMP_PH;
                } else {
                        FSTATUS = FS_CHECK_REDOX;
                }
                break;

        case FS_PUMP_PH:

                LEDSTATE = FLASHING_YELLOW;

                if (filter.readyForDosing != TRUE) {
                        digitalWrite(PIN_PH_PUMP, OFF);
                        FSTATUS = FS_CHECK_FILTER;
                };

                if( digitalRead(PIN_PH_PUMP) == OFF ) {
                        ph.startzeit = millis();
                        digitalWrite(PIN_PH_PUMP,ON);
                };

                if(millis() - ph.startzeit > ph.laufzeit) {
                        digitalWrite(PIN_PH_PUMP,OFF);
                        ph.lastRun = millis();
                        FSTATUS = FS_CHECK_FILTER;
                }
                break;





        case FS_PUMP_REDOX:

                LEDSTATE = FLASHING_YELLOW;
                break;

        case FS_ERROR:

                LEDSTATE = FLASHING_RED;
                FMODE = FM_PERM_OFF;
                break;
        }

        //check and set status


        if(filter.active == TRUE &&
           (pressure.value >= PRESSURE_MIN) &&
           flow.status == TRUE &&
           millis() - ph.lastRun > PH_DELAY) {
                ph.clearToPump = TRUE;
        } else {
                ph.clearToPump = FALSE;
        };

        if(filter.active == TRUE &&
           (pressure.value >= PRESSURE_MIN) &&
           flow.status == TRUE &&
           ph.status == TRUE &&
           millis() - ph.lastRun > PH_TO_REDOX_DELAY) {
                redox.clearToPump = TRUE;
        } else {
                redox.clearToPump = FALSE;
        }
}
