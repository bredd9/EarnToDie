#ifndef ANIMATE_H
#define ANIMATE_H


#include <SFML/Graphics.hpp>
#include <iostream>

class Animate {
public:
    Animate(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float animationSpeed);
    void update(float deltaTime);
    void reset();

private:
    sf::Sprite& sprite;
    std::vector<sf::IntRect> frames;
    float animationSpeed;
    float timeSinceLastFrame;
    size_t currentFrame;
};



#endif //ANIMATE_H
