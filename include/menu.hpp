#pragma once
#include <SFML/Graphics.hpp>

class Menu {
private:
    sf::Font font;
    sf::RectangleShape button;
    sf::Text buttonText;
    bool startClicked;   // флаг, который сбрасывается при показе меню

public:
    Menu(const std::string& fontPath);
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isStartClicked() const;
    void reset();
};