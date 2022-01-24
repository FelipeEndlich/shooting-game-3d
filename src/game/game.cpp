#include "game.hpp"
#include "../math/vector.hpp"
#include "../graphics/color/rgbaFactory.hpp"
#include "../graphics/color/rgba.hpp"
#include "../graphics/shapes/circle.hpp"
#include "../graphics/shapes/rectangle.hpp"
#include <GL/glut.h>

using namespace game;
using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace std;

Game::Game(string path)
{
    deltaTime = 0.0;

    Vector origin(2);
    origin[0] = -0.5;
    origin[1] = -0.5;

    RGBA color(0, 0, 255);

    Rectangle background(origin, 1, 1, color);

    map.setBackground(background);
}
Game::~Game()
{
}

void Game::update(double deltaTime)
{
    this->deltaTime = deltaTime;
}

void Game::render(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D GAME");

    /* selecionar cor de fundo (preto) */
    RGBA screnColor = RGBAFactory::getColor(RGBAFactory::Color::BLACK);
    glClearColor(screnColor.getR(), screnColor.getG(), screnColor.getB(), screnColor.getA());

    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 2.0, 0.0);

    glClear(GL_COLOR_BUFFER_BIT);
    map.render();
    glutSwapBuffers();

    glutMainLoop();
}