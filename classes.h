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

