#ifndef ENEMY_H
#define ENEMY_H
#include "Weapons.h"

class Enemy {
private:
    float maxHealth;
    float currentHealth;
    float movementSpeed;
    Weapons* equippedWeapon;

public:
    Enemy(float maxHealth, float movementSpeed, Weapons* weapon)
        : maxHealth(maxHealth), currentHealth(maxHealth), movementSpeed(movementSpeed), equippedWeapon(weapon) {}

    void takeDamage(float damage) {}

    bool isAlive() const {}

    float getCurrentHealth() const {}

    float getMaxHealth() const {}

    float getMovementSpeed() const {}

    Weapons* getEquippedWeapon() const {}
};



#endif //ENEMY_H
