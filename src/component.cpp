#include "component.hpp"

Component::Component(float x, float y, float vx_, float vy_, float red, float green, float blue) : Pixel(x, y, red, green, blue) {
    moveSpeed = 0.1;
    a = 0.1;
    vx = vx_;
    vy = vy_;
    size = 10;
    rect.setSize(sf::Vector2f(size, size));
}
void Component::moveToPlayer(Player player) {
    float rx = player.x - x;
    float ry = player.y - y;

    float r = sqrt(rx*rx + ry*ry);

    float n1 = rx / r;
    float n2 = ry / r;

    vx += n1 * a / r;
    vy += n2 * a / r;
}
void Component::friction() {
    vx *= 0.9;
    vy *= 0.9;
}
void Component::update(float dt, Camera camera, Player player) {
    moveToPlayer(player);
    friction();
    x += vx * dt;
    y += vy * dt;
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
}