#include <GLUT/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void drawGround();
void myTimer(int);
void myTimerDoNothing(int);
void jumpFunc();
void dontDoAnythingIdle();
void resetGame();
void drawString();
void Draw_Figure();
void drawGround();
void drawTree();

#define PI 3.1415
#define theta 90.0f

bool startGame = false;
bool gameRunning = false;
int max_score=0;
float gameSpeed = 1;
int timerTime = 1;
int score = 0;
float mX = 0;
float dinoVerticalPosition = 0;
float dinoPoints[2][33] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 1.5, -1, 2, 3, 5, 7, 7, 12, 12, 9, 9, 11, 11, 8, 8, 10, 10, 9, 9, 8, 8},
    {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 10, 9, 8, 8, 10, 14.7, 15, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float tempDinoPoints[2][33] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 1.5, -1, 2, 3, 5, 7, 7, 12, 12, 9, 9, 11, 11, 8, 8, 10, 10, 9, 9, 8, 8},
                               {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 10, 9, 8, 8, 10, 14.7, 15, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float dinoEye[2] = {8, 12};
float tempDinoEye[2] = {8, 12};
bool rst=0;
int treeLastPointPosition = 128;
float treePoints[2][16] = {{125, 125, 122, 122, 123, 123, 125, 125, 128, 128, 130, 130, 131, 131, 128, 128},
                           {0, 8, 8, 12, 12, 9, 9, 13, 13, 8, 8, 11, 11, 7, 7, 0}};
int leg_stay_count=0;
float dinoRunningLegs = false;
void myTimerDoNothing(int){
    
}
void drawString(float x, float y, float z, char *string)
{
    glRasterPos3f(x, y, z);

    for (char *c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c); // Updates the position
    }
}

void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    // Render the text
    if (!startGame)
    {
        char snum[10];
        char scoreString2[30] = "Max Score :: ";
        snprintf(snum, sizeof(snum), "%d", max_score);
        strcat(scoreString2, snum);
        drawString(70.0, 90.0, 0.0, scoreString2);
        char scoreString[30] = "Score :: ";
        snprintf(snum, sizeof(snum), "%d", score);
        strcat(scoreString, snum);
        drawString(70.0, 80.0, 0.0, scoreString);
        char *p = (char *)"Press Up Arrow to start game";
        char *u = (char *)"Made By : Jagrit Nokwal, Gaurav Baweja, Mukul Tayal";
        drawString(30.0, 50.0, 0.0, p);
        drawString(30.0, 5.0, 0.0, u);
        rst=0;
    }
    else
    {
        char snum[10];
        char scoreString2[30] = "Max Score :: ";
        snprintf(snum, sizeof(snum), "%d", max_score);
        strcat(scoreString2, snum);
        drawString(70.0, 90.0, 0.0, scoreString2);
        char scoreString[30] = "Score :: ";
        snprintf(snum, sizeof(snum), "%d", score);
        strcat(scoreString, snum);
        drawString(70.0, 80.0, 0.0, scoreString);
    }
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 33; i++)
        glVertex2f(tempDinoPoints[0][i], tempDinoPoints[1][i]);
    glEnd();
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(tempDinoEye[0], tempDinoEye[1]);
    glEnd();
    if(leg_stay_count>1e9)leg_stay_count=0;
    leg_stay_count++;
    if (startGame && dinoVerticalPosition <= 0 && dinoRunningLegs)
    {
        glBegin(GL_POLYGON);
        glVertex2f(5, 1);
        glVertex2f(7, 1);
        glVertex2f(7, 0);
        glVertex2f(5, 0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(2, 1);
        glVertex2f(4, 1);
        glVertex2f(4, 0);
        glVertex2f(2, 0);
        glEnd();
            dinoRunningLegs = false;
    }
    else
            dinoRunningLegs = true;
}

float groundDust[2][3] = {{100, 130, 170}, {-2, -2, -2}};

void drawGround()
{
    glPointSize(5.0);
    glBegin(GL_LINES);
    glVertex2f(-10, 0);
    glVertex2f(100, 0);
    glEnd();

    if (groundDust[0][0] < -10)
    {
        for (int i = 0; i < 2; i++)
        {
            groundDust[0][i] = groundDust[0][i + 1];
        }
        groundDust[0][2] = 100;
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(groundDust[0][i], groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 2, groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 1, groundDust[1][i] - 1);
        groundDust[0][i] += -gameSpeed;
    }
    glEnd();
}

void drawTree()
{

    if (treePoints[0][12] < -10)
    {
        for (int i = 0; i < 16; i++)
            treePoints[0][i] += 128;
        treeLastPointPosition = 100;
    }
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.415, 0.184);
    for (int i = 0; i < 16; i++)
    {
        glVertex2f(treePoints[0][i], treePoints[1][i]);
        treePoints[0][i] += -gameSpeed;
    }
    treeLastPointPosition--;
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    if (treePoints[0][12] <= 13 && treePoints[0][12] >= 0 && dinoVerticalPosition < 13)
    {

        char *p = (char *)"Game Over press UP arrow to play again";
        char *u = (char *)"Made By : Jagrit Nokwal, Gaurav Baweja, Mukul Tayal";
        drawString(30.0, 50.0, 0.0, p);
        drawString(30.0, 5.0, 0.0, u);
        glutTimerFunc(0, myTimerDoNothing, 0);
        gameRunning = false;
        startGame = false;
        resetGame();
    }
}

void resetGame()
{
    memcpy(tempDinoPoints, dinoPoints, sizeof tempDinoPoints);
    float tempTreePoints[2][16] = {{125, 125, 122, 122, 123, 123, 125, 125, 128, 128, 130, 130, 131, 131, 128, 128},
                                   {0, 8, 8, 12, 12, 9, 9, 13, 13, 8, 8, 11, 11, 7, 7, 0}};
    memcpy(treePoints, tempTreePoints, sizeof treePoints);
    memcpy(tempDinoEye, dinoEye, sizeof tempDinoEye);

    score = 0;
    gameSpeed = 1;
}
 
void display()
{
    Draw_Figure();
    drawGround();
    drawTree();
    glutSwapBuffers();
}

int V = 22;
int gravity = -10;

float VX = V * cos(theta * PI / 180);
float VY = V * sin(theta * PI / 180);
float time = 0.1;

void dontDoAnythingIdle()
{
}
void myIdleFunc()
{

    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
    }
}

bool jump = false;

void jumpFunc()
{
    if (jump)
    {
        dinoVerticalPosition = VY * time + 0.5 * (gravity)*time * time;
        if (dinoVerticalPosition >= 0)
        {
            time = time + (0.1) * (gameSpeed);

            for (int i = 0; i < 33; i++)
                tempDinoPoints[1][i] = dinoPoints[1][i] + dinoVerticalPosition;
            tempDinoEye[1] = dinoEye[1] + dinoVerticalPosition;
        }
        else
        {
            memcpy(tempDinoPoints, dinoPoints, sizeof tempDinoPoints);
            memcpy(tempDinoEye, dinoEye, sizeof tempDinoEye);
            time = 0.1;
            dinoVerticalPosition = 0;
            jump = false;
        }
    }
}

void myTimer(int value)
{
    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
        if (value % 10 == 0)
        {
            score += gameSpeed * gameSpeed;
            max_score = fmax(max_score,score);
        }
        if (value % 100 == 0)
        {
            gameSpeed += 0.1;
        }
    }
    glutTimerFunc(timerTime, myTimer, ++value);
}

void keyDown(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        if (startGame)
            jump = true;
        else
        {
            startGame = true;
            gameRunning = true;
        }
    }
}

void myinit() //set attributes
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 100, -10, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE
    glutInitWindowSize(900, 400);
    glutInitWindowPosition(100, 100);\
    glutCreateWindow("Dino Run");
    glutDisplayFunc(display);
    glutTimerFunc(timerTime, myTimer, 0); // mili seconds , myTimer(int value), value
    glutSpecialFunc(keyDown); // keyDown(int key , int x , int y)
    myinit();
    glutMainLoop();
    return 0;
}
