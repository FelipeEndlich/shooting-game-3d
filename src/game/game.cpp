#include "game.hpp"
#include "../math/vector.hpp"
#include "../graphics/color/rgbaFactory.hpp"
#include "../graphics/color/rgba.hpp"
#include "../graphics/shapes/circle.hpp"
#include "../graphics/shapes/rectangle.hpp"
#include "../graphics/elements/obstacle.hpp"
#include <GL/glut.h>
#include <iostream>

using namespace game;
using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace graphics::elements;
using namespace std;

#pragma region Constructors and Destructors
Game::Game(string path)
{
    loadMap(path);
}
#pragma endregion // Constructors and Destructors

#pragma region Public Methods
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
    glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoNear, orthoFar);

    glClear(GL_COLOR_BUFFER_BIT);
    map.render();
    glutSwapBuffers();

    glutMainLoop();
}
#pragma endregion // Public Methods

#pragma region Private Methods
void Game::loadMap(std::string path)
{
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());

    tinyxml2::XMLElement *root = doc.FirstChildElement("svg");

    if (root == nullptr)
    {
        throw "Configuration not found";
    }

    tinyxml2::XMLElement *rectEl = root->FirstChildElement("rect");
    while (rectEl != nullptr)
    {
        string fill = rectEl->Attribute("fill");
        if (fill == "blue")
            loadBackground(rectEl);
        else if (fill == "black")
            loadObstacle(rectEl);

        rectEl = rectEl->NextSiblingElement("rect");
    }

    tinyxml2::XMLElement *circleEl = root->FirstChildElement("circle");
    while (circleEl != nullptr)
    {
        string fill = circleEl->Attribute("fill");
        if (fill == "green")
            loadPlayer(circleEl);
        else if (fill == "red")
            loadEnemy(circleEl);

        circleEl = circleEl->NextSiblingElement("circle");
    }
}

void Game::loadBackground(tinyxml2::XMLElement *element)
{
    double width = element->DoubleAttribute("width");
    double height = element->DoubleAttribute("height");
    double x = element->DoubleAttribute("x");
    double y = element->DoubleAttribute("y");
    string fill = element->Attribute("fill");
    Vector origin(2);
    origin[0] = x;
    origin[1] = y;

    RGBA color = RGBAFactory::getColor(fill);

    Rectangle background(origin, width, height, color);

    map.setBackground(background);

    orthoLeft = x;
    orthoRight = x + width;
    orthoTop = y;
    orthoBottom = y + height;
    orthoNear = 20.0;
    orthoFar = 0.0;
}

void Game::loadObstacle(tinyxml2::XMLElement *obstacles)
{
    double width = obstacles->DoubleAttribute("width");
    double height = obstacles->DoubleAttribute("height");
    double x = obstacles->DoubleAttribute("x");
    double y = obstacles->DoubleAttribute("y");
    string fill = obstacles->Attribute("fill");

    Vector origin(2);
    origin[0] = x;
    origin[1] = y;

    RGBA color = RGBAFactory::getColor(fill);

    Obstacle obstacle(origin, width, height, color);
    map.addObstacle(obstacle);
}

void Game::loadPlayer(tinyxml2::XMLElement *player)
{
    cout << "Player" << endl;
}

void Game::loadEnemy(tinyxml2::XMLElement *enemies)
{
    cout << "Enemy" << endl;
}
#pragma endregion // Private Methods