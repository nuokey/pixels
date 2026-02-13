#include <SFML/Graphics.hpp>
#include "classes.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>


int PixelSize = 50;

int randInt(int min, int max) {
    int x = rand() % (max - min + 1) + min;
    return x;
}

int main()
{   
    std::srand(time(0));
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Pixels");
    sf::Clock clock;

    sf::Font font;
    if (!font.openFromFile("fonts/VMVSegaGenesis-Regular.otf")) { // Укажите путь к шрифту
        return -1; // Ошибка загрузки
    }

    sf::Text text(font, "", 20);
    text.setFillColor(sf::Color::White);

    Camera camera;
    

    std::vector<Pixel> pixels;
    std::vector<Particle> particles;

    // pixels.push_back(Pixel(300, 300, 100, 0, 0));

    // pixels.push_back(Pixel(
    //     randInt(0, WINDOW_WIDTH), 
    //     randInt(0, WINDOW_HEIGHT), 
    //     randInt(0, 255), 
    //     randInt(0, 255), 
    //     randInt(0, 255)
    // ));

    for (int x = 0; x < 100; x++) {
        for (int y = 0; y < 100; y++) {
            if (randInt(0, 100) < 50) {
                pixels.push_back(Pixel(x*PixelSize, y*PixelSize, randInt(0, 255), randInt(0, 255), randInt(0, 255)));
                std::cout << &pixels[pixels.size()-1] << std::endl;
            }
        }
    }
    std::cout << std::endl << std::endl;

    // for (int z = 0; z < 1; z++) {
    //     // pixels.push_back(Pixel(
    //     //     randInt(0, 100)*50, 
    //     //     randInt(0, 100)*50, 
    //     //     randInt(0, 255), 
    //     //     randInt(0, 255), 
    //     //     randInt(0, 255)));
    // }

    Player player{1000, 1000, 10, 255, 255};
    std::cout << &player << std::endl;



    text.setPosition(sf::Vector2f(camera.x, camera.y));
    
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left && player.red > 0) {
                float mouseX = sf::Mouse::getPosition(window).x+camera.x;
                float mouseY = sf::Mouse::getPosition(window).y+camera.y;

                float rx = mouseX - player.x;
                float ry = mouseY - player.y;
                float r = sqrt(rx*rx + ry*ry);
                float nx = rx / r;
                float ny = ry / r;
                float v = 1;


                particles.push_back(Particle(player.x, player.y, nx * v, ny * v, sf::Color::Red));
                // std::cout << "Fireball!!! " << nx * v << ny * v << std::endl;
                player.red -= 1;
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
        // if (sf::Mouse::(sf::Mouse::Button::Left)) {
            
        // }

        window.clear();
        

        for (int i = 0; i < pixels.size(); i++) {
            pixels[i].update(camera);
            window.draw(pixels[i].rect);

            // Collision updating
            if (std::fabs(pixels[i].x - player.x) < (pixels[i].size + player.size) / 2 && std::fabs(pixels[i].y - player.y) < (pixels[i].size + player.size) / 2) {
                if (pixels[i].x - player.x > 0 && std::fabs(pixels[i].y - player.y) < std::fabs(pixels[i].x - player.x)) {
                    player.x -= 1;
                }
                if (pixels[i].x - player.x < 0 && std::fabs(pixels[i].y - player.y) < std::fabs(pixels[i].x - player.x)) {
                    player.x += 1;
                }
                if (pixels[i].y - player.y < 0 && std::fabs(pixels[i].y - player.y) > std::fabs(pixels[i].x - player.x)) {
                    player.y += 1;
                }
                if (pixels[i].y - player.y > 0 && std::fabs(pixels[i].y - player.y) > std::fabs(pixels[i].x - player.x)) {
                    player.y -= 1;
                }
            }
        }
        for (int z = 0; z < particles.size(); z++) {
            particles[z].update(dt, camera);
            window.draw(particles[z].rect);
            for (int i = 0; i < pixels.size(); i++) {
                if (std::fabs(pixels[i].x - particles[z].x) < (pixels[i].size + particles[z].size) / 2 && std::fabs(pixels[i].y - particles[z].y) < (pixels[i].size + particles[z].size) / 2) {
                    pixels[i].blue -= 10;
                    pixels[i].red -= 10;
                    pixels[i].green -= 10;
                    particles.erase(particles.begin() + z);
                    if (pixels[i].red < 0 && pixels[i].green < 0 && pixels[i].blue < 0) {
                        pixels.erase(pixels.begin() + i);
                    }
                }
            }
        }
        player.update(dt, camera);
        camera.x = player.x-WINDOW_WIDTH/2;
        camera.y = player.y-WINDOW_HEIGHT/2;

        window.draw(player.rect);
        text.setString("Player: " + std::to_string(static_cast<int>(player.x)) + ", " + std::to_string(static_cast<int>(player.y)) + "\n" + 
            "Camera: " + std::to_string(static_cast<int>(camera.x)) + ", " + std::to_string(static_cast<int>(camera.y)));
        window.draw(text);

        window.display();
    }
}