#ifndef __PIANO_HANDLER_H__
#define __PIANO_HANDLER_H__

#include <Arduino.h>

#include "ModuleStart.h"

#ifdef _Piano
#include <FastLED.h>
#include <Wire.h>

extern CRGB leds[];

#endif

#include "libTTP229.h"

#include "BuzzerHandler.h"
#include "PinHandler.h"

extern TTP229 ttp229;

uint8_t __piano_read_keys(uint8_t);
uint8_t __piano_get_keys(uint8_t);
void    __piano_back_leds(uint8_t);
void    __piano_led_setup(void);

#endif