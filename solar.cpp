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
float angleSaturn = 0;
float angleUranus = 0;
float angleNeptune = 0;

float stars[300][3];
void drawText(float x, float y, float z, const char* text);
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
                float r, float g, float b, const char* name)
{
    glPushMatrix();

    float x = orbitRadius * cos(angle * 3.14159f / 180.0f);
    float z = orbitRadius * sin(angle * 3.14159f / 180.0f);

    glTranslatef(x, 0, z);

    glColor3f(r, g, b);
    glutSolidSphere(planetSize, 30, 30);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(0, planetSize + 0.5f, 0, name);

    glPopMatrix();
}
void drawRingedPlanet(float orbitRadius, float planetSize, float angle,
                      float r, float g, float b, const char* name)
{
    glPushMatrix();

    float x = orbitRadius * cos(angle * 3.14159f / 180.0f);
    float z = orbitRadius * sin(angle * 3.14159f / 180.0f);

    glTranslatef(x, 0, z);

    glColor3f(r, g, b);
    glutSolidSphere(planetSize, 30, 30);

    glColor3f(0.8f, 0.7f, 0.5f);
    glRotatef(90, 1, 0, 0);
    glutSolidTorus(0.08, planetSize + 0.6, 30, 60);

    glRotatef(-90, 1, 0, 0);


    glColor3f(r, g, b);
    drawText(0, planetSize + 0.8f, 0, name);
    glPopMatrix();
}
void drawText(float x, float y, float z, const char* text)
{
    glDisable(GL_DEPTH_TEST); 
    glRasterPos3f(x, y, z);

    for (int i = 0; text[i] != '\0'; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, text[i]);
    }
    glDisable(GL_DEPTH_TEST); 
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(
        0, 50, 70,
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
    drawCircleOrbit(24);
    drawCircleOrbit(29);
    drawCircleOrbit(34);

    // this is for the planets
    drawPlanet(5, 0.5, angleMercury, 0.6f, 0.6f, 0.6f, "Mercury");
    drawPlanet(8, 0.8, angleVenus,   1.0f, 0.5f, 0.1f, "Venus");
    drawPlanet(11, 1.0, angleEarth,  0.0f, 0.3f, 1.0f, "Earth");
    drawPlanet(14, 0.7, angleMars,   1.0f, 0.1f, 0.0f, "Mars");
    drawPlanet(19, 1.8, angleJupiter,0.8f, 0.5f, 0.2f, "Jupiter");
    drawRingedPlanet(24, 1.5, angleSaturn, 0.9f, 0.7f, 0.4f, "Saturn");
    drawRingedPlanet(29, 1.2, angleUranus,0.4f, 0.9f, 1.0f, "Uranus");
    drawPlanet(34, 1.2, angleNeptune,0.1f, 0.2f, 1.0f, "Neptune");

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
        angleSaturn  += 0.45f * speedMultiplier;
        angleUranus  += 0.30f * speedMultiplier;
        angleNeptune += 0.20f * speedMultiplier;
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
    gluPerspective(45.0, 900.0 / 700.0, 1.0, 300.0);

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