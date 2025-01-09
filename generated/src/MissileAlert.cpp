//
// Created by Vlad on 06-Nov-24.
//
#include <../include/MissileAlert.h>

MissileAlert::MissileAlert(const std::string& textureFile) : Object(textureFile) {
    active = false;
    alertDuration = 4.0f;
    this->sprite.setTextureRect({0, 0, 100, 100});

    // Scaling sprite
    this->sprite.scale(0.8f, 0.8f);

    // Define animation frames
    std::vector<sf::IntRect> frames = {
        {0, 0, 100, 100},   // Frame 1
        {100, 0, 100, 100}, // Frame 2
    };

    // Initialize animator
    animator = new Animate(sprite, frames, 2.5f); // Animation speed: 0.2 seconds per frame
}

MissileAlert::~MissileAlert() = default;


float MissileAlert::getY() const {
    return sprite.getPosition().y;
}

void MissileAlert::alert() {
    active = true;
    timer.restart();

}

bool MissileAlert::isAlerting() const {
    return active && (timer.getElapsedTime().asSeconds()<alertDuration && timer.getElapsedTime().asSeconds()>0.0f);
}


void MissileAlert::update(){
}

void MissileAlert::updateAlert(float playerY, float deltaTime) {
    if(isAlerting()) {
        this->sprite.setPosition(1200-this->sprite.getGlobalBounds().width,playerY); // Follow player
        animator->update(deltaTime);
    }
    else {
        active=false;
    }
}


void MissileAlert::render(sf::RenderTarget &target) const {
    if(isAlerting()) {
        target.draw(this->sprite);
    }
}

