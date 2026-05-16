#pragma once

#include "pixel.hpp"
#include <vector>

class Projectile;

class Dynamite : public Pixel {
public:
    Dynamite(float x, float y);
    void explode(std::vector<Projectile>* projectiles);
};