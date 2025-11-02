#ifndef MELEEWEAPON_H
#define MELEEWEAPON_H
#include "Weapon.h"


class MeleeWeapon:  public Weapon{
public:
    MeleeWeapon();
    MeleeWeapon(const std::string& name, float damage, float reloadTime, float range);

private:


};


#endif //MELEEWEAPON_H
