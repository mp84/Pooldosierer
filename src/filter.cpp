#include "filter.h"

filter_mode_e FMODE;
filter_status_e FSTATUS;
filter_s filter;

void setFilter() {

        switch (FMODE) {

        case FM_AUTO:

                if (filter.remote == ON && digitalRead(PIN_FILTER) == OFF) {
                        filter.startTime = millis();
                        digitalWrite(PIN_FILTER, ON);
                        lcd.backlight();
                        filter.active = TRUE;
                };

                if (filter.remote == OFF && digitalRead(PIN_FILTER) == ON) {
                        digitalWrite(PIN_FILTER, OFF);
                        lcd.noBacklight();
                        filter.active = FALSE;
                };

                break;

        case FM_PERM_ON:
                if (digitalRead(PIN_FILTER) == OFF) {
                        filter.startTime = millis();
                        digitalWrite(PIN_FILTER, ON);
                        lcd.backlight();
                        filter.active = TRUE;
                };

                break;

        case FM_PERM_OFF:
                if (digitalRead(PIN_FILTER) == ON) {
                        digitalWrite(PIN_FILTER, OFF);
                        lcd.noBacklight();
                        filter.active = FALSE;
                };

                break;
        };
};
