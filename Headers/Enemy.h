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

    void takeDamage(float damage) {
        currentHealth -= damage;
        if (currentHealth < 0) currentHealth = 0;
    }

    bool isAlive() const {
        return currentHealth > 0;
    }

    float getCurrentHealth() const {
        return currentHealth;
    }

    float getMaxHealth() const {
        return maxHealth;
    }

    float getMovementSpeed() const {
        return movementSpeed;
    }

    Weapons* getEquippedWeapon() const {
        return equippedWeapon;
    }
};



#endif //ENEMY_H
