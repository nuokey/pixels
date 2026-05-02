#pragma once
#include <SFML/Graphics.hpp>
#include "camera.hpp"

class Particle {
    public:
    float x;
    float y;
    float vx;
    float vy;
    int size;
    int ttl;
    sf::Color color;
    sf::RectangleShape rect;
    
    Particle(float x_, float y_, float vx_, float vy_, sf::Color color_, int ttl_);
    void update(float dt, Camera camera);
};