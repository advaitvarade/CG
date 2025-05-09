#include <stdio.h>
#include <GL/glut.h>

float xd1, yd1, xd2, yd2; // Line endpoints
int xmax = 100, ymax = 100, xmin = -100, ymin = -100;
static int clipped = 0;

void plotRectangle() {
    glColor3f(1.0, 0.0, 0.0); // Red for clipping window
    glBegin(GL_LINE_LOOP);
    glVertex2f(xmin, ymin);
    glVertex2f(xmax, ymin);
    glVertex2f(xmax, ymax);
    glVertex2f(xmin, ymax);
    glEnd();
}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
}

int computeCode(float x, float y) {
    int code = 0;
    if (y > ymax) code += 8;
    if (y < ymin) code += 4;
    if (x > xmax) code += 2;
    if (x < xmin) code += 1;
    return code;
}

int cohenSutherland(float x1, float y1, float x2, float y2,
                    float &cx1, float &cy1, float &cx2, float &cy2) {
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    int accept = 0;
    float x, y;

    while (1) {
        if ((code1 | code2) == 0) {
            accept = 1;
            break;
        } else if (code1 & code2) {
            break;
        } else {
            int codeOut = code1 ? code1 : code2;
            float m = (x2 - x1) != 0 ? (y2 - y1) / (x2 - x1) : 1e10;

            if (codeOut & 8) {
                y = ymax;
                x = x1 + (ymax - y1) / m;
            } else if (codeOut & 4) {
                y = ymin;
                x = x1 + (ymin - y1) / m;
            } else if (codeOut & 2) {
                x = xmax;
                y = y1 + m * (xmax - x1);
            } else if (codeOut & 1) {
                x = xmin;
                y = y1 + m * (xmin - x1);
            }

            if (codeOut == code1) {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }

    if (accept) {
        cx1 = x1;
        cy1 = y1;
        cx2 = x2;
        cy2 = y2;
    }
    return accept;
}

void disp() {
    glClear(GL_COLOR_BUFFER_BIT);
    plotRectangle();

    float cx1, cy1, cx2, cy2;
    if (cohenSutherland(xd1, yd1, xd2, yd2, cx1, cy1, cx2, cy2)) {
        drawLine(cx1, cy1, cx2, cy2, 0.0, 0.0, 1.0); // Clipped line in blue
    } else {
        printf("Line is completely outside the clipping window.\n");
    }

    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0);
    gluOrtho2D(-320, 320, -240, 240);
    glPointSize(2);
}

int main(int argc, char **argv) {
    printf("Window coordinates are (-100,100,-100,100)\n");
    printf("Enter line coordinates (limits: -320 to 320 for x, -240 to 240 for y)\n");

    printf("X1: ");
    scanf("%f", &xd1);
    printf("Y1: ");
    scanf("%f", &yd1);
    printf("X2: ");
    scanf("%f", &xd2);
    printf("Y2: ");
    scanf("%f", &yd2);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland Line Clipping with GL_LINES");
    init();
    glutDisplayFunc(disp);
    glutMainLoop();

    return 0;
}


