#include "agent.hpp"
#include "projectile.hpp"
#include "camera.hpp"
#include <cmath>
#include "classes.h"

Agent::Agent(float x, float y, Player* targetPlayer)
    : Player(x, y, 255, 0, 0)   
{
    target = targetPlayer;
    shootCooldown = 1000.0f;       
    shootTimer = 0.0f;
    damage = 10;
    a = 0.01;
    vx = 0;
    vy = 0;
    moveSpeed = 0.1;
}


void Agent::moveRight(float dt) {
    if (vx < moveSpeed) {
        vx += a;
    }
}

void Agent::moveLeft(float dt) {
    if (vx > -moveSpeed) {
        vx -= a;
    }
}
void Agent::moveDown(float dt) {
    if (vy < moveSpeed) {
        vy += a;
    }
}
void Agent::moveUp(float dt) {
    if (vy > -moveSpeed) {
        vy -= a;
    }
}

void Agent::friction() {
    vx *= 0.9;
    vy *= 0.9;
}


void Agent::collision(Pixel pixel) {
    if (std::fabs(pixel.x - x) < (pixel.size + size) / 2 && std::fabs(pixel.y - y) < (pixel.size + size) / 2 && !(pixel.red == 0 && pixel.green == 0 && pixel.blue == 0)) {
        if (pixel.x - x > 0 && std::fabs(pixel.y - y) < std::fabs(pixel.x - x)) {
            x -= 2;
        }
        if (pixel.x - x < 0 && std::fabs(pixel.y - y) < std::fabs(pixel.x - x)) {
            x += 2;
        }
        if (pixel.y - y < 0 && std::fabs(pixel.y - y) > std::fabs(pixel.x - x)) {
            y += 2;
        }
        if (pixel.y - y > 0 && std::fabs(pixel.y - y) > std::fabs(pixel.x - x)) {
            y -= 2;
        }
        if (pixel.red == 0 && pixel.green != 0 && pixel.blue == 0) {
            if (randInt(1, 100) == 1) {
                green -= 1;
            }
            
        }
    }
}

void Agent::update(float dt, Camera camera, std::vector<Projectile>* projectiles, Player* target_) {
    target = target_;
    // if (target) {
        float dx = target->x - x;
        float dy = target->y - y;

        if (dx > 0) moveRight(dt);
        else if (dx < 0) moveLeft(dt);

        if (dy > 0) moveDown(dt);
        else if (dy < 0) moveUp(dt);
    // }

    if (projectiles) {
        shootTimer += dt;
        if (shootTimer >= shootCooldown) {
            shootAtTarget(projectiles);
            shootTimer = 0.0f;
        }
    }
    x += vx * dt;
    y += vy * dt;
    friction();
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
}

void Agent::shootAtTarget(std::vector<Projectile>* projectiles) {
    if (!target) return;

    float rx = target->x - x;
    float ry = target->y - y;
    float r = std::sqrt(rx * rx + ry * ry);
    if (r == 0.0f) return;

    float nx = rx / r;
    float ny = ry / r;
    const float bulletSpeed = 1.0f;   
    projectiles->push_back(Projectile(x, y,
                                      nx * bulletSpeed,
                                      ny * bulletSpeed,
                                      sf::Color::Red,
                                      damage));   

    
}