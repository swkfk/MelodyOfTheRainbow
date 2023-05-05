#include "Utils.h"
#include "PinHandler.h"
#include "PianoHandler.h"

void __sleep() {
    while (digitalRead(pinButtonGroup[0]) == LOW && digitalRead(pinButtonGroup[1]) == LOW && digitalRead(pinButtonGroup[2]) == LOW)
        ;
    for (uint8_t i = 0; i < 7; ++i) {
        digitalWrite(pinLedGroup[i], LOW);
    }
    LEDS.showColor(CRGB(0, 0, 0));
    while (true) {
        if (digitalRead(pinButtonGroup[0]) == LOW && digitalRead(pinButtonGroup[1]) == LOW && digitalRead(pinButtonGroup[2]) == LOW) {
            break;
        }
        delay(100);
    }
}

void __global_delay(uint8_t type) {
    switch (type) {
    case DELAY_FLOW:
        delay(100);
        break;
    case DELAY_IN_READ_COLOR:
        delay(50);
        break;
    case DELAY_AFTER_READ_KEY:
        delay(100);
        break;
    case DELAY_END_FLOW:
        delay(200);
        break;
    }
}

uint8_t __change_mode_detect(uint8_t old, unsigned int *p_time=nullptr) {
#ifndef _Button_group
    return old;
#else
    if (digitalRead(pinButtonGroup[0]) == LOW) {
        if (digitalRead(pinButtonGroup[1]) == LOW && digitalRead(pinButtonGroup[2]) == LOW) {
            Serial.println("Go to sleep...");
            __sleep();
            Serial.println("Ready to reset...");
            delay(100);
            ((void (*)(void)) NULL)();
        }
#ifdef _Show_button
        Serial.println("[Button] Play");
#endif
        return MODE_PLAY;
    }
    if (digitalRead(pinButtonGroup[1]) == LOW) {
#ifdef _Show_button
        Serial.println("[Button] Auto");
#endif
        if (p_time != nullptr && old != MODE_AUTO) {
            *p_time = millis();
        }
        return MODE_AUTO;
    }
    if (digitalRead(pinButtonGroup[2]) == LOW) {
#ifdef _Show_button
        Serial.println("[Button] Guide");
#endif
        if (p_time != nullptr && old != MODE_GUIDE) {
            *p_time = millis();
        }
        return MODE_GUIDE;
    }
    return old;
#endif
}

uint8_t __color_to_key(int r, int g, int b) {
#ifndef _Tcs
    return TONE_C;
#endif
    uint8_t res = 0;
    if (__much_greater(r, g) && __much_greater(r, b)) {
        res = TONE_C;
    } else if(__much_greater(r, b) && r > g && !__much_greater(r, g) && !__approx(r, g)) {
        res = TONE_D;
    } else if(__approx(r, g) && r > b && g > b) {
        res = TONE_E;
    } else if(__much_greater(g, r) && __much_greater(g, b)) {
        res = TONE_F;
    } else if(__much_greater(g, r) && __much_greater(b, r) && g > b) {
        res = TONE_G;
    } else if(__little_greater(b, r) && __little_greater(b, g) && !__approx(r, g)) {
        res = TONE_A;
    } else if(r > g && __much_greater(b, g)) {
        res = TONE_B;
    }
    // if (b > 80) {  // blue series
    //     if (r > 75 && r < 95 && g > 70 && g < 85) {
    //         res = TONE_B;  // purple
    //     } else if (r > 62 && r < 70 && g > 84 && g < 90) {
    //         res = TONE_A;  // blue;
    //     } else if (r > 60 && r < 68 && g > 95 && g < 104) {
    //         res = TONE_G;  // cyan
    //     }
    // } else if (b > 40) { // red series
    //     if (r > 70 && r < 90 && g > 100 && g < 110) {
    //         res = TONE_F;  // green
    //     } else if (r > 93 && r < 105 && g > 90 && g < 97) {
    //         res = TONE_E;  // yellow
    //     } else if (r > 100 && r < 107 && g > 82 && g < 90) {
    //         res = TONE_D;  // orange
    //     } else if (r > 105 && r < 115 && g > 75 && g < 83) {
    //         res = TONE_C;  // red
    //     }
    // }

    // if (r > 110 && g < 80 && b < 65) {
    //     res = TONE_C;
    // }
    // if (r > 100 && g > 75 && b < 60) {
    //     res = TONE_D;
    // }
    // if (r > 80 && g > 90 && b < 60) {
    //     res = TONE_E;
    // }
    // if (r > 50 && g > 100 && b < 65) {
    //     res = TONE_F;
    // }
    // if (r < 50 && g > 70 && b < 120) {
    //     res = TONE_G;
    // }
    // if (r < 45 && g > 70 && b > 120) {
    //     res = TONE_A;
    // }
    // if (r > 45 && g < 80 && b < 125) {
    //     res = TONE_B;
    // }
#ifdef _Show_color_recognized
    Serial.print("    key_idx: ");
    Serial.println(res);
#endif
    return res;
}

bool __much_greater(int opx, int opy) {
    return (opx - opy) * 3 > opx;
}

bool __little_greater(int opx, int opy) {
    return (opx - opy) * 4 > opx;
}

bool __approx(int opx, int opy) {
    return MAX(opx - opy, opy - opx) * 4 < MIN(opx, opy);
}
