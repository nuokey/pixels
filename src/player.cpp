#include "player.hpp"
#include "camera.hpp"

Player::Player(float x, float y, float red, float green, float blue) : Pixel(x, y, red, green, blue) {
    moveSpeed = 0.1;
    a = 0.01;
    vx = 0;
    vy = 0;
    size = 40;
    rect.setSize(sf::Vector2f(size, size));
}

void Player::moveRight(float dt) {
    if (vx < moveSpeed) {
        vx += a;
    }
}

void Player::moveLeft(float dt) {
    if (vx > -moveSpeed) {
        vx -= a;
    }
}
void Player::moveDown(float dt) {
    if (vy < moveSpeed) {
        vy += a;
    }
}
void Player::moveUp(float dt) {
    if (vy > -moveSpeed) {
        vy -= a;
    }
}
void Player::friction() {
    vx *= 0.9;
    vy *= 0.9;
}

void Player::collision(Pixel pixel) {
    if (std::fabs(pixel.x - x) < (pixel.size + size) / 2 && std::fabs(pixel.y - y) < (pixel.size + size) / 2) {
        if (pixel.x - x > 0 && std::fabs(pixel.y - y) < std::fabs(pixel.x - x)) {
            x -= 1;
        }
        if (pixel.x - x < 0 && std::fabs(pixel.y - y) < std::fabs(pixel.x - x)) {
            x += 1;
        }
        if (pixel.y - y < 0 && std::fabs(pixel.y - y) > std::fabs(pixel.x - x)) {
            y += 1;
        }
        if (pixel.y - y > 0 && std::fabs(pixel.y - y) > std::fabs(pixel.x - x)) {
            y -= 1;
        }
    }
}

void Player::fire(std::vector<Projectile>* projectiles_, float mouseX, float mouseY) {
    float rx = mouseX - x;
    float ry = mouseY - y;
    float r = sqrt(rx*rx + ry*ry);
    float nx = rx / r;
    float ny = ry / r;
    float v = 1;

    projectiles_->push_back(Projectile(x, y, nx * v, ny * v, sf::Color::Red));
    
    red -= 1;
}


// void Player::collision(int ) {

// }
void Player::update(float dt, Camera camera) {
    x += vx * dt;
    y += vy * dt;
    friction();
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
}