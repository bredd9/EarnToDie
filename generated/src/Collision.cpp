//
// Created by Vlad on 09-Jan-25.

#include <Collision.h>

bool Collision::checkCollision(const sf::Sprite& sprite1, const sf::Sprite& sprite2) {
    // Get the bounding boxes of the sprites
    sf::FloatRect bounds1 = sprite1.getGlobalBounds();
    sf::FloatRect bounds2 = sprite2.getGlobalBounds();

    // Check if the bounding boxes intersect
    return bounds1.intersects(bounds2);
}