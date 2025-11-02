#include "../header/Entity.h"



Entity::Entity()
    : mTexture{},
    mSprite(mTexture),
    mMovementSpeed(0.f),
    maxHealth(),
    currentHealth()

{
    // The body is empty. The initialization list does all the work.
}

