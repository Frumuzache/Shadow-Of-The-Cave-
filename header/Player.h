#ifndef PLAYER_H
#define PLAYER_H
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    float mMovementSpeed;

public:
    Player();

    // Handle player-specific input and movement
    void update(sf::Time deltaTime);

    // Draw the player to a window
    void render(sf::RenderWindow& window) const;

};

#endif //PLAYER_H
