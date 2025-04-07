//----------------------------------------------------------------------
// sierpinski.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/glut.h>

// Number of points to plot
int n;

// Vertices of the Sierpinski triangle
const double cx[3] = {0.000, 1.000, 0.500};
const double cy[3] = {0.000, 0.000, 0.866};

// Current point coordinates
double x = 0.0;
double y = 0.0;

// Draw a single point
void drawPoint(double px, double py) {
    glVertex2d(px, py);
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        int r = rand() % 3;
        x = (x + cx[r]) / 2.0;
        y = (y + cy[r]) / 2.0;
        drawPoint(x, y);
    }
    glEnd();
    glFlush();
}

// Initialize the OpenGL environment
void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

// Main function: Accept integer n as a command-line argument and generate the Sierpinski triangle
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Sierpinski Triangle");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o sierpinski sierpinski.c -lGL -lGLU -lglut
// ./sierpinski 10000
