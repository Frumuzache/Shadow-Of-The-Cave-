#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include "Enemy.h"
#include "Player.h"

class Game
{
public:
    Game();
    void run();

    sf::Vector2u getWindowSize() {
        return mWindow.getSize();
    }

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    Enemy mEnemy;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;
    sf::RenderWindow mWindow;
    sf::Clock mClock;


};

#endif //GAME_H
