#pragma once

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
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

// Класс для управления отображением одной цветной шкалы
class ColourBar {
private:
    sf::RectangleShape background;   // фон шкалы
    sf::RectangleShape fill;         // заполненная часть
    sf::Text label;                  // текст "Цвет: X/255"
    sf::Font font;
    std::string colorName;
    int current;
    int maxValue;
    sf::Color barColor;              // цвет заполнения

public:
    ColourBar(const std::string& name, const sf::Color& color, int max, float x, float y, float width, float height, const sf::Font& fnt)
        : colorName(name), current(0), maxValue(max), barColor(color) {
        font = fnt;

        // Фон (серый)
        background.setSize(sf::Vector2f(width, height));
        background.setPosition(x, y);
        background.setFillColor(sf::Color(50, 50, 50));
        background.setOutlineThickness(1);
        background.setOutlineColor(sf::Color::White);

        // Заполнение (цветное)
        fill.setSize(sf::Vector2f(0, height));
        fill.setPosition(x, y);
        fill.setFillColor(barColor);

        // Текст
        label.setFont(font);
        label.setCharacterSize(18);
        label.setFillColor(sf::Color::White);
        label.setPosition(x, y - 25);
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
        label.setString(colorName + ": " + std::to_string(current) + "/" + std::to_string(maxValue));
    }

    void draw(sf::RenderWindow& window) {
        window.draw(background);
        window.draw(fill);
        window.draw(label);
    }
};

int main() {
    // Создаём окно
    sf::RenderWindow window(sf::VideoMode(800, 400), "Colour Bars Demo");
    window.setFramerateLimit(60);

    // Загружаем шрифт (поместите arial.ttf в папку с исполняемым файлом)
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Ошибка загрузки шрифта! Убедитесь, что arial.ttf есть в папке.\n";
        return -1;
    }

    // Параметры шкал (x, y, ширина, высота)
    float barWidth = 300;
    float barHeight = 30;
    float startX = 50;
    float startY = 100;
    float yStep = 80;

    // Создаём три шкалы (теперь ColourBar)
    ColourBar greenBar("Green", sf::Color::Green, 255, startX, startY, barWidth, barHeight, font);
    ColourBar blueBar("Blue",  sf::Color::Blue,  255, startX, startY + yStep, barWidth, barHeight, font);
    ColourBar redBar("Red",    sf::Color::Red,   255, startX, startY + 2*yStep, barWidth, barHeight, font);

    // Текущие количества шариков (пример)
    int greenBalls = 120;
    int blueBalls  = 45;
    int redBalls   = 200;

    greenBar.setValue(greenBalls);
    blueBar.setValue(blueBalls);
    redBar.setValue(redBalls);

    // Основной цикл
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            // Управление для демонстрации (стрелки вверх/вниз изменяют количество)
            if (event.type == sf::Event::KeyPressed) {
                // Зелёные: Z (уменьшить) / X (увеличить)
                if (event.key.code == sf::Keyboard::Z) greenBalls = std::max(0, greenBalls - 10);
                if (event.key.code == sf::Keyboard::X) greenBalls = std::min(255, greenBalls + 10);
                // Синие: C (уменьшить) / V (увеличить)
                if (event.key.code == sf::Keyboard::C) blueBalls = std::max(0, blueBalls - 10);
                if (event.key.code == sf::Keyboard::V) blueBalls = std::min(255, blueBalls + 10);
                // Красные: B (уменьшить) / N (увеличить)
                if (event.key.code == sf::Keyboard::B) redBalls = std::max(0, redBalls - 10);
                if (event.key.code == sf::Keyboard::N) redBalls = std::min(255, redBalls + 10);

                greenBar.setValue(greenBalls);
                blueBar.setValue(blueBalls);
                redBar.setValue(redBalls);
            }
        }

        window.clear(sf::Color::Black);

        // Рисуем шкалы
        greenBar.draw(window);
        blueBar.draw(window);
        redBar.draw(window);

        window.display();
    }

    return 0;
}
