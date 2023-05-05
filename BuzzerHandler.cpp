#include "BuzzerHandler.h"
#include "ModuleStart.h"
#include "PinHandler.h"

// 1 ~ 7  11 ~ 15
uint16_t frequences[] = {261, 293, 329, 349, 392, 440, 493, 621, 680, 740, 940, 1050};
// uint16_t frequences[] = {595, 661, 700, 786, 882, 990, 1112, 621, 680, 740, 940, 1050};

void __buzzer_play(uint8_t num) {
#ifdef _Buzzer
    // if (1 <= num && num <= 7) {
    //     tone(pinBuzzerSIG, frequences[num - 1], 400);
    // }
    if (6 <= num && num <= 12) {
        // noTone(pinBuzzerSIG);
        delay(10);
        tone(pinBuzzerSIG, frequences[num - 6], 400);
    }
#endif

#ifdef _Show_buzzer_tone
    Serial.print("[Debug] Buzzer idx: ");
    Serial.println(num);
#endif

    // delay(400);
}
