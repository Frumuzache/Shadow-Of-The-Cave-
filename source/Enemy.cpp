#include "../header/Enemy.h"
#include <stdexcept>
#include <iostream>

Enemy::Enemy(float leftBound, float rightBound, float yPos)
    : mDirection(1.f, 0.f), // Start moving right
    mLeftBound(leftBound),
    mRightBound(rightBound)
{
    // Initialize inherited members
    mMovementSpeed = 80.f; // Slower than the player

    if (!mTexture.loadFromFile("../assets/enemy.png"))
            throw std::runtime_error("Failed to load enemy or fallback texture");
    else {
        std::cout << "Enemy texture loaded." << std::endl;;
    }

    mSprite.setTexture(mTexture, true);
    mSprite.setPosition({leftBound, yPos});
}

void Enemy::update(sf::Time deltaTime, const sf::Window& window)
{
    // We use [[maybe_unused]] to tell the compiler we know
    // 'window' isn't used in this function, but we need it
    // to match the base class signature.

    // --- Patrol Logic ---
    sf::Vector2f movement = mDirection * mMovementSpeed * deltaTime.asSeconds();
    mSprite.move(movement);

    sf::Vector2f pos = mSprite.getPosition();
    sf::Vector2u spriteSize = mTexture.getSize();

    // Check boundaries and reverse direction
    if (pos.x < mLeftBound) {
        pos.x = mLeftBound;
        mDirection.x = 1.f; // Move right
    }
    else if (pos.x + spriteSize.x > mRightBound) {
        pos.x = mRightBound - spriteSize.x;
        mDirection.x = -1.f; // Move left
    }

    mSprite.setPosition(pos);
}

