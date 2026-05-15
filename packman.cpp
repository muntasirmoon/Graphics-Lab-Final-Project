#include <GL/glut.h>
#include <iostream>

using namespace std;

const int ROWS = 15;
const int COLS = 15;
const float CELL = 40.0f;

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


// Function to draw one square block
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


// Display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Maze
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            // Draw walls in blue
            if(maze[y][x] == 1)
            {
                drawSquare(x, y, 0.0f, 0.0f, 1.0f);
            }
            // Draw paths in black
            else
            {
                drawSquare(x, y, 0.0f, 0.0f, 0.0f);
            }
        }
    }

    glutSwapBuffers();
}


// Initialize OpenGL
void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, COLS * CELL, ROWS * CELL, 0);
}


// Main Function
int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(COLS * CELL, ROWS * CELL);

    glutCreateWindow("Pacman Maze");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}