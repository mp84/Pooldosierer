#include "flow.h"

flow_t flow;

void calculateFlow() {

        if(millis() - flow.lastMillis > 1000) {
                flow.lastMillis = millis();

                flow.value = (flow.pulses * 60.00 / 7.50);
                if (flow.value > 999.0) {flow.value = 999.0; };
                flow.pulses = 0.00;
        };
};

void incrementPulse() {
        flow.pulses += 1.0;
};
