#include "PianoHandler.h"
#include "BuzzerHandler.h"
#include "Utils.h"

#ifdef _Piano
CRGB leds[cntPianoLed];
TTP229 ttp229(pinPianoSCL, pinPianoSDO);
#endif

void __piano_led_setup(void) {
#ifdef _Piano
    FastLED.addLeds<NEOPIXEL, pinPianoRGB>(leds, cntPianoLed);
    LEDS.showColor(CRGB(150, 0, 0));
    Serial.println("[Led] Done!");
#endif
}

uint8_t __piano_read_keys(uint8_t mode_old) {
#ifndef _Piano
    return 6;
#else
    uint8_t  sum  = 0;
    uint16_t keys = ttp229.ReadKeys16Interruptible(mode_old);

    for (uint8_t i = 0; i < 16; i++)
        if (keys & (1 << i))
            sum += i + 1;

#ifdef _Show_keypressed
    Serial.print("[Debug] Piano pressed: ");
    Serial.println(sum);
#endif

    return sum;
#endif
}

uint8_t __piano_get_keys(uint8_t mode_old) {
#ifndef _Piano
    return 6;
#else
    uint8_t  sum  = 0;
    uint16_t keys = ttp229.GetKeys16();

    for (uint8_t i = 0; i < 16; i++)
        if (keys & (1 << i))
            sum += i + 1;

#ifdef _Show_keypressed
    Serial.print("[Debug] Piano pressed: ");
    Serial.println(sum);
#endif

    return sum;
#endif
}

void __piano_back_leds(uint8_t key_pressed) {
#ifdef _Piano
    if (6 <= key_pressed && key_pressed <= 12) {
        for (uint8_t i = 0; i < 7; ++i) {
            if (i != key_pressed - 6) {
                digitalWrite(pinLedGroup[i], LOW);
            }
        }
        digitalWrite(pinLedGroup[key_pressed - 6], HIGH);
    }
    if (key_pressed == 1) {
        LEDS.showColor(CRGB(150, 0, 0));
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 2) {
        LEDS.showColor(CRGB(0, 150, 0));
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 3) {
        LEDS.showColor(CRGB(0, 0, 150));
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 4) {
        LEDS.showColor(CRGB(150, 150, 0));
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 5) {
        LEDS.showColor(CRGB(0, 150, 150));
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 6) {
        LEDS.showColor(CRGB(255, 0, 0));
//        __buzzer_play(1);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 7) {
        LEDS.showColor(CRGB(255, 165, 0));
//        __buzzer_play(2);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 8) {
        LEDS.showColor(CRGB(255, 255, 0));
//        __buzzer_play(3);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 9) {
        LEDS.showColor(CRGB(0, 255, 0));
//        __buzzer_play(4);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 10) {
        LEDS.showColor(CRGB(0, 127, 255));
//        __buzzer_play(5);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 11) {
        LEDS.showColor(CRGB(0, 0, 255));
//        __buzzer_play(6);
        __global_delay(DELAY_AFTER_READ_KEY);
    } else if (key_pressed == 12) {
        LEDS.showColor(CRGB(139, 0, 255));
//        __buzzer_play(7);
        __global_delay(DELAY_AFTER_READ_KEY);
    }
#endif
}
