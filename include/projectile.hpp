#pragma once

#include <SFML/Graphics.hpp>
#include "camera.hpp"
#include "pixel.hpp" 
// #include "component.hpp"


class Projectile {
    public:
    float x;
    float y;
    float vx;
    float vy;
    int size;
    float damage;
    sf::Color color;
    sf::RectangleShape rect;

    Projectile(float x_, float y_, float vx_, float vy_, sf::Color color_, float damage_);
    void update(float dt, Camera camera);
    void hit(Pixel* pixel, std::vector<Projectile>* projectiles, int z);
};