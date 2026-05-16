#include "dynamite.hpp"
#include "projectile.hpp"
#include <cmath>
#include "classes.h"

Dynamite::Dynamite(float x, float y)
    : Pixel(x, y, 255, 165, 0)   // оранжевый цвет (R=255, G=165, B=0)
{
    // При необходимости можно задать отличный от стандартного размер
    // size = 10; 
    // rect.setSize(sf::Vector2f(size, size));
    // rect.setFillColor(sf::Color(255, 165, 0));
}

void Dynamite::explode(std::vector<Projectile>* projectiles, std::vector<Dynamite>* dynamite, int i) {
    const int numProjectiles = 100;      // количество осколков
    const float speed = 2.0f;           // скорость разлёта
    const float damage = 50.0f;         // урон каждого осколка
    dynamite->erase(dynamite->begin() + i);
    float angleStep = 2.0f * 3.14159265f / numProjectiles;
    for (int i = 0; i < numProjectiles; ++i) {
        float angle = i * angleStep;
        float vx = std::cos(angle) * speed;
        float vy = std::sin(angle) * speed;

        // Снаряд оранжево-красного цвета, летит от центра динамита
        projectiles->push_back(Projectile(x, y, vx, vy, sf::Color(255, 100, 0), damage));
    }
}

void Dynamite::update(Camera camera, std::vector<Dynamite>* dynamite,
    std::vector<Projectile>* projectiles, int i) {
    
    // rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x - camera.x - size/2, y - camera.y - size/2));
}
