#pragma once

#include "player.hpp"

class Agent : public Player {
private:
    Player* target;   
    float shootCooldown;  
    float shootTimer; 
    float damage;
    float a;
    float moveSpeed;
public:
    Agent(float x, float y, Player* targetPlayer);
    void moveRight(float dt);
    void moveLeft(float dt);
    void moveDown(float dt);
    void moveUp(float dt);
    void friction();
    void collision(Pixel pixel);
    void update(float dt, Camera camera, std::vector<Projectile>* projectiles, Player* player);
    void shootAtTarget(std::vector<Projectile>* projectiles);
};