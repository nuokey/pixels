#include "gamemanager.hpp"
#include "pixel.hpp"
#include "classes.h"


GameManager::GameManager(std::string importFont) {
    font.openFromFile(importFont);
    
}

std::vector<std::vector<Pixel>> GameManager::worldGeneration(int worldSizeX, int worldSizeY, int Pixelize) {
    std::vector<std::vector<Pixel>> pixels_;
    for (int x = 0; x < 100; x++) {
        std::vector<Pixel> pixelsRow;
        for (int y = 0; y < 100; y++) {
            float red = 0;
            float green = 0;
            float blue = 0;
            if (randInt(0, 100) < 50) {
               red = randInt(0, 255);
               green = randInt(0, 255);
               blue = randInt(0, 255);
            }
            
            pixelsRow.push_back(Pixel(x*PixelSize, y*PixelSize, red, green, blue));
        }
        pixels_.push_back(pixelsRow);
    } 
    pixels_[randInt(0, 99)][randInt(0, 99)].green = 255;
    pixels_[randInt(0, 99)][randInt(0, 99)].red = 0;
    pixels_[randInt(0, 99)][randInt(0, 99)].blue = 0;
    return pixels_;
}
