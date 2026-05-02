#include "gamemanager.hpp"
#include "pixel.hpp"
// #include "classes.h"


GameManager::GameManager(std::string importFont) {
    font.openFromFile(importFont);
    
}

// std::vector<Pixel> GameManager::worldGeneration(int worldSizeX, int worldSizeY) {
//     std::vector<Pixel> pixels_;
//     for (int x = 0; x < 100; x++) {
//         for (int y = 0; y < 100; y++) {
//             if (randInt(0, 100) < 50) {
//                 pixels_.push_back(Pixel(x*PixelSize, y*PixelSize, randInt(0, 255), randInt(0, 255), randInt(0, 255)));
//             }
//         }
//     } 
//     return pixels_;
// }
