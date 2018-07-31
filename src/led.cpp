#include "led.h"

ledstate_e LEDSTATE;
CRGB leds[1];

void led() {

        static unsigned long lastMillis;
        static int i                = LED_BRIGHTNESS;

        switch (LEDSTATE) {

        case HB_GREEN:

                if(millis() - lastMillis > HB_DELAY) {
                        if (i > 0) {
                                leds[0] = CRGB(i,0,0);
                                FastLED.show();
                                i--;
                                lastMillis = millis();
                        } else {
                                i = LED_BRIGHTNESS;
                        };
                };

                break;

        case FLASHING_GREEN:

                if(millis() - lastMillis > 250) {

                        if (leds[0]) {
                                leds[0] = CRGB(0,0,0);
                                FastLED.show();
                        } else {
                                leds[0] = CRGB(LED_BRIGHTNESS,0,0);
                                FastLED.show();
                        };

                        lastMillis = millis();
                };
                break;

        case HB_YELLOW:

                if(millis() - lastMillis > HB_DELAY) {
                        if (i > 0) {
                                leds[0] = CRGB(i*0.55,i,0);
                                FastLED.show();
                                i--;
                                lastMillis = millis();
                        } else {
                                i = LED_BRIGHTNESS;
                        };
                };
                break;


        case FLASHING_YELLOW:

                if(millis() - lastMillis > 250) {

                        if (leds[0]) {
                                leds[0] = CRGB(0,0,0);
                                FastLED.show();
                        } else {
                                leds[0] = CRGB(LED_BRIGHTNESS*0.55,LED_BRIGHTNESS,0);
                                FastLED.show();
                        };

                        lastMillis = millis();
                };
                break;

        case HB_RED:
                if(millis() - lastMillis > HB_DELAY) {
                        if (i > 0) {
                                leds[0] = CRGB(0,i,0);
                                FastLED.show();
                                i--;
                                lastMillis = millis();
                        } else {
                                i = LED_BRIGHTNESS;
                        };
                };
                break;

        case FLASHING_RED:

                if(millis() - lastMillis > 250) {

                        if (leds[0]) {
                                leds[0] = CRGB(0,0,0);
                                FastLED.show();
                        } else {
                                leds[0] = CRGB(0,LED_BRIGHTNESS,0);
                                FastLED.show();
                        };

                        lastMillis = millis();
                };
                break;

        case HB_BLUE:
                if(millis() - lastMillis > HB_DELAY) {
                        if (i > 0) {
                                leds[0] = CRGB(0,0,i);
                                FastLED.show();
                                i--;
                                lastMillis = millis();
                        } else {
                                i = LED_BRIGHTNESS;
                        };
                };
                break;

        case FLASHING_BLUE:

                if(millis() - lastMillis > 250) {

                        if (leds[0]) {
                                leds[0] = CRGB(0,0,0);
                                FastLED.show();
                        } else {
                                leds[0] = CRGB(0,0,LED_BRIGHTNESS);
                                FastLED.show();
                        };

                        lastMillis = millis();
                };
                break;

        };
};
