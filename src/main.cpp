#include "includes.h"

Button buttonUp(PIN_BTN_UP);
Button buttonDown(PIN_BTN_DN);
Button buttonOK(PIN_BTN_OK);
Button buttonCN(PIN_BTN_CN);

//CRGB leds[1];

void setup() {

        lcd.init();
        lcd.backlight();
        lcd.print("Initializing...");

        FastLED.addLeds<WS2811, PIN_LED, RGB>(leds, 1);

        ph.lastRun = 5UL * 60UL * 1000UL;
        ph.delay = 60UL * 60UL * 1000UL;

        ph.setPoint = 7.00;
        redox.setPoint = 750.0;

        filter.active = 0;
        filter.remote = 1;


        Serial.begin(115200);
        Serial.print("Initializing...");

        pinMode(PIN_BTN_UP, INPUT_PULLUP);
        pinMode(PIN_BTN_DN, INPUT_PULLUP);
        pinMode(PIN_BTN_OK, INPUT_PULLUP);
        pinMode(PIN_BTN_CN, INPUT_PULLUP);
        pinMode(PIN_PRESSURE, INPUT);



        buttonUp.begin();
        buttonDown.begin();
        buttonOK.begin();
        buttonCN.begin();

        pinMode(PIN_LED, OUTPUT);

        lcd.print("done!");
        Serial.println("done!");

        randomSeed(analogRead(0));

        MENU = WELCOME;
        FMODE = FM_AUTO;
        LEDSTATE = HB_GREEN;

        pinMode(PIN_FLOW, INPUT);
        attachInterrupt(PIN_FLOW-2, incrementPulse, RISING);

};

int currpress;


void loop() {

        static unsigned long lastMillis = millis();

        if (millis() - lastMillis > 1000) {

                lastMillis = millis();

                ph.value = random(400,1400) / 100.0;
                redox.value = random(600,900);
                //flow.value = random(900,1100) / 100.0;
                //pressure.value = random(50,150) / 100.0;

        };

        readButtons();
        updateDisplay();
        readPH();
        calculatePH();
        pumpPH();
        setFilter();
        led();
        getPressure();
        calculateFlow();
};
