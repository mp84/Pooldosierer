#include "pressure.h"

pressure_t pressure;

void getPressure() {
        pressure.value = map( analogRead(PIN_PRESSURE),pressure.calibration_0bar,pressure.calibration_1bar,0,100) / 100.0;
        if (pressure.value < 0) { pressure.value = 0.00; };
};
