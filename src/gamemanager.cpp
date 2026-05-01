#include "gamemanager.hpp"

GameManager::GameManager(std::string importFont) {
    font.openFromFile(importFont);
}