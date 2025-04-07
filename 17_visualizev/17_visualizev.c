//----------------------------------------------------------------------
// visualizev.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <GL/glut.h>
#include <time.h>

#define MAX_N 100

bool isOpen[MAX_N][MAX_N];
bool isFull[MAX_N][MAX_N];
int n, trials;
double p;

// Generate a random boolean matrix with given probability p
void generateRandomMatrix(bool matrix[MAX_N][MAX_N], int n, double p) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = ((double)rand() / RAND_MAX) < p;
        }
    }
}

// Compute the full sites from the open sites (vertical percolation)
void flow(bool isOpen[MAX_N][MAX_N], bool isFull[MAX_N][MAX_N], int n) {
    for (int j = 0; j < n; j++) {
        isFull[0][j] = isOpen[0][j];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (isOpen[i][j] && isFull[i-1][j]) {
                isFull[i][j] = true;
            }
        }
    }
}

// Draw a filled square at position (x, y)
void drawSquare(int x, int y, bool full) {
    double fx = x + 0.5;
    double fy = y + 0.5;
    if (full) glColor3f(0.0, 0.0, 1.0);  // blue for full
    else glColor3f(0.0, 0.0, 0.0);       // black for open
    glBegin(GL_QUADS);
    glVertex2d(fx - 0.5, fy - 0.5);
    glVertex2d(fx + 0.5, fy - 0.5);
    glVertex2d(fx + 0.5, fy + 0.5);
    glVertex2d(fx - 0.5, fy + 0.5);
    glEnd();
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            drawSquare(j, n - i - 1, isFull[i][j]);
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

// Main function: Accept n, p, and trials as command-line arguments
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <p> <trials>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    p = atof(argv[2]);
    trials = atoi(argv[3]);
    srand(time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Visualize Vertical Percolation");
    init();

    for (int i = 0; i < trials; i++) {
        generateRandomMatrix(isOpen, n, p);
        flow(isOpen, isFull, n);
        display();
        usleep(1000000);  // Delay for visualization
    }
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o visualizev visualizev.c -lGL -lGLU -lglut
// ./visualizev 20 0.65 3
// ./visualizev 20 0.60 1
// ./visualizev 20 0.55 1
