//
// Created by Vlad on 03-Nov-24.
//
#include "../include/Player.h"

void Player::initTexture() {

    if(!this->texture.loadFromFile("../resources/JetpackWalking.png"))

    {

        std::cout << "Error loading texture" << std::endl;

    }

}

void Player::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0,0,75,100});

    //Resize
    this->sprite.scale(1.0f, 1.0f);
    this->sprite.setPosition(150,791);

}

Player::Player() {
    gravity=1.3f;
    jetpackPower=-2.0f;
    isUsingJetpack=false;
    this->initTexture();
    this->initSprite();

}

Player::Player(const Player &player) {
    this->sprite=player.sprite;
    this->texture=player.texture;
}

Player & Player::operator=(const Player &other) {
    if(this == &other) {
        sprite=other.sprite;
        texture=other.texture;

    }
    return *this;
}

Player::~Player() {

}

void Player::update() {
    //Using the Jetpack
    if(isUsingJetpack)
        velocity.y=jetpackPower;
    else velocity.y=gravity;
    sprite.move(velocity);

    //Not falling off the screen

    if(sprite.getPosition().y<0) {
        sprite.setPosition(sprite.getPosition().x,0);
        velocity.y=0;
    }
    else if(sprite.getPosition().y+sprite.getGlobalBounds().height > 791) {
        sprite.setPosition(sprite.getPosition().x, 791- sprite.getGlobalBounds().height);
        velocity.y=0;

    }



}


void Player::render(sf::RenderTarget &target) {
    target.draw(this->sprite);
}


void Player::useJetpack(bool activate) {
    this->isUsingJetpack=activate;
}

