#include "colourbar.hpp"

ColourBar::ColourBar(const std::string& name, const sf::Color& color, int max, float x, float y, float width, float height, const sf::Font& fnt, sf::Color barcolor) : label(fnt, "", 20) {
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

void ColourBar::setValue(int value) {
    current = std::clamp(value, 0, maxValue);
    updateFillWidth();
    updateText();
}

void ColourBar::updateFillWidth() {
    float width = background.getSize().x * (static_cast<float>(current) / maxValue);
    fill.setSize(sf::Vector2f(width, background.getSize().y));
}

void ColourBar::updateText() {
    label.setString(std::to_string(current) + "/" + std::to_string(maxValue));
}

void ColourBar::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(fill);
    window.draw(label);
}