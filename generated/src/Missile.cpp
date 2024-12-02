//
// Created by Vlad on 05-Nov-24.
//
#include <../include/Missile.h>


void Missile::initTexture() {

    if(!this->texture.loadFromFile("../resources/Missile.png"))
    {
        std::cout << "Error loading texture" << std::endl;
    }

}

void Missile::initSprite() {
    this->sprite.setTexture(this->texture);
    this->sprite.setTextureRect({0,0,64,64});

    //Resize
    this->sprite.scale(1.0f, 1.0f);

}

bool Missile::isLaunched() const {
    return launched;
}


Missile::Missile() {
    launched=false;
    speed=-3.0f;
    this->initTexture();
    this->initSprite();
}


void Missile::launch(float yPosition){
    this->sprite.setPosition(1200,yPosition);
    launched=true;
}

void Missile::update() {
    //Launching the missile

    if (this->isLaunched()) {
        sprite.move(speed,0);
        if(sprite.getPosition().x<0)
            launched=false;
    }
}

void Missile::renderMissile(sf::RenderTarget &target) {
    if(this->isLaunched())
        target.draw(this->sprite);
}


Missile::~Missile() {

}






