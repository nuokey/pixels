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










Функции для вирусов
1) реализация
void makeVirus(Pixel& p, std::unordered_set<std::pair<float,float>, PairHash>& virusSet) {
    if (p.red == 0 && p.blue == 0) return;
    p.red = 0;
    p.blue = 0;
    virusSet.insert({p.x, p.y});
}
2) функция распространения вируса
void spreadVirus(std::vector<Pixel>& pixels,
                 std::unordered_set<std::pair<float,float>, PairHash>& virusSet,
                 float dt, float& timer, float interval) {
    timer += dt;
    if (timer < interval) return;
    timer = 0.f;

    auto currentViruses = virusSet; // копия, чтобы новые вирусы не влияли на текущий тик
    for (const auto& virusCoord : currentViruses) {
        // Найти указатель на пиксель-вирус
        Pixel* virusPixel = nullptr;
        for (auto& p : pixels) {
            if (p.x == virusCoord.first && p.y == virusCoord.second) {
                virusPixel = &p;
                break;
            }
        }
        if (!virusPixel) continue;

        // Перебрать все пиксели в поисках соседей
        for (auto& other : pixels) {
            if (&other == virusPixel) continue;
            // Соседство по горизонтали или вертикали (расстояние = PixelSize)
            bool isNeighbor = (std::fabs(virusPixel->x - other.x) < PixelSize + 1 && std::fabs(virusPixel->y - other.y) < 1) ||
                              (std::fabs(virusPixel->y - other.y) < PixelSize + 1 && std::fabs(virusPixel->x - other.x) < 1);
            if (isNeighbor) {
                other.red = std::max(0, other.red - 10);
                other.blue = std::max(0, other.blue - 10);
                if (other.red == 0 && other.blue == 0) {
                    if (virusSet.find({other.x, other.y}) == virusSet.end()) {
                        makeVirus(other, virusSet);
                    }
                }
            }
        }
    }
}
3) Вызов распространения вируса в главном цикле
// Распространение вируса
spreadVirus(pixels, virusSet, dt, virusSpreadTimer, virusSpreadInterval);

4) Вирус не дропает 
if (pixels[i].red < 0 && pixels[i].green < 0 && pixels[i].blue < 0) {
    bool isVirus = (virusSet.find({pixels[i].x, pixels[i].y}) != virusSet.end());
    if (!isVirus) {
        int capturedGreen = pixels[i].green;
        int capturedRed   = pixels[i].red;
        for (int d = 0; d < 3; ++d) {
            float angle = randInt(0, 360) * M_PI / 180.f;
            float speed = randInt(50, 150);
            float vx = std::cos(angle) * speed;
            float vy = std::sin(angle) * speed;
            int dropGreen = capturedGreen / 3;
            int dropRed   = capturedRed / 3;
            if (d == 2) {
                dropGreen = capturedGreen - dropGreen * 2;
                dropRed   = capturedRed   - dropRed * 2;
            }
            drops.emplace_back(pixels[i].x, pixels[i].y, vx, vy, dropGreen, dropRed);
        }
    }
    // Удалить пиксель из набора вирусов, если он там был
    virusSet.erase({pixels[i].x, pixels[i].y});
    pixels.erase(pixels.begin() + i);
}



5) ещё какая-то тема, хз что это
   * #include <unordered_set>

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1,T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);
        return h1 ^ (h2 << 1);
    }
};

   * // Вирусная система
std::unordered_set<std::pair<float,float>, PairHash> virusSet;
float virusSpreadTimer = 0.f;
const float virusSpreadInterval = 0.5f;   // интервал распространения (сек)


    Ещё вот страшная хрень
    . Примечание о производительности
Перебор всех пикселей для каждого вируса при распространении может быть медленным при большом количестве вирусов (O(V * N)). Для демонстрации концепции это допустимо. В реальном проекте можно оптимизировать, используя пространственное хеширование.

Вирус уменьшает red и blue соседей на 10 за один тик (каждые 0.5 сек). При необходимости измените число.

Вирусные пиксели не дропают капли и не добавляют цвет игроку.
