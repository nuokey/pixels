#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class Menu {
private:
    sf::Font font;
    sf::RectangleShape button;
    std::unique_ptr<sf::Text> buttonText;  // Используем указатель
    bool startClicked;

public:
    Menu(const std::string& fontPath);
    ~Menu() = default;
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    bool isStartClicked() const;
    void reset();
};