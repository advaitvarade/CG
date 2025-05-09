//#include <windows.h>
#include <GL/glu.h>
#include <GL/glut.h>

int framenumber = 0;

// Draw the windmill structure and rotating blades
void drawWindmill() {
    // Draw the base tower
    glColor3f(.0, .0, 1.0);  // Yellow
    glBegin(GL_POLYGON);
        glVertex2f(-5, 0);
        glVertex2f(-5, -100);
        glVertex2f(5, -100);
        glVertex2f(5, 0);
    glEnd();

    // Move origin to top of tower for blade rotation
    //glTranslatef(0, 100, 0); // local translation only for blade
    glRotated(framenumber, 0, 0, 1); // rotate blades

    // Draw 4 blades
    glColor3f(1.0, 0.0, 0.0); // Red
    for (int i = 0; i < 4; i++) {
        glRotated(90, 0, 0, 1); // rotate 90 degrees each blade
        glBegin(GL_POLYGON);
            glVertex2f(0, 0);
            glVertex2f(50, 10);
            glVertex2f(50, -10);
        glEnd();
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //glLoadIdentity();

    glPushMatrix();
    drawWindmill();  // Draw at origin, which is center of screen
    glPopMatrix();

    glutSwapBuffers();
}

// Timer function for animation
void doFrame(int v) {
    framenumber++;
    glutPostRedisplay();  // Trigger redraw
    glutTimerFunc(10, doFrame, 0); // 10 ms delay
}

// Setup OpenGL and projection
void init() {
    glClearColor(1, 1, 1, 0); // White background
    //glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-250, 250, -250, 250); // Origin at center
    //glMatrixMode(GL_MODELVIEW);
}

// Main entry point
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowSize(500, 500); // Window size
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Windmill Animation");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(10, doFrame, 0);
    glutMainLoop();
    return 0;
}
