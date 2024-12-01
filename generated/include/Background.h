//
// Created by Vlad on 01-Dec-24.
//

#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class Background {
public:
    Background();
    bool initialize(const std::string& filepath, float scrollSpeed, int windowWidth, int windowHeight);
    void update(float deltaTime);
    void render(sf::RenderWindow& window) const;

private:
    sf::Texture texture;
    sf::Sprite sprite1, sprite2;
    float speed; // Scrolling speed
    int windowWidth, windowHeight;
};

#endif