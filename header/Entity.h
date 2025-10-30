#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// An "abstract" base class for any object in our game world.
// We can't create a plain "Entity"; it must be a "Player" or an "Enemy".
class Entity {
public:
    // A virtual destructor is essential for base classes
    Entity();
    virtual ~Entity() = default;

    // A "pure virtual" update function.
    // The "= 0" means any class that inherits from Entity
    // MUST provide its own "update" function.
    virtual void update(sf::Time deltaTime, const sf::Window& window) = 0;

    // A common render function that works for all entities
    void render(sf::RenderWindow& window) const {
        window.draw(mSprite);
    }

    // Helper functions for collisions and positioning
    sf::FloatRect getGlobalBounds() const {
        return mSprite.getGlobalBounds();
    }

    sf::Vector2f getPosition() const {
        return mSprite.getPosition();
    }

    // "protected" means this class and any child classes (Player, Enemy)
    // can access these members.
protected:
    sf::Texture mTexture;
    sf::Sprite mSprite;
    float mMovementSpeed;
};

#endif //ENTITY_H
