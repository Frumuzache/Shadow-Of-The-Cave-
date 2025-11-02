#include "../header/Weapon.h"
#include <string>
#include <utility>

Weapon::Weapon()
    : name("Default Weapon"),
    damage(10.0f),
    reloadTime(1.0f),
    range(100.0f)
{

}

Weapon::Weapon(std::string  name, float damage, float reloadTime, float range)
    : name(std::move(name)),
    damage(damage),
    reloadTime(reloadTime),
    range(range)
{

}

float Weapon::getDamage() const {
    return damage;
}

float Weapon::getReloadTime() const {
    return reloadTime;
}

float Weapon::getRange() const {
    return range;
}

std::string Weapon::getName() {
    return name;
}



