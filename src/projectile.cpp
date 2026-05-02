#include "projectile.hpp"

Projectile::Projectile(float x_, float y_, float vx_, float vy_, sf::Color color_) {
    x = x_;
    y = y_;
    vx = vx_;
    vy = vy_;
    color = color_;
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