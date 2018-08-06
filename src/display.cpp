#include "display.h"

lcdMenu_e MENU;

LiquidCrystal_I2C lcd(LCDADDR,LCDCHARS,LCDLINES);

byte arrowUp[] = {
        0b00000,
        0b00100,
        0b01110,
        0b10101,
        0b00100,
        0b00100,
        0b00100,
        0b00000
};

byte arrowDn[] = {
        0b00000,
        0b00100,
        0b00100,
        0b00100,
        0b10101,
        0b01110,
        0b00100,
        0b00000
};

unsigned long displayLastUpdate;
unsigned long displayUpdateCycle;
unsigned long longPressLock=0;


void setDisplay() {

        switch(MENU) {

        case STATUS:

                displayUpdateCycle = 1000;

                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PH      : ");
                lcd.setCursor(0, 1);
                lcd.print("Redox   : ");
                lcd.setCursor(0, 2);
                lcd.print("Flow    : ");
                lcd.setCursor(0, 3);
                lcd.print("Pressure: ");

                MENU = STATUS_UPDATE;

                break;

        case STATUS_UPDATE:

                if(millis() - displayLastUpdate > displayUpdateCycle) {
                        displayLastUpdate = millis();

                        lcd.setCursor(10, 0);
                        if(ph.value >= 10) {
                                lcd.print(ph.value,1);
                                //lcd.print(String("  "));
                        } else {
                                lcd.print( String(" ") + String(ph.value) + String("  ") );
                        };

                        //redox value
                        lcd.setCursor(12, 1); lcd.print(redox.value, 0); lcd.print(" mV");

                        lcd.setCursor(9, 2);
                        if(flow.value >= 100) { lcd.print(flow.value,2); };

                        if(flow.value >= 10 && flow.value < 100) {
                                lcd.print(" ");
                                lcd.print(flow.value,2);
                                lcd.print(" L/h");
                        };

                        if (flow.value < 10) {
                                lcd.print("  ");
                                lcd.print(flow.value,2);
                                lcd.print(" L/h");
                        };


                        lcd.setCursor(11, 3); lcd.print(pressure.value); lcd.print(" Bar");

                };

                if (buttonOK.pressedFor(1000)) { MENU = PHSET; };
                if (buttonCN.pressedFor(1000)) { MENU = MANUALMODE; };

                if( buttonUp.isPressed() && buttonDown.isPressed() ) {

                        if ( millis() - longPressLock >= TYPEMATIC_DELAY) {
                                longPressLock = millis();

                                if (FMODE == FM_AUTO) {
                                        filter.remote = !filter.remote;
                                };
                        };
                };


                break;

        case PHSET:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("PH value");
                lcd.setCursor(0, 2);
                lcd.print("Current  :");
                lcd.setCursor(0, 3);
                lcd.print("Setpoint :");

                MENU = PHSET_UPDATE;
                break;

        case PHSET_UPDATE:

                lcd.setCursor(11, 2);
                lcd.print(ph.value);
                lcd.setCursor(11, 3);
                lcd.print(ph.setPoint);



                if (buttonUp.wasPressed())   { ph.setPoint += 0.1; };
                if (buttonUp.pressedFor(TYPEMATIC_DELAY) )  { ph.setPoint += 0.1; };
                if (buttonDown.wasPressed()) { ph.setPoint -= 0.1; };
                if (buttonDown.pressedFor(TYPEMATIC_DELAY) )  { ph.setPoint -= 0.1; };

                if (buttonOK.wasPressed())   { MENU = REDOXSET; };
                if (buttonCN.wasPressed())   { MENU = STATUS; };
                break;

        case REDOXSET:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("REDOX value");
                lcd.setCursor(0, 2);
                lcd.print("Current  :");
                lcd.setCursor(0, 3);
                lcd.print("Setpoint :");
                MENU = REDOXSET_UPDATE;
                break;

        case REDOXSET_UPDATE:

                lcd.setCursor(11, 2);
                lcd.print(redox.value,0);
                lcd.setCursor(11, 3);
                lcd.print(redox.setPoint,0);

                if (buttonUp.wasPressed()) { redox.setPoint += 1.0; };
                if (buttonUp.pressedFor(TYPEMATIC_DELAY) )  { redox.setPoint += 1.0; };

                if (buttonDown.wasPressed()) { redox.setPoint -= 1.0; };
                if (buttonDown.pressedFor(TYPEMATIC_DELAY) )  { redox.setPoint -= 1.0; };


                if (buttonOK.wasPressed())   { MENU = FLOWSET; };
                if (buttonCN.wasPressed())   { MENU = STATUS; };
                break;

        case FLOWSET:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Set FLOWRATE value");
                MENU = FLOWSET_UPDATE;
                break;

        case FLOWSET_UPDATE:
                if (buttonUp.wasPressed())   {  };
                if (buttonDown.wasPressed()) {  };
                if (buttonOK.wasPressed())   { MENU = PRESSURESET; };
                if (buttonCN.wasPressed())   { MENU = STATUS; };
                break;

        case PRESSURESET:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Set PRESSURE value");
                MENU = PRESSURESET_UPDATE;
                break;

        case PRESSURESET_UPDATE:
                if (buttonUp.wasPressed())   {  };
                if (buttonDown.wasPressed()) {  };
                if (buttonOK.wasPressed())   { MENU = FILTERMODE; };
                if (buttonCN.wasPressed()) { MENU = STATUS; };
                break;

        case INFO:
                lcd.clear();
                //MENU = INFO;
                break;

        case WELCOME:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Poolcontrol");
                lcd.setCursor(0, 1);
                lcd.print("");
                lcd.setCursor(0, 2);
                lcd.print("ver. 1.0");
                lcd.setCursor(0, 3);
                lcd.print("Compiled 2018-07-15");
                delay(1000);
                MENU = STATUS;
                break;

        case MANUALMODE:
                lcd.clear();

                lcd.setCursor(0, 0);
                lcd.print("Manual Mode");
                lcd.setCursor(0, 1);
                lcd.print("UP = CL");
                lcd.setCursor(0, 2);
                lcd.print("DOWN = Redox");
                lcd.setCursor(0, 3);
                lcd.print("MENU = PUMP");

                MENU = MANUALMODE_UPDATE;

                break;

        case MANUALMODE_UPDATE:
                if(buttonUp.isPressed()) { digitalWrite(PIN_LED,HIGH); };
                if(buttonDown.isPressed()) { digitalWrite(PIN_LED,HIGH); };
                if(buttonOK.isPressed()) { digitalWrite(PIN_LED,HIGH); };
                if(buttonCN.wasPressed()) { MENU = STATUS; };
                break;

        case FILTERMODE:
                lcd.clear();

                lcd.setCursor(0, 0);
                lcd.print("Filter Mode");
                MENU = FILTERMODE_UPDATE;
                break;

        case FILTERMODE_UPDATE:
                lcd.setCursor(0, 2);

                switch (FMODE) {

                case FM_AUTO:
                        lcd.print("AUTO    ");
                        break;

                case FM_PERM_ON:
                        lcd.print("PERM_ON ");
                        break;

                case FM_PERM_OFF:
                        lcd.print("PERM_OFF");
                        break;
                };


                if ( buttonUp.wasPressed() ) {

                        switch (FMODE) {

                        case FM_AUTO:
                                FMODE = FM_PERM_ON;
                                break;

                        case FM_PERM_ON:
                                FMODE = FM_PERM_OFF;
                                break;

                        case FM_PERM_OFF:
                                FMODE = FM_AUTO;
                                break;

                        };
                };

                if ( buttonDown.wasPressed() ) {

                        switch (FMODE) {

                        case FM_AUTO:
                                FMODE = FM_PERM_OFF;
                                break;

                        case FM_PERM_OFF:
                                FMODE = FM_PERM_ON;
                                break;

                        case FM_PERM_ON:
                                FMODE = FM_AUTO;
                                break;

                        };
                };

                if (buttonOK.wasPressed())   { MENU = LEDTEST; };
                if (buttonCN.wasPressed()) { MENU = STATUS; };


                break;

        case LEDTEST:
                lcd.clear();

                lcd.setCursor(0, 0);
                lcd.print("LED Test");
                MENU = LEDTEST_UPDATE;
                break;


        case LEDTEST_UPDATE:

                lcd.setCursor(0, 2);

                switch (LEDSTATE) {

                case HB_GREEN:
                        lcd.print("HB_GREEN       ");
                        break;
                case FLASHING_GREEN:
                        lcd.print("FLASHING_GREEN ");
                        break;
                case HB_YELLOW:
                        lcd.print("HB_YELLOW      ");
                        break;

                case FLASHING_YELLOW:
                        lcd.print("FLASHING_YELLOW");
                        break;
                case HB_RED:
                        lcd.print("HB_RED         ");
                        break;

                case FLASHING_RED:
                        lcd.print("FLASHING_RED   ");
                        break;

                case HB_BLUE:
                        lcd.print("HB_BLUE        ");
                        break;

                case FLASHING_BLUE:
                        lcd.print("FLASHING_BLUE  ");
                        break;

                };

                if (buttonUp.wasPressed())   {
                        switch (LEDSTATE) {

                        case HB_GREEN:
                                LEDSTATE = FLASHING_GREEN;
                                break;

                        case FLASHING_GREEN:
                                LEDSTATE = HB_YELLOW;
                                break;

                        case HB_YELLOW:
                                LEDSTATE = FLASHING_YELLOW;
                                break;

                        case FLASHING_YELLOW:
                                LEDSTATE = HB_BLUE;
                                break;

                        case HB_BLUE:
                                LEDSTATE = FLASHING_BLUE;
                                break;

                        case FLASHING_BLUE:
                                LEDSTATE = HB_RED;
                                break;

                        case HB_RED:
                                LEDSTATE = FLASHING_RED;
                                break;

                        case FLASHING_RED:
                                LEDSTATE = HB_GREEN;
                                break;
                        }
                };
                if (buttonDown.wasPressed()) {  };
                if (buttonOK.wasPressed())   { MENU = PHSET; };
                if (buttonCN.wasPressed()) { MENU = STATUS; };
                break;

        case PRESSURE_CALIBRATION:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Calibrate PRESSURE");
                lcd.setCursor(0, 1);
                lcd.write(1);
                lcd.print("=0Bar ");
                lcd.write(0);
                lcd.print("=1Bar ");
                lcd.setCursor(0, 2);
                lcd.print("Analog value:");
                lcd.setCursor(0, 3);
                lcd.print("Setpoint:");
                MENU = PRESSURE_CALIBRATION_UPDATE;
                break;

        case PRESSURE_CALIBRATION_UPDATE:

                if(millis() - displayLastUpdate > 1000) {
                        displayLastUpdate = millis();
                        lcd.setCursor(14, 2);
                        lcd.print("      ");
                        lcd.setCursor(14, 2);
                        lcd.print(analogRead(PIN_PRESSURE_READ));
                        lcd.setCursor(10,3);
                        lcd.print("          ");
                        lcd.setCursor(10,3);
                        lcd.print(pressure.cal0);
                        lcd.print(" / ");
                        lcd.print(pressure.cal1);
                };

                if(buttonUp.pressedFor(1000)) { pressure.cal1 = analogRead(PIN_PRESSURE_READ); };
                if(buttonDown.pressedFor(1000)) { pressure.cal0 = analogRead(PIN_PRESSURE_READ); };


                break;

        case FLOW_CALIBRATION:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Calibrate FLOW");
                lcd.setCursor(0, 1);
                lcd.print("pulses/s for 1L/h");
                lcd.setCursor(0, 3);
                lcd.print("Pulses:");

                MENU = FLOW_CALIBRATION_UPDATE;

                break;

        case FLOW_CALIBRATION_UPDATE:

                lcd.setCursor(8, 3);
                lcd.print(flow.calibration);

                if(buttonUp.wasPressed()) { flow.calibration += 0.1; };
                if(buttonDown.wasPressed()) { flow.calibration -= 0.1; };

                if (buttonUp.pressedFor(TYPEMATIC_DELAY) )  { flow.calibration += 0.1; };
                if (buttonDown.pressedFor(TYPEMATIC_DELAY) )  { flow.calibration -= 0.1; };

                if(flow.calibration < 0) { flow.calibration = 0; };

                break;

        case PH_CALIBRATION:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("Calibrate PH");
                lcd.setCursor(0, 1);
                lcd.write(1);
                lcd.print("=PH4 ");
                lcd.write(0);
                lcd.print("PH7 ");
                lcd.setCursor(0, 2);
                lcd.print("Analog value:");
                lcd.setCursor(0, 3);
                lcd.print("Setpoint:");
                MENU = PH_CALIBRATION_UPDATE;
                break;

        case PH_CALIBRATION_UPDATE:
                if(millis() - displayLastUpdate > 1000) {
                        displayLastUpdate = millis();
                        lcd.setCursor(14, 2);
                        lcd.print("      ");
                        lcd.setCursor(14, 2);
                        lcd.print(analogRead(PIN_PH_READ));
                        lcd.setCursor(10,3);
                        lcd.print("          ");
                        lcd.setCursor(10,3);
                        lcd.print(ph.cal4);
                        lcd.print(" / ");
                        lcd.print(ph.cal7);
                };

                if(buttonUp.pressedFor(1000)) { ph.cal7 = analogRead(PIN_PRESSURE_READ); };
                if(buttonDown.pressedFor(1000)) { ph.cal4 = analogRead(PIN_PRESSURE_READ); };

                break;

        case REDOX_CALIBRATION:

                break;

        case REDOX_CALIBRATION_UPDATE:

                break;

        default:
                MENU = STATUS;
                break;

        }

}
