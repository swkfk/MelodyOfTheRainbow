#include "ModuleStart.h"
#include "PianoHandler.h"
#include "PinHandler.h"
#include "TcsHandler.h"
#include "Utils.h"

unsigned int time;

void setup() {
    Serial.begin(115200);
    Serial.println("[Main] Program starting...");

    __pin_setup();

#ifdef _Tcs
    __tcs_setup();
#endif

    __piano_led_setup();
}

void loop() {
    static uint8_t s_mode         = MODE_START;
    static uint8_t s_led_flow_idx = 0;
    uint8_t        keypressed; // 按下的键
    uint8_t        tpm_keyread, keyread;    // 根据读取的颜色，推测出的键
    int            i_r, i_g, i_b;

    if (s_mode != MODE_START) {
#ifdef _Show_Mode
        Serial.print("[DEBUG] s_mode (befor) := ");
        Serial.println(s_mode);
#endif
        s_mode = __change_mode_detect(s_mode, &time);
#ifdef _Show_Mode
        Serial.print("[DEBUG] s_mode (after) := ");
        Serial.println(s_mode);
#endif
    }

#ifdef _Show_Mode
    Serial.print("[DEBUG] s_mode: ");
    if (s_mode == MODE_START) {
        Serial.println("START");
    } else if (s_mode == MODE_PLAY) {
        Serial.println("PLAY");
    } else if (s_mode == MODE_AUTO) {
        Serial.println("AUTO");
    } else if (s_mode == MODE_GUIDE) {
        Serial.println("GUIDE");
    } else {
        Serial.print("ERROR: ");
        Serial.println((int) s_mode);
    }
#endif

    switch (s_mode) {
    case MODE_START: // 程控的跑马灯效果
        if (s_led_flow_idx >= 21) {
#ifndef _Endless_flow_leds
            // 这里向下是正常情况下退出跑马灯的代码
            // 会全部亮起，稍停息后全部熄灭
            s_mode = MODE_PLAY;
            for (uint8_t i = 0; i < 7; ++i) {
                digitalWrite(pinLedGroup[i], HIGH);
            }
            __global_delay(DELAY_END_FLOW);
            for (uint8_t i = 0; i < 7; ++i) {
                digitalWrite(pinLedGroup[i], LOW);
            }
#else
            // 开启“无限跑马灯”后会执行这里的代码，重置 idx
            s_led_flow_idx = 0;
#endif
        } else {
            for (uint8_t i = 0; i < 7; ++i) {
                if (i != s_led_flow_idx % 7) {
                    digitalWrite(pinLedGroup[i], LOW);
                }
            }
            digitalWrite(pinLedGroup[s_led_flow_idx % 7], HIGH);
            ++s_led_flow_idx;
            __global_delay(DELAY_FLOW);
        }
        break;
    case MODE_PLAY:
        keypressed = __piano_read_keys(s_mode);
        if (0 == keypressed) {
            __global_delay(DELAY_AFTER_READ_KEY);
            break;
        }
        __buzzer_play(keypressed);
        __piano_back_leds(keypressed);
        break;
    case MODE_AUTO:
        __tcs_read_color(&i_r, &i_g, &i_b);
        tpm_keyread = __color_to_key(i_r, i_g, i_b);
        if (tpm_keyread != 0) {
            keyread = tpm_keyread;
        }
        if (millis() - time > TONE_DELAY)  {
            __buzzer_play(keyread);
            __piano_back_leds(keyread);
            time = millis();
        }
        break;
    case MODE_GUIDE:
        __tcs_read_color(&i_r, &i_g, &i_b);
        tpm_keyread = __color_to_key(i_r, i_g, i_b);
        if (tpm_keyread != 0) {
            keyread = tpm_keyread;
        }
        __piano_back_leds(keyread);
        keypressed = __piano_read_keys(s_mode);
        __buzzer_play(keypressed);
        break;
    }
}
