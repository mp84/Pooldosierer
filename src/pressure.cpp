#include "pressure.h"

pressure_t pressure;

void getPressure() {
        pressure.value = map( analogRead(PIN_PRESSURE_READ),pressure.cal0,pressure.cal1,0,100) / 100.0;
        if (pressure.value < 0) { pressure.value = 0.00; };
};
