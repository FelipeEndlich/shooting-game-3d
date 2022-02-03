#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./game/game.hpp"
#include "./graphics/color/rgba.hpp"
#include "./graphics/color/rgba_factory.hpp"
#include <cmath>

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;

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

    // Game game(configPath);
    // game.Run(argc, argv);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D GAME");

    /* selecionar cor de fundo (preto) */
    RGBA scren_color = RGBAFactory::get_color(ColorOption::kBlack);
    glClearColor(scren_color.get_red(), scren_color.get_green(), scren_color.get_blue(), scren_color.get_alpha());

    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);

    // Insert shapes here

    glutMainLoop();

    return 0;
}