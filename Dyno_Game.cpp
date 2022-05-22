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

// void beginText()
// {
//    glMatrixMode(GL_PROJECTION);

//    // Save the current projection matrix
//    glPushMatrix();

//    // Make the current matrix the identity matrix
//    glLoadIdentity();

//    // Set the projection (to 2D orthographic)
//    gluOrtho2D(0, width, 0, height);

//    glMatrixMode(GL_MODELVIEW);
// }

/**
 * End the state for text
 */
// void endText()
// {
//    glMatrixMode(GL_PROJECTION);

//    // Restore the original projection matrix
//    glPopMatrix();

//    glMatrixMode(GL_MODELVIEW);
// }

void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // beginText();

    // Render the text
    if (!startGame)
    {
        char snum[10];
        char scoreString2[30] = "Max Score :: ";
        // convert 123 to string [buf]
        // itoa(score, snum, 10)
        snprintf(snum, sizeof(snum), "%d", max_score);
        strcat(scoreString2, snum);

        drawString(70.0, 90.0, 0.0, scoreString2);
        char scoreString[30] = "Score :: ";
        // convert 123 to string [buf]
        // itoa(score, snum, 10)
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
        //   std::string str = std::to_string(sco);
        // std::string s = std::to_string(42);
        // std::string str("Test string");
        // std::string result;
        char snum[10];
        char scoreString2[30] = "Max Score :: ";
        // convert 123 to string [buf]
        // itoa(score, snum, 10)
        snprintf(snum, sizeof(snum), "%d", max_score);
        strcat(scoreString2, snum);

        drawString(70.0, 90.0, 0.0, scoreString2);
        char scoreString[30] = "Score :: ";
        // convert 123 to string [buf]
        // itoa(score, snum, 10)
        snprintf(snum, sizeof(snum), "%d", score);
        strcat(scoreString, snum);

        drawString(70.0, 80.0, 0.0, scoreString);
    }

    // Set things up for normal rendering
    // endText();

    // float dinoEye[2] = {13,13,12,12}
   

    // glPointSize(10.0);
    // glBegin(GL_POINTS);
    // glVertex2d(mX, dinoVerticalPosition);
    // glEnd();
    glBegin(GL_LINE_LOOP);
    //glColor3f(0.0, 0.0, 0.0);
    for (int i = 0; i < 33; i++)
    {
        glVertex2f(tempDinoPoints[0][i], tempDinoPoints[1][i]);
    }
    // glVertex2d(6,3);
    // glVertex2d(6,1);
    // glVertex2d(7,1);
    // glVertex2d(7,0);
    // glVertex2d(5,0);
    // glVertex2d(5,3);
    glEnd();
    //glColor3f(0.0, 0.0, 0.0);
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
    {

            dinoRunningLegs = true;
    }
    // glPushMatrix();
    // glLoadIdentity();
    // glTranslatef(0.5, 0.5, 0.0);
    // glRotatef(25.0, 0.0, 0.0, 1.0);
    // glutSolidCube(0.5);
    // glPopMatrix();
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
        {

            treePoints[0][i] += 128;

            // treePoints[0][i] += 128;
            // printf("%.0f,", treePoints[0][i]);
        }
        // printf("\n");
        treeLastPointPosition = 100;
    }
    glBegin(GL_POLYGON);
    glColor3f(0.2, 0.415, 0.184);
    for (int i = 0; i < 16; i++)
    {
        glVertex2f(treePoints[0][i], treePoints[1][i]);
        treePoints[0][i] += -gameSpeed;

        // treePoints[0][i] += 120;
        // printf("%.0f,", treePoints[0][i] );
    }
    treeLastPointPosition--;
    glEnd();
    glColor3f(0.0, 0.0, 0.0);
    if (treePoints[0][12] <= 13 && treePoints[0][12] >= 0 && dinoVerticalPosition < 13)
    {
        // printf("tree inside dragon range value is = %d \n", treeLastPointPosition);
        // glutPostRedisplay();
        char *p = (char *)"Game Over press UP arrow to play again";
        char *u = (char *)"Made By : Jagrit Nokwal, Gaurav Baweja, Mukul Tayal";
        drawString(30.0, 50.0, 0.0, p);
        drawString(30.0, 5.0, 0.0, u);
        
        // glutIdleFunc(dontDoAnythingIdle);
        glutTimerFunc(0, myTimerDoNothing, 0);
        gameRunning = false;
        startGame = false;
        resetGame();
        // return;
    }
}

void resetGame()
{
    // tempDinoPoints = dinoPoints;
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
            // mX = VX * time;

            // printf("%f--\n\n\n", dinoVerticalPosition);
            for (int i = 0; i < 33; i++)
            {
                tempDinoPoints[1][i] = dinoPoints[1][i] + dinoVerticalPosition;

                // printf("%f----\n", dinoPoints[1][i]);
            }
            // tempDinoEye[0] = dinoEye[0]+dinoVerticalPosition;
            tempDinoEye[1] = dinoEye[1] + dinoVerticalPosition;
            // glutTimerFunc(timerTime, myTimerDoNothing, 0);
        }
        else
        {
            memcpy(tempDinoPoints, dinoPoints, sizeof tempDinoPoints);
            memcpy(tempDinoEye, dinoEye, sizeof tempDinoEye);
            // glutIdleFunc(dontDoAnythingIdle); // 1 click == 1 jump
            // glutTimerFunc(timerTime, myTimer, 0);
            time = 0.1;
            dinoVerticalPosition = 0;
            jump = false;
        }
    }
}

void myTimer(int value)
{
    // glutIdleFunc(myIdleFunc);
    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
        if (value % 10 == 0)
        {

            score += gameSpeed * gameSpeed;
            max_score = fmax(max_score,score);

            // printf("%d\n",value);
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
        {
            jump = true;
            // glutTimerFunc(50, myTimer, 0);
            // glutIdleFunc(myIdleFunc);
        }
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
    glutInitWindowPosition(100, 100);

    // int wid =GLUT_SCREEN_HEIGHT;
    // printf("%d",wid);

    glutCreateWindow("Dino Run");

    glutDisplayFunc(display);

    // glutIdleFunc(myIdleFunc);
    glutTimerFunc(timerTime, myTimer, 0); // mili seconds , myTimer(int value), value
    // glutKeyboardFunc(myKeyboardFunc); // myKeyboardFunc(unsigned char key , int x , int y)
    // glutMouseFunc(myMouse); //  myMouse(int button , int state , int x , int y)
    glutSpecialFunc(keyDown); // keyDown(int key , int x , int y)
    // glutSpecialUpFunc(keyUp);   // keyUp(int key , int x , int y)
    // glutPostRedisplay();
    // glutReshapeFunc(myReshape);

    myinit();
    glutMainLoop();
    return 0;
}
