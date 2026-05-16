#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>

#include "classes.h"
#include "pixel.hpp"
#include "player.hpp"
#include "camera.hpp"
#include "colourbar.hpp"
#include "component.hpp"
#include "projectile.hpp"
#include "particle.hpp"
#include "gamemanager.hpp"
#include "agent.hpp"
#include "dynamite.hpp"


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
 
    std::vector<std::vector<Pixel>> pixels;
    std::vector<Projectile> projectiles;
    std::vector<Component> components;
    std::vector<Particle> particles;
    std::vector<Agent> agents;
    std::vector<Dynamite> dynamite;

    

    pixels = gameManager.worldGeneration(100, 100, PixelSize);
    Player player{1000, 1000, static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100))};

    dynamite.push_back(Dynamite(1000, 1200));
    agents.push_back(Agent(1200, 1200, &player));
    
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
                    // std::cout << projectiles.size() << std::endl;
                }
                if (mousePressed->button == sf::Mouse::Button::Right && player.red > 64) {
                    float mouseX = sf::Mouse::getPosition(window).x+gameManager.camera.x;
                    float mouseY = sf::Mouse::getPosition(window).y+gameManager.camera.y;

                    dynamite.push_back(Dynamite(mouseX, mouseY));
                    player.red -= 32;
                    player.blue -= 32;
                    // std::cout << projectiles.size() << std::endl;
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
        
        for (int x = 0; x < pixels.size(); x++) {
            for (int y = 0; y < pixels[x].size(); y++) {
                pixels[x][y].update(gameManager.camera, &pixels, &projectiles, &components, x, y);
                window.draw(pixels[x][y].rect);
                player.collision(pixels[x][y]);
            }
        }
        bool a = false;
        for (int z = 0; z < projectiles.size(); z++) {
            projectiles[z].update(dt, gameManager.camera);
            window.draw(projectiles[z].rect);

            for (int i = 0; i < dynamite.size(); i++) {
                if (std::fabs(dynamite[i].x - projectiles[z].x) < (dynamite[i].size + projectiles[z].size) / 2 && std::fabs(dynamite[i].y - projectiles[z].y) < (dynamite[i].size + projectiles[z].size) / 2) {
                    projectiles[z].hit(&dynamite[i], &dynamite, &projectiles, z, i);
                    a = true;
                    if (a) {
                        break;
                    }
                }
            }

            for (int x = 0; x < pixels.size(); x++) {
                for (int y = 0; y < pixels[x].size(); y++) {
                    if (std::fabs(pixels[x][y].x - projectiles[z].x) < (pixels[x][y].size + projectiles[z].size) / 2 && std::fabs(pixels[x][y].y - projectiles[z].y) < (pixels[x][y].size + projectiles[z].size) / 2) {
                        projectiles[z].hit(&pixels[x][y], &projectiles, z);
                        a = true;
                        if (a) {
                            break;
                        }
                    }
                }
                if (a) {
                    break;
                }
            }
            if (a) {
                break;
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
        for (int i = 0; i < dynamite.size(); i++) {
            dynamite[i].update(gameManager.camera, &dynamite, &projectiles, i);
            window.draw(dynamite[i].rect);
        }
        for (int i = 0; i < agents.size(); i++) {
            agents[i].update(dt, gameManager.camera, &projectiles);
            window.draw(agents[i].rect);
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
