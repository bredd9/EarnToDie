//
// Created by Vlad on 06-Nov-24.
//
#include <MissileAlert.h>

MissileAlert::MissileAlert() {
    active=false;
    alertDuration=4.0f;
    this->initTexture();
    this->initSprite();
}



void MissileAlert::initTexture() {
    if(!this->texture.loadFromFile("../resources/MissileAlert.png"))

    {

        std::cout << "Error loading texture" << std::endl;

    }
}

void MissileAlert::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0,0,100,100});
    this->sprite.scale(0.8f, 0.8f);
}

MissileAlert::~MissileAlert() {
}




float MissileAlert::getY() const {
    return sprite.getPosition().y;
}

void MissileAlert::alert() {
    active = true;
    timer.restart();

}

bool MissileAlert::isAlerting() const {
    return active && timer.getElapsedTime().asSeconds()<alertDuration;
}


void MissileAlert::update(float playerY) {
    if(isAlerting()) {
        this->sprite.setPosition(1200-this->sprite.getGlobalBounds().width,playerY); // Follow player
    }
    else {
        active=false;
    }
}


void MissileAlert::renderAlert(sf::RenderTarget &target) {
if(isAlerting()) {
    target.draw(this->sprite);
}
}

