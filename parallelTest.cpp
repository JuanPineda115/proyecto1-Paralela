#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <GL/glut.h>

// Definición de variables globales
int screenWidth = 800;
int screenHeight = 600;
double ballRadius = 0.1;

//cantidad de pelotas
const int N = 5;

// Posiciones iniciales de las pelotas
double ballX[N];
double ballY[N];

// velocidad de cada pelota
double ballVelocityX[N];
double ballVelocityY[N];

//Colores de cada pelota
float ballColor[N][3];


// Variables para contar los frames
int frameCount = 0;
int fps = 0;
int currentTime = 0;
int previousTime = 0;

// Función para generar un color aleatorio
void randomColor(float color[3])
{
    color[0] = ((double)rand() / RAND_MAX);
    color[1] = ((double)rand() / RAND_MAX);
    color[2] = ((double)rand() / RAND_MAX);
}


// Función de dibujo del screensaver
void drawScene()
{
    // Incrementar el contador de frames
    frameCount++;

    // Obtener el tiempo actual en milisegundos
    currentTime = glutGet(GLUT_ELAPSED_TIME);

    // Calcular el tiempo transcurrido desde la última actualización de FPS
    int elapsedTime = currentTime - previousTime;

    // Actualizar el FPS si ha pasado un segundo desde la última actualización
    if (elapsedTime > 1000)
    {
        fps = frameCount / (elapsedTime / 1000.0);
        frameCount = 0;
        previousTime = currentTime;
    }

    // Borrar la pantalla
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujar la pelota
    for (int i = 0; i < N; i++) {
        glPushMatrix();
        glTranslated(ballX[i], ballY[i], 0.0);
        glColor3f(ballColor[i][0], ballColor[i][1], ballColor[i][2]);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0, 0.0);
        for (int i = 0; i <= 360; i++)
        {
            glVertex2f(ballRadius * cos(i * M_PI / 180.0), ballRadius * sin(i * M_PI / 180.0));
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
    glutSwapBuffers();
    for (int i = 0; i < N; i++) {
        // Actualizar la posición de la pelota
        ballX[i] += ballVelocityX[i];
        ballY[i] += ballVelocityY[i];

        // Hacer rebotar la pelota
        if (ballX[i] > 1.0 - ballRadius)
        {
            ballX[i] = 1.0 - ballRadius;
            ballVelocityX[i] = -ballVelocityX[i];
        }
        else if (ballX[i] < -1.0 + ballRadius)
        {
            ballX[i] = -1.0 + ballRadius;
            ballVelocityX[i] = -ballVelocityX[i];
        }
        if (ballY[i] > 1.0 - ballRadius)
        {
            ballY[i] = 1.0 - ballRadius;
            ballVelocityY[i] = -ballVelocityY[i];
        }
        else if (ballY[i] < -1.0 + ballRadius)
        {
            ballY[i] = -1.0 + ballRadius;
            ballVelocityY[i] = -ballVelocityY[i];
        }
    }
}

// Función de inicialización de OpenGL
void init()
{
    // Declaro las posiciones iniciales aleatorias de las pelotas
    for (int i = 0; i < N; i++) {
        ballX[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
        ballY[i] = ((double)rand() / RAND_MAX) * 2.0 - 1.0;
    }
    for (int i = 0; i < N; i++) {
        ballVelocityX[i] = ((double)rand() / RAND_MAX) * 0.04 - 0.02;
        ballVelocityY[i] = ((double)rand() / RAND_MAX) * 0.04 - 0.02;
    }
    for (int i = 0; i < N; i++) {
        randomColor(ballColor[i]);
    }

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
    glutDisplayFunc(drawScene);

    // Inicializar OpenGL
    init();

    // Configurar el generador de números aleatorios
    srand(time(0));
    clock_t start = clock();

    // Habilitar la animación
    glutIdleFunc(drawScene);
    clock_t end = clock();

    // Calcular el tiempo transcurrido
    double timeElapsed = double(end - start) / CLOCKS_PER_SEC;
    std::cout << "Tiempo de ejecución: " << timeElapsed << " segundos" << std::endl;

    // Ejecutar el ciclo principal del programa
    glutMainLoop();

    // Salir del programa
    return 0;
}
