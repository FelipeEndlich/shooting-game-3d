#include "game.hpp"

#include <iostream>

#include <GL/glut.h>

#include "../math/vector.hpp"
#include "../graphics/color/rgba_factory.hpp"
#include "../graphics/color/rgba.hpp"
#include "../graphics/shapes/circle.hpp"
#include "../graphics/shapes/rectangle.hpp"
#include "../graphics/elements/obstacle.hpp"

using namespace std;
using namespace math;
using namespace graphics::color;
using namespace graphics::shapes;
using namespace graphics::elements;
using namespace graphics::elements::state;

namespace shoot_and_jump
{
    static Game *instance;

    void idleFunc()
    {
        instance->Idle();
    }

    void displayFunc()
    {
        instance->Display();
    }

    void keyPressedFunc(unsigned char key, int x, int y)
    {
        instance->KeyPressed(key, x, y);
    }

    void keyReleasedFunc(unsigned char key, int x, int y)
    {
        instance->KeyReleased(key, x, y);
    }

    void mouseFunc(int button, int state, int x, int y)
    {
        instance->BindMouse(button, state, x, y);
    }

#pragma region Constructors and Destructors
    Game::Game(string path)
    {
        instance = this;
        Allocate();
        LoadMap(path);
    }

    Game::~Game()
    {
        Deallocate();
    }

    void Game::Allocate()
    {
    }

    void Game::Deallocate()
    {
        delete player_;
        for (auto enemy : enemies_)
            delete enemy;
    }
#pragma endregion // Constructors and Destructors

#pragma region Public Methods
    void Game::Run(int argc, char **argv)
    {
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
        glutInitWindowSize(500, 500);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("2D GAME");

        /* selecionar cor de fundo (preto) */
        RGBA screnColor = RGBAFactory::get_color(ColorOption::kBlack);
        glClearColor(screnColor.get_red(), screnColor.get_green(), screnColor.get_blue(), screnColor.get_alpha());

        glLoadIdentity();
        glOrtho(ortho_left_, ortho_right_, ortho_bottom_, ortho_top_, ortho_near_, ortho_far_);

        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glutMouseFunc(mouseFunc);
        glutKeyboardFunc(keyPressedFunc);
        glutKeyboardUpFunc(keyReleasedFunc);
        glutDisplayFunc(displayFunc);
        glutIdleFunc(idleFunc);

        glutMainLoop();
    }

    void Game::Idle()
    {
        double currentTime = glutGet(GLUT_ELAPSED_TIME);
        delta_time_ = currentTime - this->current_time_;
        if (delta_time_ > 0.1)
        {
            this->current_time_ = currentTime;
            CheckKeys();
            glutPostRedisplay();
        }
    }

    void Game::Display()
    {
        glClear(GL_COLOR_BUFFER_BIT);

        map_.Render();
        player_->Render();
        for (auto &enemy : enemies_)
            enemy->Render();

        glutSwapBuffers();
    }

    void Game::KeyPressed(unsigned char key, int x, int y)
    {
        keys_[key] = true;
    }

    void Game::KeyReleased(unsigned char key, int x, int y)
    {
        keys_[key] = false;
    }

    void Game::BindMouse(int button, int state, int x, int y)
    {
        mouse_[button] = state == GLUT_DOWN;
    }
#pragma endregion // Public Methods

#pragma region Private Methods
    void Game::LoadMap(std::string path)
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
                LoadBackground(rectEl);
            else if (fill == "black")
                LoadObstacle(rectEl);

            rectEl = rectEl->NextSiblingElement("rect");
        }

        tinyxml2::XMLElement *circleEl = root->FirstChildElement("circle");
        while (circleEl != nullptr)
        {
            string fill = circleEl->Attribute("fill");
            if (fill == "green")
                LoadPlayer(circleEl);
            else if (fill == "red")
                LoadEnemy(circleEl);

            circleEl = circleEl->NextSiblingElement("circle");
        }
    }

    void Game::LoadBackground(tinyxml2::XMLElement *element)
    {
        double width = element->DoubleAttribute("width");
        double height = element->DoubleAttribute("height");
        double x = element->DoubleAttribute("x");
        double y = element->DoubleAttribute("y");
        string fill = element->Attribute("fill");
        Vector origin(2);
        origin[0] = x;
        origin[1] = y;

        RGBA color = RGBAFactory::get_color(fill);

        Rectangle background(origin, width, height, color);

        map_.set_background(background);

        ortho_left_ = x;
        ortho_right_ = x + width;
        ortho_top_ = y;
        ortho_bottom_ = y + height;
        ortho_near_ = 20.0;
        ortho_far_ = 0.0;
    }

    void Game::LoadObstacle(tinyxml2::XMLElement *element)
    {
        double width = element->DoubleAttribute("width");
        double height = element->DoubleAttribute("height");
        double x = element->DoubleAttribute("x");
        double y = element->DoubleAttribute("y");
        string fill = element->Attribute("fill");

        Vector origin(2);
        origin[0] = x;
        origin[1] = y;

        RGBA color = RGBAFactory::get_color(fill);

        Obstacle obstacle(origin, width, height, color);
        map_.AddObstacle(obstacle);
    }

    void Game::LoadPlayer(tinyxml2::XMLElement *element)
    {
        double radius = element->DoubleAttribute("r");
        double cx = element->DoubleAttribute("cx");
        double cy = element->DoubleAttribute("cy");
        string fill = element->Attribute("fill");

        Vector origin(2);
        origin[0] = cx;
        origin[1] = cy;

        RGBA color = RGBAFactory::get_color(fill);

        this->player_ = new Character(origin, radius, color);
    }

    void Game::LoadEnemy(tinyxml2::XMLElement *element)
    {
        double radius = element->DoubleAttribute("r");
        double cx = element->DoubleAttribute("cx");
        double cy = element->DoubleAttribute("cy");
        string fill = element->Attribute("fill");

        Vector origin(2);
        origin[0] = cx;
        origin[1] = cy;

        RGBA color = RGBAFactory::get_color(fill);

        enemies_.push_back(new Character(origin, radius, color));
    }

    void Game::CheckKeys()
    {
        // if (keys['a'] && !keys['d'] && mouse[GLUT_RIGHT_BUTTON])
        //     cout << "Jump Left" << endl;

        if (keys_['a'] && !keys_['d'] && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Move(delta_time_, Direction::kLeft);

        // if (!keys['a'] && keys['d'] && mouse[GLUT_RIGHT_BUTTON])
        //     cout << "Jump Right" << endl;

        if (!keys_['a'] && keys_['d'] && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Move(delta_time_, Direction::kRight);

        if (((!keys_['a'] && !keys_['d']) || (keys_['a'] && keys_['d'])) && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Stop(delta_time_);

        // if (((!keys['a'] && !keys['d']) || (keys['a'] && keys['d'])) && mouse[GLUT_RIGHT_BUTTON])
        //     cout << "Jump" << endl;

        // if (mouse[GLUT_LEFT_BUTTON])
        //     cout << "Shoot" << endl;
    }
#pragma endregion // Private Methods
}