#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./graphics/shapes/rectangle.hpp"
#include "./graphics/shapes/circle.hpp"
#include "./graphics/color/rgb.hpp"
#include "./math/vector.hpp"
#include <cmath>
using namespace graphics::shapes;
using namespace graphics::color;
using namespace math;

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

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D GAME");

    /* selecionar cor de fundo (preto) */
    glClearColor(0.0, 0.0, 0.0, 0.0);

    /* inicializar sistema de visualizacao */
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    Vector origin(2);
    origin[0] = 0;
    origin[1] = 0;

    Vector center(2);
    center[0] = 0.0;
    center[1] = 0.0;

    Vector translate(2);
    translate[0] = 2.0;
    translate[1] = 0.0;

    Vector scale(2);
    scale[0] = 0.25;
    scale[1] = 0.25;

    RGBA color(255, 100, 0, 255);

    Circle circle(origin, 0.5, color);
    circle.draw();

    glClear(GL_COLOR_BUFFER_BIT);
    circle.scale(center, scale);
    circle.draw();

    glutSwapBuffers();

    glutMainLoop();

    return 0;
}