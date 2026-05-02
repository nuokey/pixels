#pragma once

#include <SFML/Graphics.hpp>
#include "camera.hpp"


class Projectile {
    public:
    float x;
    float y;
    float vx;
    float vy;
    int size;
    sf::Color color;
    sf::RectangleShape rect;

    Projectile(float x_, float y_, float vx_, float vy_, sf::Color color_);
    void update(float dt, Camera camera);
};