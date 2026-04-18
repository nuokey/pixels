#include <SFML/Graphics.hpp>
#include "classes.h"
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <cmath>


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
    if (!font.openFromFile("../fonts/VMVSegaGenesis-Regular.otf")) { // Укажите путь к шрифту
        return -1; // Ошибка загрузки
    }

    sf::Text text(font, "", 20);
    text.setFillColor(sf::Color::White);

    ColourBar greenBar("Green", sf::Color::Green, 255, 0, 100, 300, 20, font, sf::Color::Green);
    ColourBar blueBar("Blue", sf::Color::Green, 255, 0, 150, 300, 20, font, sf::Color::Blue);
    ColourBar redBar("Red", sf::Color::Green, 255, 0, 200, 300, 20, font, sf::Color::Red);
    

    Camera camera;
    

    std::vector<Pixel> pixels;
    std::vector<Projectile> projectiles;
    std::vector<Component> components;
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
                // std::cout << &pixels[pixels.size()-1] << std::endl;
            }
        }
    }
    // std::cout << std::endl << std::endl;

    // for (int z = 0; z < 1; z++) {
    //     // pixels.push_back(Pixel(
    //     //     randInt(0, 100)*50, 
    //     //     randInt(0, 100)*50, 
    //     //     randInt(0, 255), 
    //     //     randInt(0, 255), 
    //     //     randInt(0, 255)));
    // }

    Player player{1000, 1000, static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100)), static_cast<float>(randInt(50, 100))};
    // std::cout << &player << std::endl;



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


                projectiles.push_back(Projectile(player.x, player.y, nx * v, ny * v, sf::Color::Red));
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
            // particles.push_back(Particle(player.x, player.y, 0, 0, sf::Color(player.red, player.green, player.blue), 1000));
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
        for (int z = 0; z < projectiles.size(); z++) {
// Обновление и сбор капель-лута
// for (size_t d = 0; d < drops.size(); ) {
//     drops[d].update(dt, camera);
//     window.draw(drops[d].rect);
    
//     // Проверка столкновения с игроком
//     if (std::fabs(drops[d].x - player.x) < (player.size + drops[d].size) / 2 &&
//         std::fabs(drops[d].y - player.y) < (player.size + drops[d].size) / 2)
//     {
//         player.green = std::min(255, player.green + drops[d].green);
//         player.red   = std::min(255, player.red   + drops[d].red);
//         drops.erase(drops.begin() + d);
//     }
//     else if (!drops[d].isAlive()) {
//         drops.erase(drops.begin() + d);
//     }
//     else {
//         ++d;
//     }
// }
            projectiles[z].update(dt, camera);
            window.draw(projectiles[z].rect);
            for (int i = 0; i < pixels.size(); i++) {
                if (std::fabs(pixels[i].x - projectiles[z].x) < (pixels[i].size + projectiles[z].size) / 2 && std::fabs(pixels[i].y - projectiles[z].y) < (pixels[i].size + projectiles[z].size) / 2) {
                    pixels[i].blue -= 10;
                    projectiles.erase(projectiles.begin() + z);
                    if (pixels[i].blue < 0) {
                        // Сохраняем цвета удаляемого пикселя
                        int capturedGreen = pixels[i].green / 5;
                        int capturedRed   = pixels[i].red / 5;

                        components.push_back(Component(pixels[i].x + randInt(-5, 5), pixels[i].y + randInt(-5, 5), randInt(-100, 100)*0.001, randInt(-100, 100)*0.001, capturedRed, 0, 0));
                        components.push_back(Component(pixels[i].x + randInt(-5, 5), pixels[i].y + randInt(-5, 5), randInt(-100, 100)*0.001, randInt(-100, 100)*0.001, 0, capturedGreen, 0));
                        

                        // Создаём 3 капли
                        // for (int d = 0; d < 3; ++d) {
                        //     float angle = randInt(0, 360) * M_PI / 180.f;
                        //     float speed = randInt(50, 150);   // пикселей в секунду
                        //     float vx = std::cos(angle) * speed;
                        //     float vy = std::sin(angle) * speed;
                            
                        //     int dropGreen = capturedGreen / 3;
                        //     int dropRed   = capturedRed / 3;
                        //     if (d == 2) { // последняя капля забирает остаток
                        //         dropGreen = capturedGreen - dropGreen * 2;
                        //         dropRed   = capturedRed   - dropRed * 2;
                        //     }
                        //     // drops.emplace_back(pixels[i].x, pixels[i].y, vx, vy, dropGreen, dropRed);
                        // }
                        pixels.erase(pixels.begin() + i);
                        }
                    break;
                }
            }
        }
        for (int i = 0; i < components.size(); i++) {
            components[i].update(dt, camera, player);
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
            particles[i].update(dt, camera);
            window.draw(particles[i].rect);
        }
        player.update(dt, camera);
        camera.x = player.x-WINDOW_WIDTH/2 + 500; // тут происходит какая-то дичь с камерой, надо будет доработать
        camera.y = player.y-WINDOW_HEIGHT/2 + 400; // тут тоже

        window.draw(player.rect);
        text.setString("Player: " + std::to_string(static_cast<int>(player.x)) + ", " + std::to_string(static_cast<int>(player.y)) + "\n" + 
            "Camera: " + std::to_string(static_cast<int>(camera.x)) + ", " + std::to_string(static_cast<int>(camera.y)));
        window.draw(text);

        greenBar.setValue(player.green);
        redBar.setValue(player.red);
        blueBar.setValue(player.blue);

        greenBar.draw(window);
        redBar.draw(window);
        blueBar.draw(window);

        window.display();
    }
}
