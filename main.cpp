#include <iostream>
#include <array>
#include <variant> // <-- Add this include for std::get_if

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

    // Load a sprite to display
    const sf::Texture texture("assets/cute_image.jpg");
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    const sf::Font font("assets/arial.ttf");
    sf::Text text(font, "Hello SFML", 50);
    text.setFillColor(sf::Color::Green);


    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Draw the string
        window.draw(text);

        // Update the window
        window.display();
    }
    return 0;
}

