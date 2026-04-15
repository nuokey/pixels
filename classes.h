#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

constexpr int WINDOW_HEIGHT = 720;
constexpr int WINDOW_WIDTH  = 1280;


class Camera {
    public:
    int x;
    int y;
    Camera() {
        x = 0;
        y = 0;
    }
};

class Pixel {
    public:
    int red;
    int green;
    int blue;
    float x;
    float y;
    float size;
    sf::RectangleShape rect;
    Pixel(float x, float y, float red, float green, float blue) {
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
    
    void update(Camera camera) {
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
};

class Player: public Pixel {
    private:
    float moveSpeed;
    float a;

    public:
    float vx;
    float vy;
    Player(float x, float y, float red, float green, float blue) : Pixel(x, y, red, green, blue) {
        moveSpeed = 0.1;
        a = 0.01;
        vx = 0;
        vy = 0;
        this->size = 40;
        rect.setSize(sf::Vector2f(size, size));
    }
    void moveRight(float dt) {
        if (vx < moveSpeed) {
            vx += a;
        }
    }
    void moveLeft(float dt) {
        if (vx > -moveSpeed) {
            vx -= a;
        }
    }
    void moveDown(float dt) {
        if (vy < moveSpeed) {
            vy += a;
        }
    }
    void moveUp(float dt) {
        if (vy > -moveSpeed) {
            vy -= a;
        }
    }
    void friction() {
        vx *= 0.9;
        vy *= 0.9;
    }
    void collision() {
        
    }
    void update(float dt, Camera camera) {
        x += vx * dt;
        y += vy * dt;
        friction();
        rect.setFillColor(sf::Color(red, green, blue));
        rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
    }
};

class Particle {
    public:
    float x;
    float y;
    float vx;
    float vy;
    int size;
    sf::Color color;
    sf::RectangleShape rect;

    Particle(float x, float y, float vx, float vy, sf::Color color) {
        this->x = x;
        this->y = y;
        this->vx = vx;
        this->vy = vy;
        this->color = color;
        size = 10;
        rect.setSize(sf::Vector2f(size, size));
        rect.setFillColor(color);
        rect.setPosition(sf::Vector2f(x, y));
        rect.setOutlineThickness(0);
    }
    void update(float dt, Camera camera) {
        x += vx * dt;
        y += vy * dt;
        rect.setPosition(sf::Vector2f(x-camera.x-size/2, y-camera.y-size/2));
    }

};


// Класс для управления отображением одной цветной шкалы
class ColourBar {
private:
    sf::RectangleShape background;   // фон шкалы
    sf::RectangleShape fill;         // заполненная часть
    sf::Font font;
    sf::Text label;
    std::string colorName;
    int current;
    int maxValue;
    sf::Color barColor;              // цвет заполнения

public:
    ColourBar(const std::string& name, const sf::Color& color, int max, float x, float y, float width, float height, const sf::Font& fnt, sf::Color barcolor) : label(fnt, "", 20) {
        font = fnt;
        barColor = barcolor;

        maxValue = 255;
        // Фон (серый)
        background.setSize(sf::Vector2f(width, height));
        background.setPosition(sf::Vector2f(x, y));
        background.setFillColor(sf::Color(0, 0, 0));
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color::White);

        // Заполнение (цветное)
        fill.setSize(sf::Vector2f(0, height));
        fill.setPosition(sf::Vector2f(x, y));
        fill.setFillColor(barColor);

        // Текст
        label.setFont(font);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);
        label.setPosition(sf::Vector2f(x, y-25));
        updateText();
    }

    void setValue(int value) {
        current = std::clamp(value, 0, maxValue);
        updateFillWidth();
        updateText();
    }

    void updateFillWidth() {
        float width = background.getSize().x * (static_cast<float>(current) / maxValue);
        fill.setSize(sf::Vector2f(width, background.getSize().y));
    }

    void updateText() {
        label.setString(std::to_string(current) + "/" + std::to_string(maxValue));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
        window.draw(label);
    }
};