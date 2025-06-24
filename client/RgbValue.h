#pragma once
#include "SDL_stdinc.h"

struct RgbValue {

    Uint8 r;
    Uint8 g;
    Uint8 b;
    Uint8 a;

    RgbValue(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha = 255):
            r(red), g(green), b(blue), a(alpha) {}
};
