#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./game/game.hpp"
#include "./graphics/color/rgba.hpp"
#include "./graphics/color/rgba_factory.hpp"
#include "./graphics/shapes/sphere.hpp"
#include <cmath>
#include "./math/matrix.hpp"
#include "./math/vector.hpp"

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
using ::graphics::shapes::Sphere;
using ::math::Vector;
// using ::graphics::shapes::Cuboid;

void displayFunc(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glRotatef(0.1, 1, 0, 0); // Rotate x axis
    glRotatef(0.1, 0, 1, 0); // Rotate y axis
    glRotatef(0.1, 0, 0, 1); // Rotate z axis

    Sphere sphere(30, Vector::Zero(3), RGBAFactory::get_color(ColorOption::kWhite));
    sphere.Draw();

    glutSwapBuffers();
}

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
    glEnable(GL_DEPTH_TEST);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D GAME");

    glutDisplayFunc(displayFunc);

    glutIdleFunc([]()
                 { glutPostRedisplay(); });

    /* selecionar cor de fundo (preto) */
    RGBA scren_color = RGBAFactory::get_color(ColorOption::kBlack);
    glClearColor(scren_color.get_red(), scren_color.get_green(), scren_color.get_blue(), scren_color.get_alpha());

    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);

    glutMainLoop();

    return 0;
}