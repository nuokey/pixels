#include "pixel.hpp"
#include "camera.hpp"
#include "component.hpp"
#include "projectile.hpp"
#include "classes.h"  // для randInt
#include <cmath>

Pixel::Pixel(float x_, float y_, float red_, float green_, float blue_) {
    x = x_;
    y = y_;
    red = red_;
    green = green_;
    blue = blue_;
    size = 50;
    
    rect.setSize(sf::Vector2f(size, size));
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x, y));
    rect.setOutlineThickness(0);
    rect.setOutlineColor(sf::Color::White);
}

void Pixel::virus(std::vector<std::vector<Pixel>>* pixels, int x_, int y_) {
    if (randInt(1, 10) == 1) {
        if (x_ < 99) {
            if ((*pixels)[x_+1][y_].green < 254 && (*pixels)[x_+1][y_].red != 0 && (*pixels)[x_+1][y_].red != 0) {
                (*pixels)[x_+1][y_].red -= 1;
                (*pixels)[x_+1][y_].green += 1;
                (*pixels)[x_+1][y_].blue -= 1;
            }
        }
        if (y_ < 99) {
            if ((*pixels)[x_][y_+1].green < 254 && (*pixels)[x_][y_+1].red != 0 && (*pixels)[x_][y_+1].red != 0) {
                (*pixels)[x_][y_+1].red -= 1;
                (*pixels)[x_][y_+1].green += 1;
                (*pixels)[x_][y_+1].blue -= 1;
            }
        }
        if (x_ > 0) {
            if ((*pixels)[x_-1][y_].green < 254 && (*pixels)[x_-1][y_].red != 0 && (*pixels)[x_-1][y_].red != 0) {
                (*pixels)[x_-1][y_].red -= 1;
                (*pixels)[x_-1][y_].green += 1;
                (*pixels)[x_-1][y_].blue -= 1;
            }
        }
        if (y_ > 0) {
            if ((*pixels)[x_][y_-1].green < 254 && (*pixels)[x_][y_-1].red != 0 && (*pixels)[x_][y_-1].red != 0) {
                (*pixels)[x_][y_-1].red -= 1;
                (*pixels)[x_][y_-1].green += 1;
                (*pixels)[x_][y_-1].blue -= 1;
            }
        }
        std::cout << "fasdf" << std::endl;
    }
    
    
}

void Pixel::update(Camera camera, std::vector<std::vector<Pixel>>* pixels,
    std::vector<Projectile>* projectiles, 
    std::vector<Component>* components, int x_, int y_) {
    if (green != 0 && red == 0 && blue == 0) {
        virus(pixels, x_, y_);
    }
    if (red < 0) red = 0;
    if (green < 0) green = 0;
    if (blue < 0) blue = 0;
    
    rect.setFillColor(sf::Color(red, green, blue));
    rect.setPosition(sf::Vector2f(x - camera.x - size/2, y - camera.y - size/2));
    
    if (blue <= 0 && red != 0 && green != 0) {
        int capturedGreen = green / 5;
        int capturedRed   = red / 5;
        red = 0;
        green = 0;

        components->push_back(Component(x + randInt(-5, 5), y + randInt(-5, 5), 
                                        randInt(-100, 100) * 0.001, randInt(-100, 100) * 0.001, 
                                        capturedRed, 0, 0));
        components->push_back(Component(x + randInt(-5, 5), y + randInt(-5, 5), 
                                        randInt(-100, 100) * 0.001, randInt(-100, 100) * 0.001, 
                                        0, capturedGreen, 0));
        
        //pixels->erase(pixels->begin() + i);
    }
}
