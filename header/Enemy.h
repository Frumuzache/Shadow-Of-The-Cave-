#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

#include "Entity.h" // <-- Include the base class

// Enemy also "is-an" Entity
class Enemy : public Entity {
public:
    // Constructor takes its patrol area
    Enemy(float leftBound, float rightBound, float yPos);

    // It must also implement the virtual update function
    void update(sf::Time deltaTime, const sf::Window& window) override;

    // render() is inherited from Entity

private:
    void updateMovementEnemy(sf::Time deltaTime, const sf::Window& window);
    sf::Vector2f mDirection;
};

#endif //ENEMY_H

