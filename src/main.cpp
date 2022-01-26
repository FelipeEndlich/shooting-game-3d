#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./game/game.hpp"
#include <cmath>
using namespace shoot_and_jump;

int main(int argc, char **argv)
{
    if (argc > 2)
    {
        cout << "Too many arguments" << endl;
        return 1;
    }
    else if (argc < 2)
    {
        cout << "Too few arguments" << endl;
        return 1;
    }
    string configPath = argv[1];

    Game game(configPath);
    game.Run(argc, argv);

    return 0;
}