//
// Created by Vlad on 06-Nov-24.
//
#include <../include/MissileAlert.h>

MissileAlert::MissileAlert(const std::string& textureFile) :Object(textureFile) {
    active=false;
    alertDuration=4.0f;
    this->sprite.setTextureRect({0,0,100,100});

    //Scaling sprite
    this->sprite.scale(0.8f, 0.8f);
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

void MissileAlert::updateAlert(float playerY) {
    if(isAlerting()) {
        this->sprite.setPosition(1200-this->sprite.getGlobalBounds().width,playerY); // Follow player
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


