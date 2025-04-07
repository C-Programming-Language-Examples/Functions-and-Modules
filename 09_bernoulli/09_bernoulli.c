//----------------------------------------------------------------------
// bernoulli.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "gaussian.h"

#define MAX_N 1000

int n, trials;
int freq[MAX_N + 1];
double norm[MAX_N + 1];
double phi[MAX_N + 1];

// Generate a binomial random variable (number of heads in n coin flips)
int binomial(int n, double p) {
    int heads = 0;
    for (int i = 0; i < n; i++) {
        if ((double)rand() / RAND_MAX < p) heads++;
    }
    return heads;
}

// Plot bars for the given data
void plotBars(double *data, int length) {
    glBegin(GL_LINES);
    for (int i = 0; i < length; i++) {
        glVertex2d((double)i / n, 0);
        glVertex2d((double)i / n, data[i]);
    }
    glEnd();
}

// Plot lines for the given data
void plotLines(double *data, int length) {
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < length; i++) {
        glVertex2d((double)i / n, data[i]);
    }
    glEnd();
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    plotBars(norm, n + 1);
    glColor3f(1.0, 0.0, 0.0);
    plotLines(phi, n + 1);
    glFlush();
}

// Initialize the OpenGL environment
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.1);
}

// Main function: Accept integers n and trials as command-line arguments
int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <n> <trials>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    trials = atoi(argv[2]);
    srand(time(NULL));

    for (int i = 0; i <= n; i++) freq[i] = 0;
    for (int t = 0; t < trials; t++) {
        int heads = binomial(n, 0.5);
        freq[heads]++;
    }
    for (int i = 0; i <= n; i++) norm[i] = (double)freq[i] / trials;

    double stddev = sqrt((double)n) / 2.0;
    for (int i = 0; i <= n; i++) {
        phi[i] = pdf((double)i, (double)n / 2.0, stddev);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 400);
    glutCreateWindow("Bernoulli Distribution");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o bernoulli bernoulli.c gaussian.c -lGL -lGLU -lglut -lm
// ./bernoulli 20 100000
