#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>

// Definición de pantalla
int screenWidth = 800;
int screenHeight = 600;
//variables de las bolas
int balls = 2.0
double ballRadius = 0.1;
double ballX = 0.0;
double ballY = 0.0;
double ballVelocityX = 0.02;
double ballVelocityY = 0.03;
// Variables para contar los frames
int frameCount = 0;
int fps = 0;
int currentTime = 0;
int previousTime = 0;

//---------------------------------------Creo que deberiamos de
/*
Primero que todo tener un array con la posicion de las bolas que sea privado
para cada uno de los hilos. 

Cada uno de los hilos dibujara una bola y tendra su propia posicion, color, y funcion 
de movimiento.

Usar un parallel for para dibujar las bolas y actualizar su posicion.

Usar una seccion critica para actualizar el contador de frames y el tiempo transcurrido
*/

// Función de dibujo del screensaver
void drawScene()
{
    // Funciones para los FPS
    frameCount++;
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    int elapsedTime = currentTime - previousTime;
    if (elapsedTime > 1000)
    {
        fps = frameCount / (elapsedTime / 1000.0);
        frameCount = 0;
        previousTime = currentTime;
    }

    // Borrar la pantalla
    glClear(GL_COLOR_BUFFER_BIT);
    // Dibujar la pelota
    for (int i = 0; i < balls; i++) {
        glPushMatrix();
        glTranslated(ballX[i], ballY[i], 0.0);
        glColor3f(1.0, 1.0, 1.0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (int j = 0; j <= 360; j++) {
            glVertex2f(ballRadius * cos(j * M_PI / 180.0), ballRadius * sin(j * M_PI / 180.0));
        }
        glEnd();
        glPopMatrix();
    }


    // Mostrar el FPS en la pantalla
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, screenWidth, 0, screenHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0, 1.0, 1.0);
    glRasterPos2i(10, 10);
    std::string fpsStr = "FPS: " + std::to_string(fps);
    for (int i = 0; i < fpsStr.length(); i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, fpsStr[i]);
    }
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    // Intercambiar los buffers
    glutSwapBuffers()
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
    //Funcion para aceptar el parametro 
    if(argc >1){
        balls = atoi(argv[1]);
    }
    // Inicializar el sistema de ventana de OpenGL
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Screensaver");
    glutDisplayFunc(drawScene);
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