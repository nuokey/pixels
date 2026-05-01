#include "projectile.hpp"

Projectile::Projectile(float x, float y, float vx, float vy, sf::Color color) {
    this->x = x;
    this->y = y;
    this->vx = vx;
    this->vy = vy;
    this->color = color;
    size = 10;
    rect.setSize(sf::Vector2f(size, size));
    rect.setFillColor(color);
    rect.setPosition(sf::Vector2f(x, y));
    rect.setOutlineThickness(0);
}
void Projectile::update(float dt, Camera camera) {
    x += vx * dt;
    y += vy * dt;
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
}