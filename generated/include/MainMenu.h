#ifndef MAINMENU_H
#define MAINMENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class MainMenu {
private:
    sf::RenderWindow* window;
    sf::Texture backgroundTexture;
    sf::Texture logoTexture;
    sf::Texture buttonTexture;
    sf::Font font;

    sf::Sprite backgroundSprite;
    sf::Sprite logoSprite;
    std::vector<sf::Sprite> buttons;
    std::vector<sf::Text> buttonTexts;

public:
    MainMenu(sf::RenderWindow* window,
             const std::string& bgPath,
             const std::string& logoPath,
             const std::string& buttonPath,
             const std::string& fontPath);
    ~MainMenu();

    void initTextures(const std::string& bgPath,
                      const std::string& logoPath,
                      const std::string& buttonPath,
                      const std::string& fontPath);
    void initButtons();
    void render() const;
    int handleInput(const sf::Event& event) const;
    void showScoreboard(int highScore);
};

#endif // MAINMENU_H
