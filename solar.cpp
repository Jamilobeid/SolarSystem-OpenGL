#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <ctime>

float speedMultiplier = 1.0f;
bool paused = false;

float angleMercury = 0;
float angleVenus   = 0;
float angleEarth   = 0;
float angleMars    = 0;
float angleJupiter = 0;
float stars[300][3];
void drawStars();

void drawCircleOrbit(float radius)
{
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++)
    {
        float theta = i * 3.14159f / 180.0f;
        glVertex3f(radius * cos(theta), 0, radius * sin(theta));
    }
    glEnd();
}

void drawPlanet(float orbitRadius, float planetSize, float angle,
                float r, float g, float b)
{
    glPushMatrix();

    float x = orbitRadius * cos(angle * 3.14159f / 180.0f);
    float z = orbitRadius * sin(angle * 3.14159f / 180.0f);

    glTranslatef(x, 0, z);

    glColor3f(r, g, b);
    glutSolidSphere(planetSize, 30, 30);

    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0, 18, 35,
        0, 0, 0,
        0, 1, 0
    );
    drawStars();
    // this is for the sun
    glColor3f(1.0f, 0.7f, 0.0f);
    glutSolidSphere(2.5, 50, 50);

    // this is for the orbits
    glColor3f(0.4f, 0.4f, 0.4f);
    drawCircleOrbit(5);
    drawCircleOrbit(8);
    drawCircleOrbit(11);
    drawCircleOrbit(14);
    drawCircleOrbit(19);

    // this is for the planets
    drawPlanet(5, 0.5, angleMercury, 0.6f, 0.6f, 0.6f);
    drawPlanet(8, 0.8, angleVenus,   1.0f, 0.5f, 0.1f);
    drawPlanet(11, 1.0, angleEarth,  0.0f, 0.3f, 1.0f);
    drawPlanet(14, 0.7, angleMars,   1.0f, 0.1f, 0.0f);
    drawPlanet(19, 1.8, angleJupiter,0.8f, 0.5f, 0.2f);

    glutSwapBuffers();
}

void update(int value)
{
    if (!paused)
    {
        angleMercury += 4.0f * speedMultiplier;
        angleVenus   += 2.5f * speedMultiplier;
        angleEarth   += 1.8f * speedMultiplier;
        angleMars    += 1.2f * speedMultiplier;
        angleJupiter += 0.6f * speedMultiplier;
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}
void generateStars()
{
    srand(time(0));

    for (int i = 0; i < 300; i++)
    {
        stars[i][0] = rand() % 900; 
        stars[i][1] = rand() % 700; 
    }
}
void drawStars()
{
    glDisable(GL_DEPTH_TEST);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 900, 0, 700);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glPointSize(2.0f);

    glBegin(GL_POINTS);
    for (int i = 0; i < 300; i++)
    {
        glVertex2f(stars[i][0], stars[i][1]);
    }
    glEnd();

    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'p':
    case 'P':
        paused = !paused;
        break;

    case '+':
    case '=':
        speedMultiplier += 0.5f;
        break;

    case '-':
        speedMultiplier -= 0.5f;
        if (speedMultiplier < 0.1f)
            speedMultiplier = 0.1f;
        break;

    case 'r':
    case 'R':
        speedMultiplier = 1.0f;
        break;

    case 27:
        exit(0);
        break;
    }
}

void init()
{
    glEnable(GL_DEPTH_TEST);

    glClearColor(0.0f, 0.0f, 0.05f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 900.0 / 700.0, 1.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowSize(900, 700);
    glutCreateWindow("Solar System - OpenGL Project");

    init();
    generateStars();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);

    glutMainLoop();
    return 0;
}