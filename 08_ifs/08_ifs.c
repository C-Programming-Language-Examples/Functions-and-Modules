//----------------------------------------------------------------------
// ifs.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

#define MAX_ROWS 10
#define MAX_COLS 3

// Number of points to plot
int n;
int m;
double dist[MAX_ROWS];
double cx[MAX_ROWS][MAX_COLS];
double cy[MAX_ROWS][MAX_COLS];
double x = 0.0;
double y = 0.0;

// Generate a random discrete value based on the distribution
int discrete(double *dist, int m) {
    double r = (double)rand() / RAND_MAX;
    double sum = 0.0;
    for (int i = 0; i < m; i++) {
        sum += dist[i];
        if (r < sum) return i;
    }
    return m - 1;
}

// Draw a single point
void drawPoint(double px, double py) {
    glVertex2d(px, py);
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for (int i = 0; i < n; i++) {
        int r = discrete(dist, m);
        double x0 = cx[r][0] * x + cx[r][1] * y + cx[r][2];
        double y0 = cy[r][0] * x + cy[r][1] * y + cy[r][2];
        x = x0;
        y = y0;
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

// Main function: Accept integer n as a command-line argument and read transformation data from standard input
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    n = atoi(argv[1]);
    srand(time(NULL));

    // Reading the number of transformations
    scanf("%d", &m);
    for (int i = 0; i < m; i++) scanf("%lf", &dist[i]);
    for (int i = 0; i < m; i++) for (int j = 0; j < 3; j++) scanf("%lf", &cx[i][j]);
    for (int i = 0; i < m; i++) for (int j = 0; j < 3; j++) scanf("%lf", &cy[i][j]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Iterated Function System");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o ifs ifs.c -lGL -lGLU -lglut
// ./ifs 10000 < sierpinski.txt
