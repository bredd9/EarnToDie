//
// Created by Vlad on 01-Dec-24.
//

#include <Background.h>

Background::Background(): speed(0), windowWidth(0), windowHeight(0) {
}

bool Background::initialize(const std::string& filepath, const float scrollSpeed, const int Width, const int Height) {
    this->speed = scrollSpeed;
    this->windowWidth = Width;
    this->windowHeight = Height;


    if (!texture.loadFromFile(filepath)) {
        std::cout << "Failed to load background image " << "\n";
        return false; // Initialization failed
    }

    // Set the texture for the sprites
    sprite1.setTexture(texture);
    sprite2.setTexture(texture);

    // Adjust sizes if necessary
    const sf::Vector2u textureSize = texture.getSize();
    const float scaleX = static_cast<float>(Width) / textureSize.x;
    const float scaleY = static_cast<float>(Height) / textureSize.y;
    sprite1.setScale(scaleX, scaleY);
    sprite2.setScale(scaleX, scaleY);

    // Set the initial positions
    sprite1.setPosition(0, 0);
    sprite2.setPosition(Width, 0);

    return true; // Initialization successful
}

void Background::update(const float deltaTime) {
    const float offset = speed * deltaTime;

    // Move both sprites to the left
    sprite1.move(-offset, 0);
    sprite2.move(-offset, 0);

    // Check if a sprite has moved completely out of the window
    if (sprite1.getPosition().x + windowWidth < 0) {
        sprite1.setPosition(sprite2.getPosition().x + windowWidth, 0);
    }
    if (sprite2.getPosition().x + windowWidth < 0) {
        sprite2.setPosition(sprite1.getPosition().x + windowWidth, 0);
    }
}

void Background::render(sf::RenderWindow& window) const {
    window.draw(this->sprite1);
    window.draw(this->sprite2);
}
