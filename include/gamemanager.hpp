#pragma once

#include <SFML/Graphics.hpp>

#include "colourbar.hpp"
#include "camera.hpp"
// #include "pixel.hpp"

class GameManager {
    public:
    sf::Font font;
    Camera camera;
    GameManager(std::string importFont);
    // std::vector<Pixel> worldGeneration(int worldSizeX, int worldSizeY);
};
