//
// Created by Vlad on 04-Dec-24.
//
#include <MainMenu.h>

MainMenu::MainMenu(sf::RenderWindow* window, const std::string& bgPath, const std::string& logoPath, const std::string& buttonPath, const std::string& fontPath)
    : window(window) {
    this->initTextures(bgPath, logoPath, buttonPath, fontPath);
    this->initButtons();
}

MainMenu::~MainMenu() {}

void MainMenu::initTextures(const std::string& bgPath, const std::string& logoPath, const std::string& buttonPath, const std::string& fontPath) {
    if (!this->backgroundTexture.loadFromFile(bgPath)) {
        throw std::runtime_error("Failed to load Menu Background");
    }
    if (!this->logoTexture.loadFromFile(logoPath)) {
        throw std::runtime_error("Failed to load Logo");
    }
    if (!this->buttonTexture.loadFromFile(buttonPath)) {
        throw std::runtime_error("Failed to load Button");
    }
    if (!this->font.loadFromFile(fontPath)) {
        throw std::runtime_error("Failed to load Font");
    }

    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->logoSprite.setTexture(this->logoTexture);
}

void MainMenu::initButtons() {
    // Button titles
    std::vector<std::string> titles = {"PLAY", "SCOREBOARD", "RULES"};

    // Set positions for the background and logo
    this->backgroundSprite.setPosition(0.f, 0.f); // Fill the window
    this->logoSprite.setPosition(125.f, 250.f);     // Place the logo on the left

    // Calculate button positions on the right
    float startX = this->window->getSize().x - this->buttonTexture.getSize().x - 50.f;
    float startY = this->window->getSize().y / 2.f -
                   (titles.size() * (this->buttonTexture.getSize().y + 20.f)) / 2.f;

    for (size_t i = 0; i < titles.size(); ++i) {
        // Create button sprite
        sf::Sprite button;
        button.setTexture(this->buttonTexture);
        button.setPosition(startX, startY + i * (this->buttonTexture.getSize().y + 20.f));

        // Create button label
        sf::Text text;
        text.setFont(this->font);
        text.setString(titles[i]);
        text.setCharacterSize(45);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setOutlineThickness(3.f); // Thickness of the outline
        text.setOutlineColor(sf::Color::Black); // Black outline

        // Center text on the button
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setPosition(
            button.getPosition().x + this->buttonTexture.getSize().x / 2.f - textBounds.width / 2.f,
            button.getPosition().y + this->buttonTexture.getSize().y / 2.f - textBounds.height / 2.f - textBounds.top
        );

        // Add button and label to vectors
        this->buttons.push_back(button);
        this->buttonTexts.push_back(text);
    }
}

void MainMenu::render() const {
    // Draw background and logo
    this->window->draw(this->backgroundSprite);
    this->window->draw(this->logoSprite);

    // Draw buttons and labels
    for (const auto& button : this->buttons) {
        this->window->draw(button);
    }
    for (const auto& text : this->buttonTexts) {
        this->window->draw(text);
    }
}

int MainMenu::handleInput(const sf::Event& event) const {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);

        for (size_t i = 0; i < this->buttons.size(); ++i) {
            if (this->buttons[i].getGlobalBounds().contains(mousePos)) {
                return static_cast<int>(i); // Return the index of the clicked button
            }
        }
    }
    return -1; // No button clicked
}
