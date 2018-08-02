#include "buttons.h"

Button buttonUp(PIN_BTN_UP);
Button buttonDown(PIN_BTN_DN);
Button buttonOK(PIN_BTN_OK);
Button buttonCN(PIN_BTN_CN);

void getButtons() {
        buttonUp.read();
        buttonDown.read();
        buttonOK.read();
        buttonCN.read();
};
