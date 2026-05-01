#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "camera.hpp"

class Pixel {
    public:
    int red;
    int green;
    int blue;
    float x;
    float y;
    float size;
    sf::RectangleShape rect;
    Pixel(float x, float y, float red, float green, float blue);
    void update(Camera camera);
};
