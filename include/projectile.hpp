#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "camera.hpp"
#include "dynamite.hpp"
#include "player.hpp"

// Forward declaration (достаточно для указателя)
class Pixel;

class Projectile {
    public:
    float x;
    float y;
    float vx;
    float vy;
    int size;
    float damage;
    sf::Color color;
    sf::RectangleShape rect;

    Projectile(float x_, float y_, float vx_, float vy_, sf::Color color_, float damage_);
    void update(float dt, Camera camera);
    void hit(Pixel* pixel, std::vector<Projectile>* projectiles, int z);
    void hit(Dynamite* dynamite, std::vector<Dynamite>* dynamiteVector, std::vector<Projectile>* projectiles, int z, int i);
    void hit(Player* player, std::vector<Projectile>* projectiles, int z);
};
