#include "game.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>
#include <tuple>

#include <GL/glut.h>

#include "../math/vector.hpp"
#include "../graphics/color/rgba_factory.hpp"
#include "../graphics/color/rgba.hpp"
#include "../graphics/shapes/circle.hpp"
#include "../graphics/shapes/rectangle.hpp"
#include "../graphics/elements/obstacle.hpp"
#include "../physics/direction.hpp"

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
using ::graphics::elements::Obstacle;
using ::graphics::elements::character::Character;
using ::graphics::shapes::Circle;
using ::graphics::shapes::Rectangle;
using ::math::Vector;
using ::physic::CollisionSystem;
using ::physic::Direction;
using ::physic::ICollidable;
using ::physic::IGravityAffectable;
using ::std::cout;
using ::std::endl;
using ::std::get;
using ::std::max;
using ::std::min;
using ::std::string;

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
        instance->BindMouseButton(button, state, x, y);
    }

    void motionPassifeFunc(int x, int y)
    {
        instance->BindMouseMotion(x, y);
    }

#pragma region Constructors and Destructors
    Game::Game(string path)
    {
        instance = this;
        Allocate();
        LoadMap(path);
        get<0>(mouse_position_) = 1;
        window_width_ = 500;
        window_height_ = 500;
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
        glutInitWindowSize(window_width_, window_height_);
        glutInitWindowPosition(100, 100);
        glutCreateWindow("2D GAME");

        /* selecionar cor de fundo (preto) */
        RGBA scren_color = RGBAFactory::get_color(ColorOption::kBlack);
        glClearColor(scren_color.get_red(), scren_color.get_green(), scren_color.get_blue(), scren_color.get_alpha());

        glLoadIdentity();
        glOrtho(ortho_left_, ortho_right_, ortho_bottom_, ortho_top_, ortho_near_, ortho_far_);

        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
        glutMouseFunc(mouseFunc);
        glutPassiveMotionFunc(motionPassifeFunc);
        glutKeyboardFunc(keyPressedFunc);
        glutKeyboardUpFunc(keyReleasedFunc);
        glutDisplayFunc(displayFunc);
        glutIdleFunc(idleFunc);

        glutMainLoop();
    }

    void Game::Idle()
    {
        double current_time = glutGet(GLUT_ELAPSED_TIME);
        delta_time_ = current_time - this->current_time_;
        if (delta_time_ > 0.1)
        {
            this->current_time_ = current_time;

            Vector old_position = player_->get_position();

            CheckKeys();
            collision_system_.ProcessCollisions();
            gravity_constraint_system_.ProcessGravityEffects();

            Vector translation = old_position - player_->get_position();
            glTranslated(translation[0], 0, 0);

            Vector mouse_position(2);
            mouse_position[0] = get<0>(mouse_position_);

            if (player_->IsLookingRight())
                mouse_position[1] = ((ortho_bottom_ - player_->get_position()[1]) / (ortho_bottom_ - ortho_top_)) * window_height_ - get<1>(mouse_position_);
            else
                mouse_position[1] = get<1>(mouse_position_) - ((ortho_bottom_ - player_->get_position()[1]) / (ortho_bottom_ - ortho_top_)) * window_height_;

            double angle = atan2(mouse_position[1], mouse_position[0]);

            if (angle > M_PI / 2)
                angle = M_PI - angle;

            if (angle < -M_PI / 2)
                angle = -M_PI - angle;

            angle = max(angle, -M_PI / 4);
            angle = min(angle, M_PI / 4);

            player_->Aim(angle);

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

    void Game::BindMouseButton(int button, int state, int x, int y)
    {
        mouse_[button] = state == GLUT_DOWN;
    }

    void Game::BindMouseMotion(int x, int y)
    {
        get<0>(mouse_position_) = x - window_width_ / 2;
        get<1>(mouse_position_) = window_height_ - y;
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

        tinyxml2::XMLElement *circle_element = root->FirstChildElement("circle");
        while (circle_element != nullptr)
        {
            string fill = circle_element->Attribute("fill");
            if (fill == "green")
                LoadPlayer(circle_element);
            else if (fill == "red")
                LoadEnemy(circle_element);

            circle_element = circle_element->NextSiblingElement("circle");
        }

        tinyxml2::XMLElement *rect_element = root->FirstChildElement("rect");
        while (rect_element != nullptr)
        {
            string fill = rect_element->Attribute("fill");
            if (fill == "blue")
                LoadBackground(rect_element);
            else if (fill == "black")
                LoadObstacle(rect_element);

            rect_element = rect_element->NextSiblingElement("rect");
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

        Rectangle *background = new Rectangle(origin, width, height, color);

        map_.set_background(background);

        Vector player_position = player_->get_position();

        ortho_left_ = player_position[0] - height / 2;
        ortho_right_ = player_position[0] + height / 2;
        ortho_top_ = y;
        ortho_bottom_ = y + height;
        ortho_near_ = 20.0;
        ortho_far_ = 0.0;

        RGBA obstacle_color = RGBAFactory::get_color("black");

        double obstacle_stroke = 1;

        Vector bottom_limit = Vector(origin);
        bottom_limit[1] += height;
        Obstacle *bottom_limit_obstacle = new Obstacle(bottom_limit, width, obstacle_stroke, obstacle_color);
        map_.AddObstacle(bottom_limit_obstacle);
        collision_system_.AddToCollisionSystem(bottom_limit_obstacle);
        gravity_constraint_system_.AddSurface(bottom_limit_obstacle);

        Vector top_limit = Vector(origin);
        top_limit[1] -= obstacle_stroke;
        Obstacle *top_limit_obstacle = new Obstacle(top_limit, width, obstacle_stroke, obstacle_color);
        map_.AddObstacle(top_limit_obstacle);
        collision_system_.AddToCollisionSystem(top_limit_obstacle);

        Vector left_limit = Vector(origin);
        left_limit[0] -= obstacle_stroke;
        Obstacle *left_limit_obstacle = new Obstacle(left_limit, obstacle_stroke, height, obstacle_color);
        map_.AddObstacle(left_limit_obstacle);
        collision_system_.AddToCollisionSystem(left_limit_obstacle);

        Vector right_limit = Vector(origin);
        right_limit[0] += width;
        Obstacle *right_limit_obstacle = new Obstacle(right_limit, obstacle_stroke, height, obstacle_color);
        map_.AddObstacle(right_limit_obstacle);
        collision_system_.AddToCollisionSystem(right_limit_obstacle);
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

        Obstacle *obstacle = new Obstacle(origin, width, height, color);
        map_.AddObstacle(obstacle);
        collision_system_.AddToCollisionSystem(obstacle);
        gravity_constraint_system_.AddSurface(obstacle);
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

        Character *player = new Character(origin, radius, color);
        this->player_ = player;
        collision_system_.AddToCollisionSystem(player);
        gravity_constraint_system_.AddCorp(player);
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

        Character *enemy = new Character(origin, radius, color, false);
        enemies_.push_back(enemy);
        collision_system_.AddToCollisionSystem(enemy);
    }

    void Game::CheckKeys()
    {
        if (keys_['a'] && !keys_['d'] && mouse_[GLUT_RIGHT_BUTTON])
            player_->Jump(delta_time_, Direction::kLeft);

        if (keys_['a'] && !keys_['d'] && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Move(delta_time_, Direction::kLeft);

        if (!keys_['a'] && keys_['d'] && mouse_[GLUT_RIGHT_BUTTON])
            player_->Jump(delta_time_, Direction::kRight);

        if (!keys_['a'] && keys_['d'] && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Move(delta_time_, Direction::kRight);

        if (((!keys_['a'] && !keys_['d']) || (keys_['a'] && keys_['d'])) && !mouse_[GLUT_RIGHT_BUTTON])
            player_->Stop(delta_time_);

        if (((!keys_['a'] && !keys_['d']) || (keys_['a'] && keys_['d'])) && mouse_[GLUT_RIGHT_BUTTON])
            player_->Jump(delta_time_);

        // if (mouse[GLUT_LEFT_BUTTON])
        //     cout << "Shoot" << endl;
    }
#pragma endregion // Private Methods
}