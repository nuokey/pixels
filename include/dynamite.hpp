#pragma once

#include "projectile.hpp"
#include <vector>

class Dynamite : public Projectile {
private:
    static const int explosionCount = 12;      
    static const float explosionSpeed;         
    float explosionDamage;                     

public:
    Dynamite(float x_, float y_, float vx_, float vy_, sf::Color color_, float damage_);
    
    void hit(Pixel* pixel, std::vector<Projectile>* projectiles, int index) override;
};