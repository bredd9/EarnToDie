//
// Created by Vlad on 09-Jan-25.
//

#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Collision {
public:
    // Check if two objects are colliding
    static bool checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2);
};

#endif //COLLISION_H
