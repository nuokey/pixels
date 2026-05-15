#include "agent.hpp"
#include "projectile.hpp"
#include "camera.hpp"
#include <cmath>

Agent::Agent(float x, float y, Player* targetPlayer)
    : Player(x, y, 255, 0, 0)   
{
    target = targetPlayer;
    shootCooldown = 0.5f;       
    shootTimer = 0.0f;
}

void Agent::update(float dt, Camera camera, std::vector<Projectile>* projectiles) {
    if (target) {
        float dx = target->x - x;
        float dy = target->y - y;

        if (dx > 0) moveRight(dt);
        else if (dx < 0) moveLeft(dt);

        if (dy > 0) moveDown(dt);
        else if (dy < 0) moveUp(dt);
    }

    Player::update(dt, camera);

    if (projectiles) {
        shootTimer += dt;
        if (shootTimer >= shootCooldown) {
            shootAtTarget(projectiles);
            shootTimer = 0.0f;
        }
    }
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