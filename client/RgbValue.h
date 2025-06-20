#pragma once
#include "SDL_stdinc.h"

struct RgbValue {

    Uint8 red;
    Uint8 green;
    Uint8 blue;

    RgbValue(Uint8 red, Uint8 green, Uint8 blue): red(red), green(green), blue(blue) {}
};
