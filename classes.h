#pragma once
#include <string>
#include <iostream>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

constexpr int WINDOW_HEIGHT = 1600;
constexpr int WINDOW_WIDTH  = 2560;

inline int PixelSize = 50;

inline int randInt(int min, int max) {
    int x = rand() % (max - min + 1) + min;
    return x;
}
