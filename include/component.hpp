#pragma once
#include <SFML/Graphics.hpp>
#include "pixel.hpp"
#include "player.hpp"
#include "camera.hpp"

class Component : public Pixel {
private:
    float vx;
    float vy;
    float moveSpeed;
    float a;
public:
    Component(float x, float y, float vx, float vy, float red, float green, float blue);
    void moveToPlayer(Player player);
    void friction();
    void update(float dt, Camera camera, Player player);
};