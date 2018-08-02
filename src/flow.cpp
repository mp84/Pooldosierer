#include "flow.h"

flow_t flow;

void getFlow() {

        if(millis() - flow.lastMillis > 1000) {
                flow.lastMillis = millis();

                flow.value = (flow.pulses * 60.00 / flow.calibration);
                if (flow.value > 999.0) {flow.value = 999.0; };
                flow.pulses = 0.00;
        };
};

void incrementPulse() {
        flow.pulses += 1.0;
};
