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

    void updateMovement(sf::Time deltaTime, const sf::Window& window);

    void updateHealth(sf::Time deltaTime);


    void update(sf::Time deltaTime, const sf::Window& window);

    // Draw the player to a window
    void render(sf::RenderWindow& window) const;

};

#endif //PLAYER_H
