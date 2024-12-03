//
// Created by Vlad on 02-Dec-24.
//
#include <Object.h>

Object::Object(const std::string& textureFile)
    {
    if (!texture.loadFromFile(textureFile)) {
        throw std::runtime_error("Failed to load texture");

    }
    sprite.setTexture(texture);
    }

Object::~Object() {

}



