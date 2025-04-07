//----------------------------------------------------------------------
// brownian.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <time.h>

//----------------------------------------------------------------------

// Generate a Gaussian random number with mean 0 and standard deviation 1
double gaussian() {
    double u = (double)rand() / RAND_MAX;
    double v = (double)rand() / RAND_MAX;
    return sqrt(-2.0 * log(u)) * cos(2.0 * M_PI * v);
}

// Draw a line between two points
void drawLine(double x0, double y0, double x1, double y1) {
    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();
}

// Draw a Brownian bridge from (x0, y0) to (x1, y1) with the given variance and scaleFactor
void curve(double x0, double y0, double x1, double y1, double variance, double scaleFactor) {
    if ((x1 - x0) < 0.01) {
        drawLine(x0, y0, x1, y1);
        return;
    }
    double xm = (x0 + x1) / 2.0;
    double ym = (y0 + y1) / 2.0;
    double delta = gaussian() * sqrt(variance);
    curve(x0, y0, xm, ym + delta, variance / scaleFactor, scaleFactor);
    curve(xm, ym + delta, x1, y1, variance / scaleFactor, scaleFactor);
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    curve(0.0, 0.5, 1.0, 0.5, 0.01, pow(2, 2.0 * 0.5));
    glFlush();
}

// Initialize the OpenGL environment
void init() {
    glClearColor(0.9, 0.9, 0.9, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

// Main function: Accept a Hurst exponent as a command-line argument
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <hurstExponent>\n", argv[0]);
        return 1;
    }
    double hurstExponent = atof(argv[1]);
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Brownian Bridge");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o brownian brownian.c -lGL -lGLU -lglut -lm
// ./brownian 1
// ./brownian 0.5
// ./brownian 0.05
