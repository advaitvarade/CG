#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int iterations = 3;

// Function to draw Koch curve segment
void koch(int it, float x1, float y1, float x5, float y5) {
    if (it == 0) {
        glVertex2f(x1, y1);
        glVertex2f(x5, y5);
    } else {
        float dx = (x5 - x1) / 3.0;
        float dy = (y5 - y1) / 3.0;

        float x2 = x1 + dx;
        float y2 = y1 + dy;

        float x3 = 0.5 * (x1 + x5) + sqrt(3) * (y1 - y5) / 6.0;
        float y3 = 0.5 * (y1 + y5) + sqrt(3) * (x5 - x1) / 6.0;

        float x4 = x1 + 2 * dx;
        float y4 = y1 + 2 * dy;

        koch(it - 1, x1, y1, x2, y2);
        koch(it - 1, x2, y2, x3, y3);
        koch(it - 1, x3, y3, x4, y4);
        koch(it - 1, x4, y4, x5, y5);
    }
}

// Display callback
void display() {
    glClearColor(1, 1, 1, 1);  // White background
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0, 0, 0);  // Black

    glBegin(GL_LINES);
    // Triangle base points
    koch(iterations, 150, 50, 50, 250);   // Left side
    koch(iterations, 50, 250, 250, 250);  // Bottom side
    koch(iterations, 250, 250, 150, 50);  // Right side
    glEnd();

    glFlush();
}


// Main
int main(int argc, char** argv) {
    cout << "Enter number of iterations: ";
    cin >> iterations;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Koch Curve - OpenGL");
    gluOrtho2D(0, 500, 0, 500);
   
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
