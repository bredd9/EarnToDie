//
// Created by Vlad on 03-Dec-24.
//

#ifndef COINMANAGER_H
#define COINMANAGER_H

#include "Coin.h"
#include <vector>
#include <SFML/Graphics.hpp>

class CoinManager {
private:
    std::vector<Coin> coins;     // Coins currently active
    const float spawnInterval = 10.f; // Time between spawns
    sf::Vector2f windowSize;     // Window size for bounds
    sf::Clock spawnClock;        // Timer to track spawning
    float speed;                 // Speed of coin movement

    // Helper methods for spawning coins in various shapes
    void spawnLine(int count, float startX, float startY, float spacing);
    void spawnWave(int count, float startX, float startY, float amplitude, float frequency);
    void spawnSquare(int count, float startX, float startY, float sideLength);

public:
    CoinManager(const std::string& coinTexture, const sf::Vector2f& windowSize, float speed);

    void update();                            // Move coins and remove off-screen ones
    void render(sf::RenderTarget& target) const;    // Render coins
    void spawnRandomShape();                  // Spawn coins in a random shape
};

#endif // COINMANAGER_H

