#ifndef ENEMY_H
#define ENEMY_H

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
    // Members unique to the Enemy's AI
    sf::Vector2f mDirection;
    float mLeftBound;
    float mRightBound;
};

#endif //ENEMY_H

