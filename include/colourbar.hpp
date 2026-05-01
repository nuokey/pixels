#pragma once
#include <SFML/Graphics.hpp>


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
    ColourBar(const std::string& name, const sf::Color& color, int max, float x, float y, float width, float height, const sf::Font& fnt, sf::Color barcolor);

    void setValue(int value);
    void updateFillWidth();
    void updateText();
    void draw(sf::RenderWindow& window);
};
