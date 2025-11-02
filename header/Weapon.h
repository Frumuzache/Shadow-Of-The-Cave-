#ifndef WEAPON_H
#define WEAPON_H
#include <string>

class Weapon {
private:
    std::string name;
    float damage;
    float reloadTime;
    float range;


public:
    Weapon();
    Weapon(std::string  name, float damage, float reloadTime, float range);

    float getDamage() const;
    float getReloadTime() const;
    float getRange() const;
    std::string getName();

    float attack();


};


#endif //WEAPON_H
