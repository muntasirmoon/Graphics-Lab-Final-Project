#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

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


// ====================================
// SCORE & LIVES
// ====================================

int score = 0;
int lives = 3;


// ====================================
// GHOST STRUCTURE
// ====================================

struct Ghost
{
    int x, y;

    float r, g, b;

    int dirX, dirY;

    int moveCounter;
};


// Ghost List
vector<Ghost> ghosts;


// ====================================
// INITIALIZE GHOSTS
// ====================================

void initializeGhosts()
{
    ghosts.clear();

    Ghost ghost1 = {7, 7, 1.0f, 0.0f, 0.0f, 1, 0, 0};

    Ghost ghost2 = {7, 8, 0.0f, 1.0f, 1.0f, -1, 0, 0};

    Ghost ghost3 = {8, 7, 1.0f, 0.5f, 0.0f, 0, 1, 0};

    Ghost ghost4 = {8, 8, 1.0f, 0.6f, 0.8f, 0, -1, 0};

    ghosts.push_back(ghost1);

    ghosts.push_back(ghost2);

    ghosts.push_back(ghost3);

    ghosts.push_back(ghost4);
}


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


// ====================================
// TEXT DRAWING FUNCTION
// ====================================

void drawText(float x, float y, string text)
{
    glColor3f(1.0f, 1.0f, 1.0f);

    glRasterPos2f(x, y);

    for(char c : text)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, c);
    }
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


// Pacman Drawing
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


// ====================================
// CLASSIC GHOST DRAWING
// ====================================

void drawGhost(const Ghost& ghost)
{
    float centerX = ghost.x * CELL + CELL / 2;
    float centerY = ghost.y * CELL + CELL / 2;

    float radius = 15.0f;

    glColor3f(ghost.r, ghost.g, ghost.b);

    glBegin(GL_POLYGON);

    for(int i = 0; i <= 180; i++)
    {
        float theta = i * 3.14159f / 180;

        glVertex2f(
            centerX + radius * cos(theta),
            centerY + radius * sin(theta)
        );
    }

    glVertex2f(centerX + radius, centerY);

    glVertex2f(centerX + radius * 0.6f, centerY - radius * 0.3f);

    glVertex2f(centerX + radius * 0.3f, centerY - radius * 0.6f);

    glVertex2f(centerX, centerY - radius * 0.3f);

    glVertex2f(centerX - radius * 0.3f, centerY - radius * 0.6f);

    glVertex2f(centerX - radius * 0.6f, centerY - radius * 0.3f);

    glVertex2f(centerX - radius, centerY);

    glEnd();
}


// Draw All Ghosts
void drawGhosts()
{
    for(const auto& ghost : ghosts)
    {
        drawGhost(ghost);
    }
}


// ====================================
// DISPLAY FUNCTION
// ====================================

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // Draw Maze
    for(int y = 0; y < ROWS; y++)
    {
        for(int x = 0; x < COLS; x++)
        {
            if(maze[y][x] == 1)
            {
                drawSquare(x, y, 0.0f, 0.0f, 1.0f);
            }
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

    // Draw Ghosts
    drawGhosts();

    // ====================================
    // DRAW HUD
    // ====================================

    drawText(10, 20, "Score: " + to_string(score));

    drawText(COLS * CELL - 120, 20,
             "Lives: " + to_string(lives));

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

    srand(time(0));

    initializeGhosts();
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

    glutCreateWindow("Pacman HUD System");

    init();

    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}