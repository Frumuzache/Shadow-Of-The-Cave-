#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h" // <-- Include the new base class

// Player "is-an" Entity
class Player : public Entity {
public:
    Player();

    // "override" tells the compiler we are implementing
    // the pure virtual function from our parent (Entity)
    void update(sf::Time deltaTime, const sf::Window& window) override;

    // render() is now inherited from Entity!

private:
    // These functions are specific to the Player's update
    void updateMovement(sf::Time deltaTime, const sf::Window& window);
    void updateHealth(sf::Time deltaTime);

    // mTexture, mSprite, and mMovementSpeed are
    // now inherited from Entity!
};

#endif //PLAYER_H
