//
// Created by Vlad on 01-Dec-24.
//

#include <Background.h>

Background::Background() {

}

bool Background::initialize(const std::string& filepath, const float scrollSpeed, const int windowWidth, const int windowHeight) {
    this->speed = scrollSpeed;
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;

    if (!texture.loadFromFile(filepath)) {
        std::cout << "Failed to load background image " << "\n";
        return false; // Initialization failed
    }

    // Set the texture for the sprites
    sprite1.setTexture(texture);
    sprite2.setTexture(texture);

    // Adjust sizes if necessary
    sf::Vector2u textureSize = texture.getSize();
    float scaleX = static_cast<float>(windowWidth) / textureSize.x;
    float scaleY = static_cast<float>(windowHeight) / textureSize.y;
    sprite1.setScale(scaleX, scaleY);
    sprite2.setScale(scaleX, scaleY);

    // Set the initial positions
    sprite1.setPosition(0, 0);
    sprite2.setPosition(windowWidth, 0);

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
