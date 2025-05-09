#include <GL/glut.h>
#include <math.h>

#define DEG2RAD(angle) ((angle) * M_PI / 180.0)
int angle=0;
void rotateY(float x, float y,float z, float angle, float& newX,float& newY, float& newZ) {
    float rad = DEG2RAD(angle);

        newX = x * cos(rad) + z * sin(rad);
        newY=y;
        newZ = -x * sin(rad) + z * cos(rad);
    
}

void rotatedVertex(float x, float y, float z, float angle) {
    float rx, rz, ry;
    rotateY(x,y, z, angle, rx, ry, rz);
    glVertex3f(rx, ry, rz);
}

void drawCube(float angle) {
    glBegin(GL_QUADS);

    // Front
    glColor3f(1, 0, 0);
    rotatedVertex(-1, -1, 1, angle);
    rotatedVertex(1, -1, 1, angle);
    rotatedVertex(1, 1, 1, angle);
    rotatedVertex(-1, 1, 1, angle);

    // Back
    glColor3f(0, 1, 0);
    rotatedVertex(-1, -1, -1, angle);
    rotatedVertex(-1, 1, -1, angle);
    rotatedVertex(1, 1, -1, angle);
    rotatedVertex(1, -1, -1, angle);

    // Top
    glColor3f(0, 0, 1);
    rotatedVertex(-1, 1, -1, angle);
    rotatedVertex(-1, 1, 1, angle);
    rotatedVertex(1, 1, 1, angle);
    rotatedVertex(1, 1, -1, angle);

    // Bottom
    glColor3f(1, 1, 0);
    rotatedVertex(-1, -1, -1, angle);
    rotatedVertex(1, -1, -1, angle);
    rotatedVertex(1, -1, 1, angle);
    rotatedVertex(-1, -1, 1, angle);

    // Right
    glColor3f(0, 1, 1);
    rotatedVertex(1, -1, -1, angle);
    rotatedVertex(1, 1, -1, angle);
    rotatedVertex(1, 1, 1, angle);
    rotatedVertex(1, -1, 1, angle);

    // Left
    glColor3f(1, 0, 1);
    rotatedVertex(-1, -1, -1, angle);
    rotatedVertex(-1, -1, 1, angle);
    rotatedVertex(-1, 1, 1, angle);
    rotatedVertex(-1, 1, -1, angle);

    glEnd();
}

void display() {
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glLoadIdentity();

    drawCube(angle);  // Rotate by 45 degrees manually

    glFlush();  // Static image
}

void init() {
    glEnable(GL_DEPTH_TEST);
    glClearColor(0, 0, 0, 1);
    
    glMatrixMode(GL_PROJECTION);
    //glLoadIdentity();
    glOrtho(-3, 3, -3, 3, -3, 3); // Orthographic projection
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int ,int){
    switch(key){
        case 'r':
            angle=angle+10;
            glutPostRedisplay();
            break;
        case 't':
            angle=angle-10;
            glutPostRedisplay();
            break;    
    }
}
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Manual Rotated Cube - Y Axis");

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
