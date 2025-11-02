#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>

#include "Entity.h"

class Enemy : public Entity {
public:
    // Constructor takes its patrol area
    Enemy();
    Enemy(sf::Vector2f startPosition);


    void update(sf::Time deltaTime, const sf::Window& window) override;

    void takeDamage(float damageAmount);

    static void death();

    float getCurrentHealth() const;


private:
    void UpdateHealthEnemy(sf::Time deltaTime);
    void updateMovementEnemy(sf::Time deltaTime, const sf::Window& window);
    sf::Vector2f mDirection;
    sf::Vector2f initialPosition;
};

#endif //ENEMY_H

