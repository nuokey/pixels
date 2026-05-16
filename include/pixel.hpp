#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

// Forward declarations
class Camera;
class Projectile;
class Component;

class Pixel {
    public:
    int red;
    int green;
    int blue;
    float x;
    float y;
    float size;
    sf::RectangleShape rect;
    
    Pixel(float x_, float y_, float red_, float green_, float blue_);
    void virus(std::vector<std::vector<Pixel>>* pixels_, int x_, int y_);
    void update(Camera camera, std::vector<std::vector<Pixel>>* pixels,
                std::vector<Projectile>* projectiles, 
                std::vector<Component>* components, int x_, int y_);
};
