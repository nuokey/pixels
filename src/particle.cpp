#include "particle.hpp"

Particle::Particle(float x, float y, float vx, float vy, sf::Color color, int ttl) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->color = color;
    this->ttl = ttl;
    size = 5;
    rect.setSize(sf::Vector2f(size, size));
    rect.setFillColor(color);
    rect.setPosition(sf::Vector2f(x, y));
    rect.setOutlineThickness(0);
}
void Particle::update(float dt, Camera camera) {
    x += vx * dt;
    y += vy * dt;
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
    ttl--;
}