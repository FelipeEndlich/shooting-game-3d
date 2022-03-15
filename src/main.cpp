#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./game/game.hpp"
#include "./game/clock.hpp"
#include "./graphics/color/rgba.hpp"
#include "./graphics/color/rgba_factory.hpp"
#include "./graphics/shapes/sphere.hpp"
#include "./graphics/shapes/cuboid.hpp"
#include <cmath>
#include "./math/matrix.hpp"
#include "./math/vector.hpp"
#include "./game/scene.hpp"

#define FRAMERATE 60

#define ROT_X_DELTA 1.00 / FRAMERATE * 60
#define ROT_Y_DELTA 1.00 / FRAMERATE * 60
#define ROT_Z_DELTA 1.00 / FRAMERATE * 60

using ::game::Clock;
using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
using ::graphics::shapes::Cuboid;
using ::graphics::shapes::Sphere;
using ::math::Vector;
using ::game::GameScene;

// Control variables
bool pressed_key[256];
bool hold_mouse_right;
bool hold_mouse_left;
bool press_mouse_right;
bool press_mouse_left;

// Camera settings
double rx, ry, rz; // Rotation
double dx, dy, dz; // Displacement

// Timing and framerate settings
Clock timer;

// Game scene description
GameScene* scene;

void restart_clock()
{
    timer.start();
}

void reset_controls()
{
    for (int i = 0; i < 256; i++)
        pressed_key[i] = false;

    hold_mouse_left = false;
    hold_mouse_right = false;
    press_mouse_right = false;
    press_mouse_left = false;
}

void reset_camera()
{
    rx = 0; ry = 0; rz = 0;
    dx = 0; dy = 0; dz = 0;
}

void keydown_func(unsigned char key, int x, int y)
{
    pressed_key[(int)key] = true;
}

void keyup_func(unsigned char key, int x, int y)
{
    pressed_key[(int)key] = false;
}

void idle_func()
{
    restart_clock();

    // Lambda function to ease the key press checking
    auto is_pressed = [](unsigned char key) { return pressed_key[(int)key]; };
    
    // Camera angle control
    if (is_pressed('2'))
        rx += ROT_X_DELTA;
    else if (is_pressed('8'))
        rx -= ROT_X_DELTA;
    if (is_pressed('6'))
        ry += ROT_Y_DELTA;
    else if (is_pressed('4'))
        ry -= ROT_Y_DELTA;
    if (is_pressed('9'))
        rz += ROT_Z_DELTA;
    else if (is_pressed('7'))
        rz -= ROT_Z_DELTA;

    // Camera displacement control
    if (is_pressed('a'))
        dx += ROT_X_DELTA;
    else if (is_pressed('d'))
        dx -= ROT_X_DELTA;
    if (is_pressed('s'))
        dy += ROT_Y_DELTA;
    else if (is_pressed('w'))
        dy -= ROT_Y_DELTA;
    if (is_pressed('q'))
        dz += ROT_Z_DELTA;
    else if (is_pressed('e'))
        dz -= ROT_Z_DELTA;

    timer.tick(1000 / FRAMERATE);
    glutPostRedisplay();
}

void displayFunc(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glRotatef(rx, 1, 0, 0); // Rotate x axis
    glRotatef(ry, 0, 1, 0); // Rotate y axis
    glRotatef(rz, 0, 0, 1); // Rotate z axis
    glTranslatef(dx, dy, dz);
    //glDisable(GL_LIGHTING);

    //Cuboid sphere(15, 15, 15, Vector::Zero(3));
    //sphere.Translate(sphere.get_center_position() * -1.0);
    //sphere.Rotate(sphere.get_center_position(), 0.125 * M_PI, 0.125 * M_PI, 0.125 * M_PI);
    //sphere.Transform(sphere.get_center_position(), Vector::Zero(3), 0.125 * M_PI, 0.125 * M_PI, 0.125 * M_PI);
    glEnable(GL_DEPTH_TEST);
    scene->Draw();

    glTranslatef(-dx, -dy, -dz);
    glRotatef(-rz, 0, 0, 1);
    glRotatef(-ry, 0, 1, 0);
    glRotatef(-rx, 1, 0, 0);

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

    // Reseting controls
    reset_controls();

    // Loading scene
    scene = new GameScene(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glViewport(500, 500, 500, 500);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_LIGHT0);

    GLfloat light_position[] = {50.0, 50.0, 50.0, 50.0};
    //glLightfv(GL_LIGHT0, GL_SPECULAR, light_position);

    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D GAME");

    glutDisplayFunc(displayFunc);
    glutIdleFunc(idle_func);

    glutKeyboardFunc(keydown_func);
    glutKeyboardUpFunc(keyup_func);

    /* selecionar cor de fundo (preto) */
    RGBA scren_color = RGBAFactory::get_color(ColorOption::kBlack);
    glClearColor(scren_color.get_red(), scren_color.get_green(), scren_color.get_blue(), scren_color.get_alpha());

    glLoadIdentity();
    glOrtho(0, 250, 250, 0, -50, 50);

    glutMainLoop();

    return 0;
}