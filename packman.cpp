#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

const int ROWS = 15;
const int COLS = 15;
const float CELL = 40.0f;

// Maze Structure
int maze[ROWS][COLS] = {

    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},

    {1,0,0,0,1,0,0,0,0,0,0,1,0,0,1},

    {1,0,1,0,1,0,1,1,1,0,0,1,0,0,1},

    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},

    {1,0,1,1,1,1,0,1,1,0,1,1,1,0,1},

    {1,0,0,0,0,1,0,0,0,0,0,0,1,0,1},

    {1,1,1,1,0,1,1,1,1,1,1,0,1,0,1},

    {1,0,0,1,0,0,0,0,0,1,0,0,1,0,1},

    {1,0,0,1,1,1,1,0,1,1,1,0,1,0,1},

    {1,0,0,0,0,0,1,0,0,0,0,0,1,0,1},

    {1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},

    {1,0,1,0,0,0,0,0,1,0,0,0,0,0,1},

    {1,0,1,0,1,1,1,0,1,1,1,1,1,0,1},

    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},

    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}

};


// Pacman Position
int pacmanX = 1;
int pacmanY = 1;


// Function to draw one square
void drawSquare(int x, int y, float r, float g, float b)
{
    glColor3f(r, g, b);

    glBegin(GL_QUADS);

    glVertex2f(x * CELL, y * CELL);

    glVertex2f((x + 1) * CELL, y * CELL);

    glVertex2f((x + 1) * CELL, (y + 1) * CELL);

    glVertex2f(x * CELL, (y + 1) * CELL);

    glEnd();
}


// Pellet Rendering Function
void drawPellets()
{
    glColor3f(1.0f, 1.0f, 0.5f);

    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            if(maze[y][x] == 0)
            {
                glPointSize(5);

                glBegin(GL_POINTS);

                glVertex2f(
                    x * CELL + CELL / 2,
                    y * CELL + CELL / 2
                );

                glEnd();
            }
        }
    }
}


// ================================
// PACMAN DRAWING FUNCTION
// ================================

void drawPacman()
{
    glColor3f(1.0f, 1.0f, 0.0f);

    glBegin(GL_POLYGON);

    for(int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159f / 180;

        glVertex2f(
            pacmanX * CELL + CELL / 2 + 15 * cos(theta),
            pacmanY * CELL + CELL / 2 + 15 * sin(theta)
        );
    }

    glEnd();
}


// Display Function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Maze
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            // Wall
            if(maze[y][x] == 1)
            {
                drawSquare(x, y, 0.0f, 0.0f, 1.0f);
            }
            // Path
            else
            {
                drawSquare(x, y, 0.0f, 0.0f, 0.0f);
            }
        }
    }

    // Draw Pellets
    drawPellets();

    // Draw Pacman
    drawPacman();

    glutSwapBuffers();
}


// OpenGL Initialization
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(
        0,
        COLS * CELL,
        ROWS * CELL,
        0
    );
}


// Main Function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(
        COLS * CELL,
        ROWS * CELL
    );

    glutCreateWindow("Pacman with Pellets");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}