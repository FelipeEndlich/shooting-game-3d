#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#include "./game/game.hpp"
#include "./graphics/color/rgba.hpp"
#include "./graphics/color/rgba_factory.hpp"
//#include "./graphics/shapes/cuboid.hpp"
#include <cmath>
#include "./math/matrix.hpp"

using ::graphics::color::ColorOption;
using ::graphics::color::RGBA;
using ::graphics::color::RGBAFactory;
//using ::graphics::shapes::Cuboid;

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

    /* selecionar cor de fundo (preto) */
    RGBA scren_color = RGBAFactory::get_color(ColorOption::kBlack);
    glClearColor(scren_color.get_red(), scren_color.get_green(), scren_color.get_blue(), scren_color.get_alpha());

    glLoadIdentity();
    glOrtho(-50, 50, -50, 50, -50, 50);

    // Insert shapes here

    /* Teste de Cuboid do Jorge */
    /*
    //Cuboid cuboidA(1, 1, 1);
    math::Matrix m(3, 1);
    float width = 20, height = 20, depth = 20;

    // General coordinates
    float xc, yc, zc, rotation;
    xc = m[0][0];
    yc = m[0][1];
    zc = m[0][2];

    rotation = 60;
    
    glRotatef(rotation, 1, 0, 0);
    glRotatef(rotation, 0, 1, 0);
    glBegin(GL_LINES);
        // Front lines
        float x00, x01, y00, y01, z0, z1;
        x00 = xc - width / 2;
        x01 = xc + width / 2;
        y00 = yc + height / 2;
        y01 = yc - height / 2;
        z0 = zc - depth / 2;

        glColor3f(1, 0, 0);

        // Front superior line
            glVertex3f(x00, y00, z0);
            glVertex3f(x01, y00, z0);

        // Front right line
            glVertex3f(x01, y00, z0);
            glVertex3f(x01, y01, z0);
        
        // Front inferior line
            glVertex3f(x01, y01, z0);
            glVertex3f(x00, y01, z0);

        // Front left line
            glVertex3f(x00, y01, z0);
            glVertex3f(x00, y00, z0);

        // Back lines
        z1 = zc + depth / 2;

        // Back superior line
            glVertex3f(x00, y00, z1);
            glVertex3f(x01, y00, z1);

        // Back right line
            glVertex3f(x01, y00, z1);
            glVertex3f(x01, y01, z1);
        
        // Back inferior line
            glVertex3f(x01, y01, z1);
            glVertex3f(x00, y01, z1);

        // Back left line
            glVertex3f(x00, y01, z1);
            glVertex3f(x00, y00, z1);

        // Connection lines

        // Left superior line
            glVertex3f(x00, y00, z0);
            glVertex3f(x00, y00, z1);

        // Right superior line
            glVertex3f(x01, y00, z0);
            glVertex3f(x01, y00, z1);

        // Left inferior line
            glVertex3f(x00, y01, z0);
            glVertex3f(x00, y01, z1);

        // Right inferior line
            glVertex3f(x01, y01, z0);
            glVertex3f(x01, y01, z1);

    glEnd();
    glRotatef(-rotation, 0, 1, 0);
    glRotatef(-rotation, 1, 0, 0);

    glFlush();
    glutSwapBuffers();
    */
   /* Fim do teste de Cuboid do Jorge */

    glutMainLoop();

    return 0;
}