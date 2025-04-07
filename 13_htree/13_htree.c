//----------------------------------------------------------------------
// htree.c
//----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

//----------------------------------------------------------------------

// Draw a line between two points
void drawLine(double x0, double y0, double x1, double y1) {
    glBegin(GL_LINES);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();
}

// Draw a level n H-tree centered at (x, y) with lines of length lineLength.
void draw(int n, double lineLength, double x, double y) {
    if (n == 0) return;
    double x0 = x - lineLength / 2;
    double x1 = x + lineLength / 2;
    double y0 = y - lineLength / 2;
    double y1 = y + lineLength / 2;

    drawLine(x0, y, x1, y);      // horizontal line
    drawLine(x0, y0, x0, y1);    // left vertical line
    drawLine(x1, y0, x1, y1);    // right vertical line

    draw(n - 1, lineLength / 2, x0, y0);  // bottom-left
    draw(n - 1, lineLength / 2, x0, y1);  // top-left
    draw(n - 1, lineLength / 2, x1, y0);  // bottom-right
    draw(n - 1, lineLength / 2, x1, y1);  // top-right
}

// Display function for OpenGL
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);
    draw(3, 0.5, 0.5, 0.5);  // Example H-tree with level 3
    glFlush();
}

// Initialize the OpenGL environment
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    glPointSize(1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 1.0, 0.0, 1.0);
}

// Main function: Accept integer n as a command-line argument.
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <n>\n", argv[0]);
        return 1;
    }
    int n = atoi(argv[1]);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("H-Tree");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

//----------------------------------------------------------------------

// Compile and run:
// gcc -o htree htree.c -lGL -lGLU -lglut
// ./htree 3
