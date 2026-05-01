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
    
    Particle(float x, float y, float vx, float vy, sf::Color color, int ttl);
    void update(float dt, Camera camera);
};