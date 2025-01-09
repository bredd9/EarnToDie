//
// Created by Vlad on 05-Nov-24.
//
#include <../include/Missile.h>


Missile::Missile(const std::string& textureFile) : Object(textureFile){
    launched=false;
    speed=-8.0f;
    this->sprite.setTextureRect({0,0,100,64});

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

}


void Missile::updateMissile(float deltaTime) {
    if (this->isLaunched()) {
        // Move the missile
        sprite.move(speed, 0);

        // Check if off-screen
        if (sprite.getPosition().x < -sprite.getGlobalBounds().width) {
            launched = false;
        }

        // Animate the missile
        const int frameWidth = 100;       // Width of a single frame
        const int frameCount = 7;        // Total number of frames
        const float animationSpeed = 0.22f; // Time per frame in seconds

        timer += deltaTime; // Increment the timer by delta time

        // Update the texture rect if enough time has passed for a new frame
        if (timer >= animationSpeed) {
            int currentFrame = (static_cast<int>(timer / animationSpeed) % frameCount);
            sprite.setTextureRect({currentFrame * frameWidth, 0, frameWidth, 64});
            timer -= animationSpeed; // Keep the remainder for smooth transitions
        }
    }
}


void Missile::render(sf::RenderTarget &target) const {
    if(this->isLaunched())
        target.draw(this->sprite);
}


Missile::~Missile()  = default;





