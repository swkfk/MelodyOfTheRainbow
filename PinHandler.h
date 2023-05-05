#ifndef __PIN_DEF_H__
#define __PIN_DEF_H__

#include <Arduino.h>

#include "ModuleStart.h"

#ifdef _Led_group
const int pinLedGroup[] = {13, 12, 11, 10, 9, 8, A1};
#endif

#ifdef _Button_group
const int pinButtonGroup[] = {5, 6, 7};
#endif

#ifdef _Piano
const int pinPianoSCL = 2;
const int pinPianoSDO = 3;
const int pinPianoRGB = 4, cntPianoLed = 4;
#endif

#ifdef _Buzzer
const int pinBuzzerSIG = A0;
#endif

#ifdef _Tcs
const int pinColorSCL = A5;
const int pinColorSDA = A4;
#endif

void __pin_setup(void);

#endif