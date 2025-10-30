#include <SFML/Graphics.hpp>

#include "../header/Game.h"
#include <iostream>


// Constructor
Game::Game()
    : mPlayer{},
    mEnemy(100.f, 600.f, 400.f),
    mBackgroundTexture{},
    mBackgroundSprite(mBackgroundTexture),
    mWindow(sf::VideoMode({800, 600}), "Shadow Of The Cave"),
    mClock{}

{
    mWindow.setFramerateLimit(60); // <--- ADD THIS LINE

    if (!mBackgroundTexture.loadFromFile("../assets/background.png"))
        throw std::runtime_error("Failed to load background texture");

    mBackgroundSprite.setTexture(mBackgroundTexture, true);
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







// Function to handle all user input
void Game::processEvents()
{
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
    }
}




// Function to update the game state
void Game::update(sf::Time deltaTime) {
    mPlayer.update(deltaTime, mWindow);
    mEnemy.update(deltaTime,mWindow);

}




// Function to draw everything
void Game::render()
{

    // Clear the window with black color
    mWindow.clear(sf::Color::Black);

    // Draw background first
    mWindow.draw(mBackgroundSprite);

    // Draw the player
    mPlayer.render(mWindow);

    // Draw the enemy
    mEnemy.render(mWindow);

    // Display what was drawn to the screen
    mWindow.display();
}