//
// Created by Vlad on 03-Dec-24.
//
#include <Coin.h>

float Coin::randomFloat(float min, float max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

Coin::Coin(const std::string& textureFile) : Object(textureFile), speed(150.f) {
    this->sprite.setTextureRect({0,0,40,40});
    this->sprite.setScale(1.f, 1.f);
    this->sprite.setRotation(randomFloat(0.f, 360.f));
}

Coin::~Coin() {}

void Coin::updateMovement(float offsetX, float offsetY) {
    this->sprite.move(offsetX, offsetY); // Move the coin
}

void Coin::update() {
}

void Coin::render(sf::RenderTarget& target) const {
    target.draw(this->sprite);
}

void Coin::spawnAt(float x, float y) {
    this->sprite.setPosition(x, y);
}

float Coin::getY() const {
    return this->sprite.getPosition().y;
}

float Coin::getX() const {
    return this->sprite.getPosition().x;
}

float Coin::getWidth() const {
    return this->sprite.getGlobalBounds().width;
}
