#pragma once

#include "player.hpp"

class Agent : public Player {
private:
    Player* target;         
public:
    Agent(float x, float y, Player* targetPlayer);
    void update(float dt, Camera camera, std::vector<Projectile>* projectiles);
    void shootAtTarget(std::vector<Projectile>* projectiles);
};