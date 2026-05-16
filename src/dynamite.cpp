#include "dynamite.hpp"
#include "projectile.hpp"
#include <cmath>

Dynamite::Dynamite(float x, float y)
    : Pixel(x, y, 255, 165, 0)   // оранжевый цвет (R=255, G=165, B=0)
{
    // При необходимости можно задать отличный от стандартного размер
    // size = 10; 
    // rect.setSize(sf::Vector2f(size, size));
    // rect.setFillColor(sf::Color(255, 165, 0));
}

void Dynamite::explode(std::vector<Projectile>* projectiles) {
    const int numProjectiles = 12;      // количество осколков
    const float speed = 2.0f;           // скорость разлёта
    const float damage = 10.0f;         // урон каждого осколка

    float angleStep = 2.0f * 3.14159265f / numProjectiles;
    for (int i = 0; i < numProjectiles; ++i) {
        float angle = i * angleStep;
        float vx = std::cos(angle) * speed;
        float vy = std::sin(angle) * speed;

        // Снаряд оранжево-красного цвета, летит от центра динамита
        projectiles->push_back(Projectile(x, y, vx, vy, sf::Color(255, 100, 0), damage));
    }
    // После взрыва динамит должен быть удалён из мира.
    // Это нужно сделать в том месте, где вызывается explode().
}
