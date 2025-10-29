#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Player.h"

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time deltaTime);
    void render();

    Player mPlayer;
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;
    sf::RenderWindow mWindow;
    sf::Clock mClock;


};

#endif //GAME_H
