#include <Animate.h>

Animate::Animate(sf::Sprite& sprite, const std::vector<sf::IntRect>& frames, float animationSpeed)
    : sprite(sprite), frames(frames), animationSpeed(animationSpeed), timeSinceLastFrame(0.0f), currentFrame(0) {}

void Animate::update(float deltaTime) {
    timeSinceLastFrame += deltaTime;

    if (timeSinceLastFrame >= animationSpeed) {
        // Switch to the next frame
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);

        // Reset the timer
        timeSinceLastFrame = 0.0f;
    }
}

void Animate::reset() {
    currentFrame = 0;
    timeSinceLastFrame = 0.0f;
}
