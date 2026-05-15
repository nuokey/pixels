#include "dynamite.hpp"
#include "projectile.hpp"
#include "pixel.hpp"
#include <cmath>

const float Dynamite::explosionSpeed = 2.0f;

Dynamite::Dynamite(float x_, float y_, float vx_, float vy_, sf::Color color_, float damage_)
    : Projectile(x_, y_, vx_, vy_, sf::Color(255, 165, 0), damage_)   
{
    explosionDamage = damage_ * 0.6f;  
    size = 12;                         
    rect.setSize(sf::Vector2f(size, size));
    rect.setFillColor(sf::Color(255, 165, 0));
}

void Dynamite::hit(Pixel* pixel, std::vector<Projectile>* projectiles, int index) {
    
    float angleStep = 2.0f * 3.14159f / explosionCount;
    for (int i = 0; i < explosionCount; ++i) {
        float angle = i * angleStep;
        float vx_expl = std::cos(angle) * explosionSpeed;
        float vy_expl = std::sin(angle) * explosionSpeed;
        
        Projectile shrapnel(x, y, vx_expl, vy_expl, sf::Color(255, 100, 0), explosionDamage);
        projectiles->push_back(shrapnel);
    }
    
    projectiles->erase(projectiles->begin() + index);
}