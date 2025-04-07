//----------------------------------------------------------------------
// percolationio.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <time.h>

#define MAX_N 100

bool matrix[MAX_N][MAX_N];
int n;
double p;
bool which;

// Generate a random boolean matrix with given probability p
void generateRandomMatrix(int n, double p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) < p;
        }
    }
}

// Draw a filled square at position (x, y)
void drawSquare(int x, int y) {
    double fx = x + 0.5;
    double fy = y + 0.5;
    glBegin(GL_QUADS);
    glVertex2d(fx - 0.5, fy - 0.5);
    glVertex2d(fx + 0.5, fy - 0.5);
    glVertex2d(fx + 0.5, fy + 0.5);
    glVertex2d(fx - 0.5, fy + 0.5);
    glEnd();
}

// Draw the matrix on the screen
void drawMatrix() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == which) {
                glColor3f(0.0, 0.0, 0.0);  // black square
                drawSquare(j, n - i - 1);
            } else {
                glColor3f(1.0, 1.0, 1.0);  // white square
                drawSquare(j, n - i - 1);
            }
        }
    }
    glFlush();
}

// Initialize the OpenGL environment
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-0.5, n - 0.5, -0.5, n - 0.5);
}

// Main function: Accept n and p as command-line arguments
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <p>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    p = atof(argv[2]);
    which = false;  // Change this to true to display True entries
    srand(time(NULL));
    generateRandomMatrix(n, p);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Percolation IO");
    init();
    glutDisplayFunc(drawMatrix);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o percolationio percolationio.c -lGL -lGLU -lglut
// ./percolationio 10 0.8
