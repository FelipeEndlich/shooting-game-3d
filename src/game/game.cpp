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
#include "../graphics/shapes/cuboid.hpp"
#include "../graphics/elements/obstacle.hpp"
#include "../graphics/elements/bullet.hpp"
#include "../physics/direction.hpp"

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
using ::graphics::elements::Bullet;
using ::graphics::elements::Obstacle;
using ::graphics::elements::character::Character;
using ::graphics::shapes::Circle;
using ::graphics::shapes::Cuboid;
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
using ::std::remove;
using ::std::string;

#define TRANSLATION_DELTA 2
#define ROTATION_DELTA 0.162

double dx, dy, dz;
double rx, ry, rz;

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

        glViewport(0, 0, 500, 500);
        glMatrixMode(GL_PROJECTION);
        gluPerspective(45, 1, 1000, 0.1);
        glMatrixMode(GL_MODELVIEW);

        glLoadIdentity();

        glOrtho(ortho_left_, ortho_right_, ortho_bottom_, ortho_top_, 1000, 2000);

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
        // Controlling
        auto is_pressed = [this](char key)
        {
            return this->keys_[key];
        };

        if (is_pressed('w') && !is_pressed('s'))
            camera_dy = TRANSLATION_DELTA;
        else if (!is_pressed('w') && is_pressed('s'))
            camera_dy = -TRANSLATION_DELTA;
        else if (!is_pressed('w') && !is_pressed('s'))
            camera_dy = 0;
        else if (is_pressed('w') && is_pressed('s'))
            camera_dy = 0;

        if (is_pressed('a') && !is_pressed('d'))
            camera_dx = TRANSLATION_DELTA;
        else if (!is_pressed('a') && is_pressed('d'))
            camera_dx = -TRANSLATION_DELTA;
        else if (!is_pressed('a') && !is_pressed('d'))
            camera_dx = 0;
        else if (is_pressed('a') && is_pressed('d'))
            camera_dx = 0;

        if (is_pressed('q') && !is_pressed('e'))
            camera_dz = 7 * TRANSLATION_DELTA;
        else if (!is_pressed('q') && is_pressed('e'))
            camera_dz = -7 * TRANSLATION_DELTA;
        else if (!is_pressed('q') && !is_pressed('e'))
            camera_dz = 0;
        else if (is_pressed('q') && is_pressed('e'))
            camera_dz = 0;

        if (is_pressed('8') && !is_pressed('2'))
            camera_rx = ROTATION_DELTA;
        else if (!is_pressed('8') && is_pressed('2'))
            camera_rx = -ROTATION_DELTA;
        else if (!is_pressed('8') && !is_pressed('2'))
            camera_rx = 0;
        else if (is_pressed('8') && is_pressed('2'))
            camera_rx = 0;

        if (is_pressed('4') && !is_pressed('6'))
            camera_ry = ROTATION_DELTA;
        else if (!is_pressed('4') && is_pressed('6'))
            camera_ry = -ROTATION_DELTA;
        else if (!is_pressed('4') && !is_pressed('6'))
            camera_ry = 0;
        else if (is_pressed('4') && is_pressed('6'))
            camera_ry = 0;
        // End of controlling

        double current_time = glutGet(GLUT_ELAPSED_TIME);
        delta_time_ = current_time - this->current_time_;
        if (delta_time_ > 0.1)
        {
            this->current_time_ = current_time;
            Vector old_position = player_->get_position();
            CheckKeys();

            // ProcessAiming();

            // for (auto bullet : bullets_)
            //     bullet->Update(delta_time_);

            // collision_system_.ProcessCollisions();
            // gravity_constraint_system_.ProcessGravityEffects();
            // shooting_system_.ProcessShoots();

            // for (auto &bullet : shooting_system_.hit_bullets_)
            //     bullets_.erase(remove(bullets_.begin(), bullets_.end(), bullet), bullets_.end());
            // shooting_system_.hit_bullets_.clear();

            // for (auto &enemy : shooting_system_.hit_enemies_)
            // {
            //     collision_system_.RemoveFromCollisionSystem(enemy);
            //     enemies_.erase(remove(enemies_.begin(), enemies_.end(), enemy), enemies_.end());
            // }
            // shooting_system_.hit_enemies_.clear();

            // Vector translation = old_position - player_->get_position();
            // glTranslated(translation[0], 0, 0);

            glutPostRedisplay();
        }
    }

    void Game::ProcessAiming()
    {
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
    }

    void Game::Display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glTranslatef(camera_dx, camera_dy, camera_dz);
        glRotatef(camera_rx, 1, 0, 0);
        glRotatef(camera_ry, 0, 1, 0);
        glRotatef(camera_rz, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);

        map_.Render();
        player_->Render();

        for (auto &enemy : enemies_)
            enemy->Render();

        for (auto &bullet : bullets_)
            bullet->Render();

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

        if (mouse_[GLUT_LEFT_BUTTON] && state != GLUT_UP)
            shoot_processed_ = false;
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
        double depth = 1;
        double x = element->DoubleAttribute("x");
        double y = element->DoubleAttribute("y");
        string fill = element->Attribute("fill");
        Vector origin(3);
        origin[0] = x;
        origin[1] = y;
        origin[2] = 0;

        RGBA color = RGBAFactory::get_color(fill);

        Cuboid *background = new Cuboid(origin, width, height, depth, color);

        map_.set_background(background);

        Vector player_position = player_->get_position();

        ortho_left_ = player_position[0] - height / 2;
        ortho_right_ = player_position[0] + height / 2;
        ortho_top_ = y;
        ortho_bottom_ = y + height;
        ortho_near_ = 0.0;
        ortho_far_ = 20.0;

        RGBA obstacle_color = RGBAFactory::get_color("black");

        double obstacle_stroke = 1;

        Vector bottom_limit = Vector(origin);
        bottom_limit[1] += height;
        Obstacle *bottom_limit_obstacle = new Obstacle(bottom_limit, width, obstacle_stroke, depth, obstacle_color);
        map_.AddObstacle(bottom_limit_obstacle);
        collision_system_.AddToCollisionSystem(bottom_limit_obstacle);
        gravity_constraint_system_.AddSurface(bottom_limit_obstacle);
        shooting_system_.AddObstacle(bottom_limit_obstacle);

        Vector top_limit = Vector(origin);
        top_limit[1] -= obstacle_stroke;
        Obstacle *top_limit_obstacle = new Obstacle(top_limit, width, obstacle_stroke, depth, obstacle_color);
        map_.AddObstacle(top_limit_obstacle);
        collision_system_.AddToCollisionSystem(top_limit_obstacle);
        shooting_system_.AddObstacle(top_limit_obstacle);

        Vector left_limit = Vector(origin);
        left_limit[0] -= obstacle_stroke;
        Obstacle *left_limit_obstacle = new Obstacle(left_limit, obstacle_stroke, height, depth, obstacle_color);
        map_.AddObstacle(left_limit_obstacle);
        collision_system_.AddToCollisionSystem(left_limit_obstacle);
        shooting_system_.AddObstacle(left_limit_obstacle);

        Vector right_limit = Vector(origin);
        right_limit[0] += width;
        Obstacle *right_limit_obstacle = new Obstacle(right_limit, obstacle_stroke, height, depth, obstacle_color);
        map_.AddObstacle(right_limit_obstacle);
        collision_system_.AddToCollisionSystem(right_limit_obstacle);
        shooting_system_.AddObstacle(right_limit_obstacle);
    }

    void Game::LoadObstacle(tinyxml2::XMLElement *element)
    {
        double width = element->DoubleAttribute("width");
        double height = element->DoubleAttribute("height");

        double depth = height;
        if (width > height)
            depth = width;
        depth /= 2;

        double x = element->DoubleAttribute("x");
        double y = element->DoubleAttribute("y");
        double z = 1;
        string fill = element->Attribute("fill");

        Vector origin(3);
        origin[0] = x;
        origin[1] = y;
        origin[2] = z;

        RGBA color = RGBAFactory::get_color(fill);

        Obstacle *obstacle = new Obstacle(origin, width, height, depth, color);
        map_.AddObstacle(obstacle);
        collision_system_.AddToCollisionSystem(obstacle);
        gravity_constraint_system_.AddSurface(obstacle);
        shooting_system_.AddObstacle(obstacle);
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
        shooting_system_.set_player(player);
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
        shooting_system_.AddEnemy(enemy);
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

        if (mouse_[GLUT_LEFT_BUTTON] && !shoot_processed_)
        {
            shoot_processed_ = true;
            Bullet *bullet = player_->Shoot();
            bullets_.push_back(bullet);
            shooting_system_.AddBullet(bullet);
        }
    }
#pragma endregion // Private Methods
}