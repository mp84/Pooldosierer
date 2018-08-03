#include "includes.h"

void setup() {

        Serial.begin(115200);
        Serial.print("Initializing...");

        lcd.init();
        lcd.backlight();
        lcd.print("Initializing...");

        FastLED.addLeds<WS2811, PIN_LED, RGB>(leds, 1);

        //maybe needet as initial value
        //ph.lastRun = 5UL * 60UL * 1000UL;


        //This values should come from EEPROM
        ph.setPoint = 7.00;
        ph.runtimePerUnit = 100;
        ph.delay = 60UL * 60UL * 1000UL; //60 minutes

        redox.setPoint = 750.0;
        redox.runtimePerUnit = 100;

        pressure.setPoint = 1.00;
        pressure.min = 0.3;
        pressure.calibration_0bar = 127;
        pressure.calibration_1bar = 730;

        flow.setPoint = 30.0;
        flow.calibration = 7.5;

        filter.grantedStartupTime = 5UL;
        filter.delayAfterStartup = 2UL;  // 2 minutes

        FMODE = FM_AUTO;
        //end of EEPROM values

        //testing values
        filter.active = 0;
        filter.remote = 1;


        pinMode(PIN_BTN_UP, INPUT_PULLUP);
        pinMode(PIN_BTN_DN, INPUT_PULLUP);
        pinMode(PIN_BTN_OK, INPUT_PULLUP);
        pinMode(PIN_BTN_CN, INPUT_PULLUP);
        pinMode(PIN_PRESSURE, INPUT);
        pinMode(PIN_LED, OUTPUT);
        pinMode(PIN_FLOW, INPUT);
        attachInterrupt(PIN_FLOW-2, incrementPulse, RISING);

        buttonUp.begin();
        buttonDown.begin();
        buttonOK.begin();
        buttonCN.begin();

        MENU = WELCOME;

        //remove LEDstate after testing
        LEDSTATE = HB_GREEN;

        randomSeed(analogRead(0));

        lcd.print("done!");
        Serial.println("done!");
};

//int currpress;


void loop() {

        static unsigned long lastMillis = millis();

        if (millis() - lastMillis > 1000) {

                lastMillis = millis();

                ph.value = random(400,1400) / 100.0;
                redox.value = random(600,900);
        };

        getButtons();
        getPressure();
        getFlow();

        setDisplay();
        setLED();


};
