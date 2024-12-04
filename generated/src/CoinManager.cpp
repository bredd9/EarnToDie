//
// Created by Vlad on 03-Dec-24.
//

#include "CoinManager.h"
#include <cstdlib>
#include <ctime>

CoinManager::CoinManager(const std::string& coinTexture, const sf::Vector2f& windowSize, float scrollSpeed)
    : windowSize(windowSize) {
    this->speed = scrollSpeed;
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random number generator
    for (int i = 0; i < 50; ++i) {
        coins.emplace_back(coinTexture);
    }
}

// Helper: Spawn coins in a line
void CoinManager::spawnLine(int count, float startX, float startY, float spacing) {
    for (int i = 0; i < count; ++i) {
        Coin coin("../resources/Coin.png");
        coin.spawnAt(startX + i * spacing, startY );
        coins.push_back(std::move(coin));
    }
}

// Helper: Spawn coins in a wave
void CoinManager::spawnWave(int count, float startX, float startY, float amplitude, float frequency) {
    for (int i = 0; i < count; ++i) {
        float x = startX - i * 50.f; // Offset coins horizontally
        float y = startY + amplitude * std::sin(frequency * i);
        Coin coin("../resources/Coin.png");
        coin.spawnAt(x, y);
        coins.push_back(std::move(coin));
    }
}

// Helper: Spawn coins in a square
void CoinManager::spawnSquare(int count, float startX, float startY, float sideLength) {
    int side = count / 4; // Divide coins evenly along the square sides
    for (int i = 0; i < count; ++i) {
        float x, y;
        if (i < side) { // Top side
            x = startX + i * (sideLength / side);
            y = startY;
        } else if (i < 2 * side) { // Right side
            x = startX + sideLength;
            y = startY + (i - side) * (sideLength / side);
        } else if (i < 3 * side) { // Bottom side
            x = startX + sideLength - (i - 2 * side) * (sideLength / side);
            y = startY + sideLength;
        } else { // Left side
            x = startX;
            y = startY + sideLength - (i - 3 * side) * (sideLength / side);
        }
        Coin coin("../resources/Coin.png");
        coin.spawnAt(x, y);
        coins.push_back(std::move(coin));
    }
}

// Spawn a random shape of coins
void CoinManager::spawnRandomShape() {
    switch (std::rand() % 3) {
        case 0: // Line
            spawnLine(10, windowSize.x, windowSize.y / 2.f, 30.f);
        break;
        case 1: // Wave
            spawnWave(10, windowSize.x, windowSize.y / 2.f, 50.f, 0.5f);
        break;
        case 2: // Square
            spawnSquare(16, windowSize.x + 100.f, windowSize.y / 3.f, 100.f);
        break;
        default: ;
    }
}

// Update: Move coins and remove off-screen ones
void CoinManager::update() {

    for (auto& coin : coins) {
        coin.updateMovement(-speed, 0.f); // Move left at a constant speed
    }

    // Remove coins that are off the screen
    coins.erase(std::remove_if(coins.begin(), coins.end(),
                               [this](const Coin& coin) {
                                   return coin.getX() + coin.getWidth() < 0; // Off the left side
                               }),
                coins.end());

    // Check if it's time to spawn a new sequence
    if (spawnClock.getElapsedTime().asSeconds() > spawnInterval) {
        spawnRandomShape();
        spawnClock.restart();
    }
}

// Render: Draw all coins
void CoinManager::render(sf::RenderTarget& target) const {
    for (const auto& coin : coins) {
        coin.render(target);
    }
}


