#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Window/Window.hpp>

#include "Weapons.h"

class Enemy {
private:
    sf::Texture eTexture;
    sf::Sprite eSprite;
    float eMovementSpeed;

public:
    Enemy();

    void updateMovement(sf::Time deltaTime, const sf::Window& window);

    void updateHealth(sf::Time deltaTime);

    void update(sf::Time deltaTime, const sf::Window& window);

    void render(sf::RenderWindow& window) const;

};

#endif //ENEMY_H
