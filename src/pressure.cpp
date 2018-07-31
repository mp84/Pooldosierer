#include "pressure.h"

pressure_t pressure;

void getPressure() {
        pressure.value = map( analogRead(PIN_PRESSURE),125,730,0,180) / 100.0;
        if (pressure.value < 0) { pressure.value = 0.00; };
};
