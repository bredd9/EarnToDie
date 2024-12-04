//
// Created by Vlad on 04-Dec-24.

#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MainMenu {
private:
    sf::RenderWindow* window;

    // Background and logo
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Texture logoTexture;
    sf::Sprite logoSprite;

    // Buttons
    sf::Texture buttonTexture;
    std::vector<sf::Sprite> buttons;      // Vector to hold button sprites
    std::vector<sf::Text> buttonTexts;    // Vector to hold button labels
    sf::Font font;

    void initTextures(const std::string& bgPath, const std::string& logoPath, const std::string& buttonPath, const std::string& fontPath);
    void initButtons();                   // Initialize buttons and labels

public:
    MainMenu(sf::RenderWindow* window, const std::string& bgPath, const std::string& logoPath, const std::string& buttonPath, const std::string& fontPath);
    ~MainMenu();

    void render() const;                  // Render the menu
    int handleInput(const sf::Event& event) const; // Handle user input and return the clicked button index
};
#endif // MAINMENU_H

