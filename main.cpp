#include <Game.h>

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));
    sf::Clock clock;
    Game game;
    float deltaTime = clock.restart().asSeconds();

    while(game.running()) {
        game.update(deltaTime);
        game.render();
    }

    return 0;
}
