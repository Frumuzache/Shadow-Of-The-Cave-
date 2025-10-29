#include "../header/Player.h"
#include <cmath>
#include <iostream>


// Constructor
Player::Player()
    :mTexture{},
    mSprite(mTexture),
    mMovementSpeed(150.f)
{
    if (!mTexture.loadFromFile("../assets/player.png"))
        throw std::runtime_error("Failed to load player texture");

    // --- ADD THIS LINE ---
    std::cout << "Player texture size: " << mTexture.getSize().x
              << " x " << mTexture.getSize().y << std::endl;

    mSprite.setTexture(mTexture, true);
    constexpr sf::Vector2f initialPosition(400.f, 300.f);
    mSprite.setPosition(initialPosition); // Starting position
}






// Update the player's logic (input and movement)
void Player::update(sf::Time deltaTime)
{

    sf::Vector2f movement(0.f, 0.f);

    // Check for real-time keyboard input
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
    {
        movement.x -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
    {
        movement.x += 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
    {
        movement.y -= 1.f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
    {
        movement.y += 1.f;
    }

    if (movement.x != 0.f || movement.y != 0.f) {
        float len = std::sqrt(movement.x * movement.x + movement.y * movement.y);
        movement.x = (movement.x / len) * mMovementSpeed * deltaTime.asSeconds();
        movement.y = (movement.y / len) * mMovementSpeed * deltaTime.asSeconds();
    }

    // Apply the movement, scaled by speed and delta time
    mSprite.move(movement);
}






// Draw the player
void Player::render(sf::RenderWindow& window) const {
    // Draw our shape to the target window
    window.draw(mSprite);
}
