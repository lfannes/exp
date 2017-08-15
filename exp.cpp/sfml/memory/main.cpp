#include "game.hpp"

using namespace std;

int main()
{
    Game game;

    while (game.ok())
    {
        game.process();
        game.update();
        game.draw();
    };

    return 0;
}
