#include "../header/Enemy.h"
#include "../header/Player.h"
#include <stdexcept>
#include <iostream>
#include <cmath>




Enemy::Enemy()
    : mDirection(0.f, 0.f),
    initialPosition(0.f, 0.f),
    Entity() // Call base class constructor
{
    // Initialize inherited members
    mMovementSpeed = 80.f; // Slower than the player
    maxHealth = 50;
    currentHealth = maxHealth;

    if (!mTexture.loadFromFile("../assets/enemy.png"))
            throw std::runtime_error("Failed to load enemy texture");
    else {
        std::cout << "Enemy texture loaded." << std::endl;;
    }

    initialPosition = {100.f, 100.f};

    mSprite.setTexture(mTexture, true);
    mSprite.setPosition(initialPosition);
}







Enemy::Enemy(sf::Vector2f startPosition)
    : mDirection(0.f, 0.f),
    initialPosition(startPosition),
    Entity()
{
    mMovementSpeed = 80.f; // Slower than the player
    maxHealth = 50;
    currentHealth = maxHealth;

    if (!mTexture.loadFromFile("../assets/enemy.png"))
        throw std::runtime_error("Failed to load enemy texture");
    else {
        std::cout << "Enemy texture loaded." << std::endl;;
    }
    mSprite.setTexture(mTexture, true);
    mSprite.setPosition(startPosition);
}







void Enemy::takeDamage(float damageAmount)
{
    currentHealth -= damageAmount;
}








void Enemy::UpdateHealthEnemy(sf::Time deltaTime)
{
    // Use range placeholder for player and weapon
    float range = 50.f; // Example range value

    Player& player = Player::getInstance();
    // Weapon& playerWeapon = player.getWeapon();

    sf::Vector2f playerPosition = player.getPlayerPosition();
    sf::Vector2u playerSpriteSize = player.getTextureSize();

    sf::Vector2f currentEnemyPos = mSprite.getPosition();
    sf::Vector2u enemySpriteSize = mTexture.getSize();

    float distanceX = (playerPosition.x + playerSpriteSize.x / 2) - (currentEnemyPos.x + enemySpriteSize.x / 2);
    float distanceY = (playerPosition.y + playerSpriteSize.y / 2) - (currentEnemyPos.y + enemySpriteSize.y / 2);
    float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

    if (distance <= range  && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
    {
        // Placeholder damage amount
        int damageAmount = 10;
        takeDamage(damageAmount);
        std::cout << "Enemy hit. Current Health: " << currentHealth << std::endl;

    }

}






float Enemy::getCurrentHealth() const {
    return currentHealth;
}







void Enemy:: death() {
    std::cout << "Enemy has died." << std::endl;
    //logic for removing enemy from the game can be added here

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

    sf::Vector2f newPosition = currentEnemyPos + movement;



    // Keep enemy within window bounds
    if (newPosition.x < 0.f)
        newPosition.x = 0.f;
    if (newPosition.y < 0.f)
        newPosition.y = 0.f;
    if (newPosition.x + enemySpriteSize.x > windowSize.x)
        newPosition.x = windowSize.x - enemySpriteSize.x;
    if (newPosition.y + enemySpriteSize.y > windowSize.y)
        newPosition.y = windowSize.y - enemySpriteSize.y;


    mSprite.setPosition(newPosition);
}





void Enemy::update(sf::Time deltaTime, const sf::Window& window)
{
    updateMovementEnemy(deltaTime, window);
}

