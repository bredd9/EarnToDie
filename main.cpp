#include <Game.h>

int main()
{
    srand(static_cast<unsigned int>(time(NULL)));

    Game game;

    while(game.running()) {
        game.update();
        game.render();
    }

    return 0;
}
