#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>

// Definición de variables globales
int screenWidth = 800;
int screenHeight = 600;
double ballRadius = 0.1;
double ballX = 0.0;
double ballY = 0.0;
double ballVelocityX = 0.02;
double ballVelocityY = 0.03;

// Función de dibujo del screensaver
void drawScene()
{
    // Borrar la pantalla
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar la pelota
    glPushMatrix();
    glTranslated(ballX, ballY, 0.0);
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 360; i++)
    {
        glVertex2f(ballRadius * cos(i * M_PI / 180.0), ballRadius * sin(i * M_PI / 180.0));
    }
    glEnd();
    glPopMatrix();

    // Intercambiar los buffers
    glutSwapBuffers();

    // Actualizar la posición de la pelota
    ballX += ballVelocityX;
    ballY += ballVelocityY;

    // Hacer rebotar la pelota
    if (ballX > 1.0 - ballRadius)
    {
        ballX = 1.0 - ballRadius;
        ballVelocityX = -ballVelocityX;
    }
    else if (ballX < -1.0 + ballRadius)
    {
        ballX = -1.0 + ballRadius;
        ballVelocityX = -ballVelocityX;
    }
    if (ballY > 1.0 - ballRadius)
    {
        ballY = 1.0 - ballRadius;
        ballVelocityY = -ballVelocityY;
    }
    else if (ballY < -1.0 + ballRadius)
    {
        ballY = -1.0 + ballRadius;
        ballVelocityY = -ballVelocityY;
    }
}

// Función de inicialización de OpenGL
void init()
{
    // Definir el color de fondo
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // Definir la vista de la cámara
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
}

// Función principal
int main(int argc, char** argv)
{
    // Inicializar el sistema de ventana de OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Screensaver");

    // Inicializar OpenGL
    init();

    // Configurar el generador de números aleatorios
    srand(time(0));

    // Habilitar la animación
    glutIdleFunc(drawScene);

    // Ejecutar el ciclo principal del programa
    glutMainLoop();

    // Salir del programa
    return 0;
}
