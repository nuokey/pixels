#pragma once

#include "pixel.hpp"
#include <vector>

class Projectile;

class Dynamite : public Pixel {
public:
    Dynamite(float x, float y);
    void explode(std::vector<Projectile>* projectiles, std::vector<Dynamite>* dynamite, int i);
    void update(Camera camera, std::vector<Dynamite>* dynamite,
    std::vector<Projectile>* projectiles, int i);
};