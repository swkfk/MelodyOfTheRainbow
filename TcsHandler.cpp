#include "TcsHandler.h"

MH_TCS34725 tcs = MH_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

void __tcs_setup(void) {
#ifdef _Tcs
    if (tcs.begin()) {
        Serial.println("[TCS] Done!");
    } else {
        Serial.println("[TCS] Error! Tcs sensor not found!");
        while (1)
            ;
    }
#else
    Serial.println("[TCS] Module not start.");
#endif
}

void __tcs_read_color(int *r, int *g, int *b) {
#ifdef _Tcs
    uint16_t clear, red, green, blue;

    tcs.unlock();
    delay(60);
    tcs.getRGBC(&red, &green, &blue, &clear);
    tcs.lock();
    *r = (int) ((float) red  / clear * 256);
    *g = (int) ((float) green  / clear * 256);
    *b = (int) ((float) blue  / clear * 256);

#ifdef _Show_color_recognized
    Serial.print("R:\t");
    Serial.print(*r);
    Serial.print("\tG:\t");
    Serial.print(*g);
    Serial.print("\tB:\t");
    Serial.println(*b);
#endif

#else
    *r = *g = *b = 255;
#endif
}
