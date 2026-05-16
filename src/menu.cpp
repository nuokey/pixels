// #include "menu.hpp"
// #include <iostream>

// Menu::Menu(const std::string& fontPath) : startClicked(false) {
//     if (!font.openFromFile(fontPath)) {
//         std::cerr << "Failed to load font: " << fontPath << std::endl;
//     }
//     button.setSize(sf::Vector2f(200.f, 60.f));
//     button.setFillColor(sf::Color(50, 150, 50));
//     button.setOutlineColor(sf::Color::White);
//     button.setOutlineThickness(2.f);

//     buttonText.setFont(font);
//     buttonText.setString("START");
//     buttonText.setCharacterSize(30);
//     buttonText.setFillColor(sf::Color::White);
//     buttonText.setStyle(sf::Text::Bold);
// }

// void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
//     if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
//         if (mousePressed->button == sf::Mouse::Button::Left) {
//             sf::Vector2i mousePos = sf::Mouse::getPosition(window);
//             if (button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
//                 startClicked = true;
//             }
//         }
//     }
// }

// void Menu::draw(sf::RenderWindow& window) {
//     sf::Vector2u winSize = window.getSize();
//     button.setPosition(winSize.x / 2.f - button.getSize().x / 2.f,
//                        winSize.y / 2.f - button.getSize().y / 2.f);
    
//     sf::FloatRect textBounds = buttonText.getLocalBounds();
//     buttonText.setPosition(button.getPosition().x + (button.getSize().x - textBounds.size.x) / 2.f,
//                            button.getPosition().y + (button.getSize().y - textBounds.size.y) / 2.f - 5.f);
    
//     window.draw(button);
//     window.draw(buttonText);
// }

// bool Menu::isStartClicked() const {
//     return startClicked;
// }

// void Menu::reset() {
//     startClicked = false;
// }