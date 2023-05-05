#ifndef __TCS_HANDLER_H__
#define __TCS_HANDLER_H__

#include "ModuleStart.h"
#include <Arduino.h>


#include "libMH_TCS34725.h"

extern MH_TCS34725 tcs;

void __tcs_setup(void);
void __tcs_read_color(int *, int *, int *);

#endif