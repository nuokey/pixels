#include "pixel.hpp"
#include "camera.hpp"

Pixel::Pixel(float x, float y, float red, float green, float blue) {
    this->x = x;
    this->y = y;
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->size = 50;
    
    rect.setSize(sf::Vector2f(size, size));
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setOutlineThickness(0);
    rect.setOutlineColor(sf::Color::White);
}

void Pixel::update(Camera camera) {
    if (red < 0) {
        red = 0;
    }
    if (green < 0) {
        green = 0;
    }
    if (blue < 0) {
        blue = 0;
    }
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
}