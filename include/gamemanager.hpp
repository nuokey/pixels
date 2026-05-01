#pragma once

#include <SFML/Graphics.hpp>

#include "colourbar.hpp"
#include "camera.hpp"

class GameManager {
    public:
    sf::Font font;
    Camera camera;
    GameManager(std::string importFont);
    void worldGeneration(int worldSizeX, int worldSizeY);
};