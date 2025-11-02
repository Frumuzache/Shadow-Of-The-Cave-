#include "../header/Enemy.h"
#include "../header/Player.h"
#include <stdexcept>
#include <iostream>
#include <cmath>



Enemy::Enemy(float leftBound, float rightBound, float yPos)
    : mDirection(0.f, 0.f)
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




void Enemy::updateMovementEnemy(sf::Time deltaTime, sf::Window const& window)
{
    Player& player = Player::getInstance();
    sf::Vector2f playerPosition = player.getPlayerPosition();
    sf::Vector2u playerSpriteSize = player.getTextureSize();

    sf::Vector2f currentEnemyPos = mSprite.getPosition();
    sf::Vector2u enemySpriteSize = mTexture.getSize();
    sf::Vector2u windowSize = window.getSize();

    //Find center of enemy sprite
    sf::Vector2f enemyCenter(
        currentEnemyPos.x + static_cast<float>(enemySpriteSize.x) * 0.5f,
        currentEnemyPos.y + static_cast<float>(enemySpriteSize.y) * 0.5f
    );

    //Find center of player sprite
    sf::Vector2f playerCenter(
         playerPosition.x + static_cast<float>(playerSpriteSize.x) * 0.5f,
         playerPosition.y + static_cast<float>(playerSpriteSize.y) * 0.5f
     );

    // --- 2. CALCULATE DIRECTION AND MOVEMENT ---

    sf::Vector2f direction = playerCenter - enemyCenter;
    sf::Vector2f movement(0.f, 0.f);

    const float deadZoneRadius = 5.0f;
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (distance > deadZoneRadius)
    {
        // Normalize the direction vector (making its length 1)
        movement = direction / distance;

        // Apply speed and time
        movement.x *= mMovementSpeed * deltaTime.asSeconds();
        movement.y *= mMovementSpeed * deltaTime.asSeconds();
    }

    // --- 3. CALCULATE NEW POSITION ---
    sf::Vector2f newPosition = currentEnemyPos + movement;


    // --- 4. BOUNDS LOGIC (Applied to newPosition) ---


    // Keep enemy within window bounds
    if (newPosition.x < 0.f)
        newPosition.x = 0.f;
    if (newPosition.y < 0.f)
        newPosition.y = 0.f;
    if (newPosition.x + enemySpriteSize.x > windowSize.x)
        newPosition.x = windowSize.x - enemySpriteSize.x;
    if (newPosition.y + enemySpriteSize.y > windowSize.y)
        newPosition.y = windowSize.y - enemySpriteSize.y;



    // --- 5. SET FINAL POSITION ---
    mSprite.setPosition(newPosition);
}


void Enemy::update(sf::Time deltaTime, const sf::Window& window)
{
    updateMovementEnemy(deltaTime, window);
}

