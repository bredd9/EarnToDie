//
// Created by Vlad on 05-Nov-24.
//
#include <../include/Missile.h>


Missile::Missile(const std::string& textureFile) : Object(textureFile){
    launched=false;
    speed=-3.0f;
    this->sprite.setTextureRect({0,0,64,64});

    //Resize
    this->sprite.scale(1.0f, 1.0f);

}

bool Missile::isLaunched() const {
    return launched;
}


void Missile::launch(const float yPosition){
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

void Missile::render(sf::RenderTarget &target) const {
    if(this->isLaunched())
        target.draw(this->sprite);
}


Missile::~Missile()  {

}






