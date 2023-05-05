#include "PinHandler.h"

void __pin_setup(void) {

#ifdef _Buzzer
    pinMode(pinBuzzerSIG, OUTPUT);
    digitalWrite(pinBuzzerSIG, LOW);
#endif

#ifdef _Led_group
    for (uint8_t i = 0; i < 7; ++i) {
        pinMode(pinLedGroup[i], OUTPUT);
    }
#endif

#ifdef _Button_group
    for (uint8_t i = 0; i < 3; ++i) {
        pinMode(pinButtonGroup[i], INPUT_PULLUP);
    }
#endif

    Serial.println("[Pin] Done!");
}
