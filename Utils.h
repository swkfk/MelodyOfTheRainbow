#ifndef __UTILS__
#define __UTILS__

#include "libMH_TCS34725.h"

#define DELAY_FLOW 0x00
#define DELAY_IN_READ_COLOR 0x01
#define DELAY_AFTER_READ_KEY 0x02

#define MODE_START 0x1f
#define MODE_PLAY 0x10
#define MODE_AUTO 0x11
#define MODE_GUIDE 0x12
#define DELAY_END_FLOW 0x13

#define TONE_bD 1 // 降半音的 re
#define TONE_bE 2 // 降半音的 mi
#define TONE_bG 3 // 降半音的 sol
#define TONE_bA 4 // 降半音的 la
#define TONE_bB 5 // 降半音的 si
#define TONE_C 6  // do
#define TONE_D 7  // re
#define TONE_E 8  // mi
#define TONE_F 9  // fa
#define TONE_G 10 // sol
#define TONE_A 11 // la
#define TONE_B 12 // si

#define TONE_DELAY 800

#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

void    __global_delay(uint8_t);
uint8_t __change_mode_detect(uint8_t, unsigned int*);
uint8_t __color_to_key(int, int, int);

void __sleep(void);

bool __much_greater(int, int);
bool __little_greater(int, int);
bool __approx(int, int);

#endif
