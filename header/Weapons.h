#ifndef WEAPONS_H
#define WEAPONS_H

class Weapons {
private:
    std::string name;
public:
    std::string getName() const {
        return name;
    }
    void setName(std::string name) {
        this->name = name;
    }
};

class MeleeWeapon : public Weapons {
private:
    float damage;
    float range;
    float attackSpeed;
public:
    MeleeWeapon(float damage, float range, float attackSpeed)
        : damage(damage), range(range), attackSpeed(attackSpeed) {}
};

class RangedWeapon : public Weapons {
private:
    int bulletNumber;
    float damage;
    float range;
    float attackSpeed;
public:
    RangedWeapon(int bulletNumber, float damage, float range, float attackSpeed)
        : bulletNumber(bulletNumber), damage(damage), range(range), attackSpeed(attackSpeed) {}

    int getBulletNumber() const {
        return bulletNumber;
    }

};

#endif //WEAPONS_H
