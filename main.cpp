#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>

#include "pixel.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "colourbar.hpp"
#include "component.hpp"
#include "projectile.hpp"
#include "particle.hpp"
#include "gamemanager.hpp"

#include "classes.h"

int main()
{
    std::srand(time(0));
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pixels");
    sf::Clock clock;
    
    GameManager gameManager("../fonts/VMVSegaGenesis-Regular.otf");

    // sf::Text text(font, "", 20);
    // text.setFillColor(sf::Color::White);

    ColourBar greenBar("Green", sf::Color::Green, 255, 0, 100, 300, 20, gameManager.font, sf::Color::Green);
    ColourBar blueBar("Blue", sf::Color::Green, 255, 0, 150, 300, 20, gameManager.font, sf::Color::Blue);
    ColourBar redBar("Red", sf::Color::Green, 255, 0, 200, 300, 20, gameManager.font, sf::Color::Red);
 
    std::vector<Pixel> pixels;
    std::vector<Projectile> projectiles;
    std::vector<Component> components;
    std::vector<Particle> particles;

    pixels = gameManager.worldGeneration(100, 100, PixelSize);
    Player player{1000, 1000, static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100))};
    
    // text.setPosition(sf::Vector2f(camera.x, camera.y));
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left && player.red > 0) {
                    float mouseX = sf::Mouse::getPosition(window).x+gameManager.camera.x;
                    float mouseY = sf::Mouse::getPosition(window).y+gameManager.camera.y;

                    player.fire(&projectiles, mouseX, mouseY);
                    std::cout << projectiles.size() << std::endl;
                }
            }
        }
        float dt = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        dt = dt * 0.001;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            player.moveRight(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            player.moveLeft(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            player.moveDown(dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            player.moveUp(dt);
        }
        window.clear();
        

        for (int i = 0; i < pixels.size(); i++) {
            pixels[i].update(gameManager.camera);
            window.draw(pixels[i].rect);
            player.collision(pixels[i]);
        }
        for (int z = 0; z < projectiles.size(); z++) {
            projectiles[z].update(dt, gameManager.camera);
            window.draw(projectiles[z].rect);
            for (int i = 0; i < pixels.size(); i++) {
                if (std::fabs(pixels[i].x - projectiles[z].x) < (pixels[i].size + projectiles[z].size) / 2 && std::fabs(pixels[i].y - projectiles[z].y) < (pixels[i].size + projectiles[z].size) / 2) {
                    // pixels[i].blue -= 10;
                    // projectiles.erase(projectiles.begin() + z);
                    projectiles[z].hit(&pixels[i], &projectiles, z);
                    if (pixels[i].blue < 0) {
                        // Сохраняем цвета удаляемого пикселя
                        int capturedGreen = pixels[i].green / 5;
                        int capturedRed   = pixels[i].red / 5;

                        components.push_back(Component(pixels[i].x + randInt(-5, 5), pixels[i].y + randInt(-5, 5), randInt(-100, 100)*0.001, randInt(-100, 100)*0.001, capturedRed, 0, 0));
                        components.push_back(Component(pixels[i].x + randInt(-5, 5), pixels[i].y + randInt(-5, 5), randInt(-100, 100)*0.001, randInt(-100, 100)*0.001, 0, capturedGreen, 0));
                        
                        pixels.erase(pixels.begin() + i);
                        }
                    break;
                }
            }
        }
        for (int i = 0; i < components.size(); i++) {
            components[i].update(dt, gameManager.camera, player);
            window.draw(components[i].rect);

            // Collision updating
            if (std::fabs(components[i].x - player.x) < (components[i].size + player.size) / 2 && std::fabs(components[i].y - player.y) < (components[i].size + player.size) / 2) {
                if (player.red + components[i].red <= 255) {player.red += components[i].red;}
                if (player.green + components[i].green <= 255) {player.green += components[i].green;}
                if (player.blue + components[i].blue <= 255) {player.blue += components[i].blue;}
                components.erase(components.begin() + i);
                break;
            }
        }
        for (int i = 0; i < particles.size(); i++) {
            particles[i].update(dt, gameManager.camera);
            window.draw(particles[i].rect);
        }
        player.update(dt, gameManager.camera);
        gameManager.camera.x = player.x-WINDOW_WIDTH/2 + 500; // тут происходит какая-то дичь с камерой, надо будет доработать
        gameManager.camera.y = player.y-WINDOW_HEIGHT/2 + 400; // тут тоже

        window.draw(player.rect);
        // text.setString("Player: " + std::to_string(static_cast<int>(player.x)) + ", " + std::to_string(static_cast<int>(player.y)) + "\n" + 
        //     "Camera: " + std::to_string(static_cast<int>(camera.x)) + ", " + std::to_string(static_cast<int>(camera.y)));
        // window.draw(text);

        greenBar.setValue(player.green);
        redBar.setValue(player.red);
        blueBar.setValue(player.blue);

        greenBar.draw(window);
        redBar.draw(window);
        blueBar.draw(window);

        window.display();
    }
}
