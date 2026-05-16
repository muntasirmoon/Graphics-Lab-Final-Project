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

// ====================================
// MAZE
// 0 = pellet path
// 1 = wall
// 2 = eaten pellet
// ====================================

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


// ====================================
// PACMAN VARIABLES
// ====================================

int pacmanX = 1;
int pacmanY = 1;

int dirX = 0;
int dirY = 0;


// ====================================
// GAME VARIABLES
// ====================================

int score = 0;

int lives = 3;

bool gameOver = false;


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


// ====================================
// DRAW SQUARE
// ====================================

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
// DRAW TEXT
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


// ====================================
// DRAW PELLETS
// ====================================

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


// ====================================
// DRAW PACMAN
// ====================================

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
// MOVE PACMAN
// ====================================

void movePacman()
{
    if(gameOver) return;

    int nextX = pacmanX + dirX;

    int nextY = pacmanY + dirY;

    if(maze[nextY][nextX] != 1)
    {
        pacmanX = nextX;

        pacmanY = nextY;

        // Pellet Eating
        if(maze[pacmanY][pacmanX] == 0)
        {
            maze[pacmanY][pacmanX] = 2;

            score += 10;
        }
    }
}


// ====================================
// MOVE GHOSTS
// ====================================

void moveGhosts()
{
    if(gameOver) return;

    for(auto& ghost : ghosts)
    {
        ghost.moveCounter++;

        // Change direction randomly
        if(ghost.moveCounter > 5)
        {
            int direction = rand() % 4;

            switch(direction)
            {
                case 0:
                    ghost.dirX = 1;
                    ghost.dirY = 0;
                    break;

                case 1:
                    ghost.dirX = -1;
                    ghost.dirY = 0;
                    break;

                case 2:
                    ghost.dirX = 0;
                    ghost.dirY = 1;
                    break;

                case 3:
                    ghost.dirX = 0;
                    ghost.dirY = -1;
                    break;
            }

            ghost.moveCounter = 0;
        }

        int nextX = ghost.x + ghost.dirX;

        int nextY = ghost.y + ghost.dirY;

        if(maze[nextY][nextX] != 1)
        {
            ghost.x = nextX;
            ghost.y = nextY;
        }
    }
}


// ====================================
// COLLISION CHECK
// ====================================

void checkCollision()
{
    for(const auto& ghost : ghosts)
    {
        if(pacmanX == ghost.x &&
           pacmanY == ghost.y)
        {
            lives--;

            pacmanX = 1;
            pacmanY = 1;

            if(lives <= 0)
            {
                gameOver = true;
            }
        }
    }
}


// ====================================
// TIMER FUNCTION
// ====================================

void timer(int value)
{
    movePacman();

    moveGhosts();

    checkCollision();

    glutPostRedisplay();

    glutTimerFunc(200, timer, 0);
}


// ====================================
// KEYBOARD CONTROLS
// ====================================

void handleKeys(int key, int, int)
{
    switch(key)
    {
        case GLUT_KEY_UP:
            dirX = 0;
            dirY = -1;
            break;

        case GLUT_KEY_DOWN:
            dirX = 0;
            dirY = 1;
            break;

        case GLUT_KEY_LEFT:
            dirX = -1;
            dirY = 0;
            break;

        case GLUT_KEY_RIGHT:
            dirX = 1;
            dirY = 0;
            break;
    }
}


// ====================================
// DRAW CLASSIC GHOST
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


// ====================================
// DRAW ALL GHOSTS
// ====================================

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

    drawPellets();

    drawPacman();

    drawGhosts();

    // HUD
    drawText(10, 20,
             "Score: " + to_string(score));

    drawText(COLS * CELL - 120, 20,
             "Lives: " + to_string(lives));

    // Game Over Message
    if(gameOver)
    {
        drawText(
            COLS * CELL / 2 - 70,
            ROWS * CELL / 2,
            "GAME OVER"
        );
    }

    glutSwapBuffers();
}


// ====================================
// INITIALIZATION
// ====================================

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


// ====================================
// MAIN FUNCTION
// ====================================

int main(int argc, char** argv)
{
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize(
        COLS * CELL,
        ROWS * CELL
    );

    glutCreateWindow("Pacman Final Game");

    init();

    glutDisplayFunc(display);

    glutSpecialFunc(handleKeys);

    glutTimerFunc(200, timer, 0);

    glutMainLoop();

    return 0;
}