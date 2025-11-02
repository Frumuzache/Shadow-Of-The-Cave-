#include <SFML/Graphics.hpp>
#include "../header/Game.h"
#include "../header/Player.h"
#include <cmath>


// Constructor
Game::Game()
    : mBackgroundTexture{},
    mBackgroundSprite(mBackgroundTexture),
    mWindow(sf::VideoMode({1920, 1080}), "Shadow Of The Cave"),
    mClock{}

{
    mWindow.setFramerateLimit(120);

    if (!mBackgroundTexture.loadFromFile("../assets/background.png"))
        throw std::runtime_error("Failed to load background texture");

    mBackgroundSprite.setTexture(mBackgroundTexture, true);

    mEnemies.push_back(std::make_unique<Enemy>(sf::Vector2f(300.f, 100.f)));
    mEnemies.push_back(std::make_unique<Enemy>(sf::Vector2f(600.f, 400.f)));
    mEnemies.push_back(std::make_unique<Enemy>(sf::Vector2f(900.f, 700.f)));
}





// The main run function
void Game::run()
{

    while (mWindow.isOpen())
    {
        sf::Time deltaTime = mClock.restart();

        processEvents();
        update(deltaTime);
        render();
    }
}







void Game::processEvents() {
    while (const std::optional event = mWindow.pollEvent()) {

        if (event->is<sf::Event::Closed>())
        {
            mWindow.close();
        }

        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                mWindow.close();
        }

        if (isKeyPressed(sf::Keyboard::Key::Space))
        {
            for (const auto& enemyPtr : mEnemies)
            {
                Enemy* mEnemy = enemyPtr.get();
                // If the enemy doesn't exist (is_dead/nullptr), do nothing
                if (!mEnemy) // <-- ADD THIS CHECK
                {
                    continue; // Skip this input
                }

                Player& player = Player::getInstance();
                float attackRange = player.getAttackRange();
                float attackDamage = player.getAttackDamage();

                sf::Vector2f playerPosition = player.getPlayerPosition();
                sf::Vector2u playerSpriteSize = player.getTextureSize();

                sf::Vector2f enemyPosition = mEnemy->getPosition();
                sf::Vector2u enemySpriteSize = mEnemy->getSpriteSize();

                float distanceX = (playerPosition.x + playerSpriteSize.x / 2) - (enemyPosition.x + enemySpriteSize.x / 2);
                float distanceY = (playerPosition.y + playerSpriteSize.y / 2) - (enemyPosition.y + enemySpriteSize.y / 2);
                float distance = std::sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distance <= attackRange)
                    mEnemy->takeDamage(attackDamage);
            }
        }
    }
}

// Function to update the game state
void Game::update(sf::Time deltaTime) {
    Player::getInstance().update(deltaTime, mWindow);
    for (auto& enemy : mEnemies)
        enemy->update(deltaTime, mWindow);

    std::erase_if(mEnemies, [](const auto& enemy) {
        if (enemy->getCurrentHealth() <= 0)
        {
            enemy->death();
            return true;
        }
        return false;

    });
}




// Function to draw everything
void Game::render()
{
    // Clear the window with black color
    mWindow.clear(sf::Color::Black);

    // Draw background first
    mWindow.draw(mBackgroundSprite);

    // Draw the player
    Player::getInstance().render(mWindow);

    for (auto& enemy : mEnemies)
    {
        enemy->render(mWindow);
    }

    // Display what was drawn to the screen
    mWindow.display();
}