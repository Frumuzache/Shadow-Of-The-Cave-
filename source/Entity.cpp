#include "../header/Entity.h"

// Define the default constructor
// This initializes mSprite with the (currently empty) mTexture,
// which is required since sf::Sprite has no default constructor.
Entity::Entity()
    : mTexture{},
    mSprite(mTexture),
    mMovementSpeed(0.f)
{
    // The body is empty. The initialization list does all the work.
}

