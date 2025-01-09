#include "MainMenu.h"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow* window, 
                   const std::string& bgPath, 
                   const std::string& logoPath, 
                   const std::string& buttonPath, 
                   const std::string& fontPath)
    : window(window) {
    this->initTextures(bgPath, logoPath, buttonPath, fontPath);
    this->initButtons();
}

MainMenu::~MainMenu() {}

void MainMenu::initTextures(const std::string& bgPath, 
                            const std::string& logoPath, 
                            const std::string& buttonPath, 
                            const std::string& fontPath) {
    // Load textures and font
    if (!backgroundTexture.loadFromFile(bgPath)) {
        throw std::runtime_error("Failed to load background texture from " + bgPath);
    }
    backgroundSprite.setTexture(backgroundTexture);

    if (!logoTexture.loadFromFile(logoPath)) {
        throw std::runtime_error("Failed to load logo texture from " + logoPath);
    }
    logoSprite.setTexture(logoTexture);

    if (!buttonTexture.loadFromFile(buttonPath)) {
        throw std::runtime_error("Failed to load button texture from " + buttonPath);
    }

    if (!font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load font from " + fontPath);
    }
}

void MainMenu::initButtons() {
    // Button titles
    std::vector<std::string> titles = {"PLAY", "SCOREBOARD"};

    // Set positions for the background and logo
    backgroundSprite.setPosition(0.f, 0.f);
    logoSprite.setPosition(125.f, 250.f);

    // Calculate button positions on the right
    float startX = window->getSize().x - buttonTexture.getSize().x - 50.f;
    float startY = window->getSize().y / 2.f -
                   (titles.size() * (buttonTexture.getSize().y + 20.f)) / 2.f;

    for (size_t i = 0; i < titles.size(); ++i) {
        // Create button sprite
        sf::Sprite button;
        button.setTexture(buttonTexture);
        button.setPosition(startX, startY + i * (buttonTexture.getSize().y + 20.f));

        // Create button label
        sf::Text text;
        text.setFont(font);
        text.setString(titles[i]);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setOutlineThickness(3.f);
        text.setOutlineColor(sf::Color::Black);

        // Center text on the button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            button.getPosition().x + buttonTexture.getSize().x / 2.f - textBounds.width / 2.f,
            button.getPosition().y + buttonTexture.getSize().y / 2.f - textBounds.height / 2.f - textBounds.top
        );

        buttons.push_back(button);
        buttonTexts.push_back(text);
    }
}

void MainMenu::render() const {
    // Draw background and logo
    window->draw(backgroundSprite);
    window->draw(logoSprite);

    // Draw buttons and labels
    for (const auto& button : buttons) {
        window->draw(button);
    }
    for (const auto& text : buttonTexts) {
        window->draw(text);
    }
}

int MainMenu::handleInput(const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (size_t i = 0; i < buttons.size(); ++i) {
            if (buttons[i].getGlobalBounds().contains(mousePos)) {
                return static_cast<int>(i); // Return index of clicked button
            }
        }
    }
    return -1; // No button clicked
}

void MainMenu::showScoreboard(int highScore) {
    sf::Sprite goBackButton;
    goBackButton.setTexture(buttonTexture);
    goBackButton.setPosition(
        window->getSize().x / 2.f - buttonTexture.getSize().x / 2.f,
        window->getSize().y / 2.f + 100.f
    );

    sf::Text goBackText;
    goBackText.setFont(font);
    goBackText.setString("GO BACK");
    goBackText.setCharacterSize(45);
    goBackText.setFillColor(sf::Color::White);
    goBackText.setStyle(sf::Text::Bold);
    goBackText.setOutlineThickness(3.f);
    goBackText.setOutlineColor(sf::Color::Black);

    sf::FloatRect goBackTextBounds = goBackText.getLocalBounds();
    goBackText.setPosition(
        goBackButton.getPosition().x + buttonTexture.getSize().x / 2.f - goBackTextBounds.width / 2.f,
        goBackButton.getPosition().y + buttonTexture.getSize().y / 2.f - goBackTextBounds.height / 2.f - goBackTextBounds.top
    );

    while (window->isOpen()) {
        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                if (goBackButton.getGlobalBounds().contains(mousePos)) {
                    return; // Go back to the main menu
                }
            }
        }

        window->clear();

        // Draw background
        window->draw(backgroundSprite);

        // High score button
        sf::Sprite highScoreButton;
        highScoreButton.setTexture(buttonTexture);
        highScoreButton.setPosition(
            window->getSize().x / 2.f - buttonTexture.getSize().x / 2.f,
            window->getSize().y / 2.f - 50.f
        );
        window->draw(highScoreButton);

        // High score label
        sf::Text highScoreLabel;
        highScoreLabel.setFont(font);
        highScoreLabel.setString("HIGHSCORE");
        highScoreLabel.setCharacterSize(45);
        highScoreLabel.setFillColor(sf::Color::White);
        highScoreLabel.setStyle(sf::Text::Bold);
        highScoreLabel.setOutlineThickness(3.f);
        highScoreLabel.setOutlineColor(sf::Color::Black);

        sf::FloatRect textBounds = highScoreLabel.getLocalBounds();
        highScoreLabel.setPosition(
            highScoreButton.getPosition().x + buttonTexture.getSize().x / 2.f - textBounds.width / 2.f,
            highScoreButton.getPosition().y - textBounds.height - 20.f
        );
        window->draw(highScoreLabel);

        // High score text
        sf::Text highScoreText;
        highScoreText.setFont(font);
        highScoreText.setString(std::to_string(highScore));
        highScoreText.setCharacterSize(45);
        highScoreText.setFillColor(sf::Color::White);
        highScoreText.setStyle(sf::Text::Bold);
        highScoreText.setOutlineThickness(3.f);
        highScoreText.setOutlineColor(sf::Color::Black);

        sf::FloatRect scoreTextBounds = highScoreText.getLocalBounds();
        highScoreText.setPosition(
            highScoreButton.getPosition().x + buttonTexture.getSize().x / 2.f - scoreTextBounds.width / 2.f,
            highScoreButton.getPosition().y + buttonTexture.getSize().y / 2.f - scoreTextBounds.height / 2.f - scoreTextBounds.top
        );
        window->draw(highScoreText);

        // Go back button
        window->draw(goBackButton);
        window->draw(goBackText);

        window->display();
    }
}
