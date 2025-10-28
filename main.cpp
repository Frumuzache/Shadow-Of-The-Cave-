#include <iostream>
#include <cmath>
#include <array>
#include <variant>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


#include "Headers/Weapons.h"
#include "Headers/Player.h"
#include "Headers/Enemy.h"

int main() {
    std::cout << "Hello, world!\n";


    // Create the main window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png"))
    {
        return -1; // Error
    }

    sf::Sprite background(backgroundTexture);

    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("assets/player.png"))
    {
        return -1; // Error
    }

    sf::Vector2f initialPosition(400.f, 300.f);
    sf::Sprite player(playerTexture);
    player.setPosition(initialPosition);


    const float speed = 250.f; // pixels per second
    sf::Clock clock;

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float dt = clock.restart().asSeconds();

        sf::Vector2f movement(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
            movement.y -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
            movement.y += 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
            movement.x -= 1.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
            movement.x += 1.f;

        // Normalize so diagonal movement isn't faster
        if (movement.x != 0.f || movement.y != 0.f) {
            float len = std::sqrt(movement.x * movement.x + movement.y * movement.y);
            movement.x = (movement.x / len) * speed * dt;
            movement.y = (movement.y / len) * speed * dt;
            player.move(movement);
        }

        window.clear();

        window.draw(background); // Draw background FIRST
        window.draw(player);     // Draw player SECOND (on top)

        window.display();
    }
    return 0;
}

