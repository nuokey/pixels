#pragma once

#include <SFML/Graphics.hpp>
#include "pixel.hpp"
#include "camera.hpp"
#include "projectile.hpp"

class Player: public Pixel {
    private:
    float moveSpeed;
    float a;
    float damage;

    public:
    float vx;
    float vy;
    Player(float x, float y, float red, float green, float blue);
    void moveRight(float dt);
    void moveLeft(float dt);
    void moveDown(float dt);
    void moveUp(float dt);
    void friction();
    void collision(Pixel pixel);
    void fire(std::vector<Projectile>* projectiles, float mouseX, float mouseY);
    void update(float dt, Camera camera);
};
