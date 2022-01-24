#include "game.hpp"
#include "../math/vector.hpp"
#include "../graphics/color/rgbaFactory.hpp"
#include "../graphics/color/rgba.hpp"
#include "../graphics/shapes/circle.hpp"
#include "../graphics/shapes/rectangle.hpp"
#include "../graphics/elements/obstacle.hpp"
#include <GL/glut.h>
#include <iostream>

using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace graphics::elements;
using namespace std;

namespace game
{
    static Game *instance;

    void idleFunc()
    {
        instance->idle();
    }

    void displayFunc()
    {
        instance->display();
    }

    void keyPressedFunc(unsigned char key, int x, int y)
    {
        instance->keyPressed(key, x, y);
    }

    void keyReleasedFunc(unsigned char key, int x, int y)
    {
        instance->keyReleased(key, x, y);
    }

    void mouseFunc(int button, int state, int x, int y)
    {
        instance->bindMouse(button, state, x, y);
    }

#pragma region Constructors and Destructors
    Game::Game(string path)
    {
        instance = this;
        loadMap(path);
    }
#pragma endregion // Constructors and Destructors

#pragma region Public Methods
    void Game::update(double deltaTime)
    {
        this->deltaTime = deltaTime;
    }

    void Game::run(int argc, char **argv)
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

        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glutMouseFunc(mouseFunc);
        glutKeyboardFunc(keyPressedFunc);
        glutKeyboardUpFunc(keyReleasedFunc);
        glutDisplayFunc(displayFunc);
        glutIdleFunc(idleFunc);

        glutMainLoop();
    }

    void Game::idle()
    {
        checkKeys();
        glutPostRedisplay();
    }

    void Game::display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        map.render();
        player.render();
        for (auto &enemy : enemies)
            enemy.render();

        glutSwapBuffers();
    }

    void Game::keyPressed(unsigned char key, int x, int y)
    {
        keys[key] = true;
    }

    void Game::keyReleased(unsigned char key, int x, int y)
    {
        keys[key] = false;
    }

    void Game::bindMouse(int button, int state, int x, int y)
    {
        mouse[button] = state == GLUT_DOWN;
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

    void Game::loadObstacle(tinyxml2::XMLElement *element)
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

        Obstacle obstacle(origin, width, height, color);
        map.addObstacle(obstacle);
    }

    void Game::loadPlayer(tinyxml2::XMLElement *element)
    {
        double radius = element->DoubleAttribute("r");
        double cx = element->DoubleAttribute("cx");
        double cy = element->DoubleAttribute("cy");
        string fill = element->Attribute("fill");

        Vector origin(2);
        origin[0] = cx;
        origin[1] = cy;

        RGBA color = RGBAFactory::getColor(fill);

        Character player(origin, radius, color);

        this->player = player;
    }

    void Game::loadEnemy(tinyxml2::XMLElement *element)
    {
        double radius = element->DoubleAttribute("r");
        double cx = element->DoubleAttribute("cx");
        double cy = element->DoubleAttribute("cy");
        string fill = element->Attribute("fill");

        Vector origin(2);
        origin[0] = cx;
        origin[1] = cy;

        RGBA color = RGBAFactory::getColor(fill);

        Character enemy(origin, radius, color);

        enemies.push_back(enemy);
    }

    void Game::checkKeys()
    {
        if (keys['a'] && !keys['d'] && mouse[GLUT_LEFT_BUTTON])
            cout << "Jump Left" << endl;

        if (keys['a'] && !keys['d'] && !mouse[GLUT_LEFT_BUTTON])
            cout << "Walk Left" << endl;

        if (!keys['a'] && keys['d'] && mouse[GLUT_LEFT_BUTTON])
            cout << "Jump Right" << endl;

        if (!keys['a'] && keys['d'] && !mouse[GLUT_LEFT_BUTTON])
            cout << "Walk Right" << endl;

        if (((!keys['a'] && !keys['d']) || (keys['a'] && keys['d'])) && mouse[GLUT_LEFT_BUTTON])
            cout << "Jump" << endl;

        if (mouse[GLUT_RIGHT_BUTTON])
            cout << "Shoot" << endl;
    }
#pragma endregion // Private Methods
}