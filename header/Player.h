#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

#pragma once

class Player : public Entity {
public:
    Player();

    // "override" tells the compiler we are implementing
    // the pure virtual function from our parent (Entity)
    void update(sf::Time deltaTime, const sf::Window& window) override;

    sf::Vector2f getPlayerPosition() const;

    static Player& getInstance();
    sf::Vector2u getTextureSize() const;

private:
    // These functions are specific to the Player's update
    void updateMovement(sf::Time deltaTime, const sf::Window& window);
    void updateHealth(sf::Time deltaTime);
};

#endif //PLAYER_H
