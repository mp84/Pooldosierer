#include "ph.h"

parameters_ph_t ph;

void getPH() {

        ph.value = map(analogRead(PIN_PH_READ),ph.cal4,ph.cal7,400,700) / 100.0;
        if(ph.value < 0 || ph.value > 14) {ph.value = 0.00; };

};
