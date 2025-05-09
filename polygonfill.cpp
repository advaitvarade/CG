#include <GL/freeglut.h>
#include <GL/gl.h>
#include <math.h>

typedef struct pixel {
    GLubyte r, g, b;
} pixel;

pixel f_color, b_color;

void rotatePoint(float x, float y, float cx, float cy, float angle, float &rx, float &ry) {
    float radians = angle * M_PI / 180.0;
    float dx = x - cx;
    float dy = y - cy;

    rx = cx + dx * cos(radians) - dy * sin(radians);
    ry = cy + dx * sin(radians) + dy * cos(radians);
}

bool isBoundaryColor(pixel c) {
    return (c.r == b_color.r && c.g == b_color.g && c.b == b_color.b);
}

void boundary_fill(int x, int y) {
    pixel c;
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &c);

    // Check if the current pixel is not boundary or fill color
    if (!isBoundaryColor(c) && (c.r != f_color.r || c.g != f_color.g || c.b != f_color.b)) {
        // Set fill color
        glColor3ub(f_color.r, f_color.g, f_color.b);

        // Draw pixel
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        // Recursive calls for adjacent pixels
        boundary_fill(x + 1, y);
        boundary_fill(x - 1, y);
        boundary_fill(x, y + 1);
        boundary_fill(x, y - 1);
    }
}

void drawRotatedLine(float x1, float y1, float x2, float y2, float cx, float cy, float angle) {
    float rx1, ry1, rx2, ry2;
    rotatePoint(x1, y1, cx, cy, angle, rx1, ry1);
    rotatePoint(x2, y2, cx, cy, angle, rx2, ry2);

    glVertex2f(rx1, ry1);
    glVertex2f(rx2, ry2);
}

void renderFunction2() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);

    float angle = 45;      // Rotation angle
    float cx = 150, cy = 150;  // Center of rotation

    glColor3f(0, 0, 0); // Boundary color
    glBegin(GL_LINE_LOOP);
    float rx, ry;
    rotatePoint(90, 90, cx, cy, angle, rx, ry); glVertex2f(rx, ry);
    rotatePoint(90, 210, cx, cy, angle, rx, ry); glVertex2f(rx, ry);
    rotatePoint(210, 210, cx, cy, angle, rx, ry); glVertex2f(rx, ry);
    rotatePoint(210, 90, cx, cy, angle, rx, ry); glVertex2f(rx, ry);
    glEnd();

    // Draw internal grid lines (rotated)
    glBegin(GL_LINES);
    drawRotatedLine(120, 90, 120, 210, cx, cy, angle);
    drawRotatedLine(150, 90, 150, 210, cx, cy, angle);
    drawRotatedLine(180, 90, 180, 210, cx, cy, angle);
    drawRotatedLine(90, 120, 210, 120, cx, cy, angle);
    drawRotatedLine(90, 150, 210, 150, cx, cy, angle);
    drawRotatedLine(90, 180, 210, 180, cx, cy, angle);
    glEnd();

    glFlush();

    // Set boundary color (black)
    b_color.r = 0;
    b_color.g = 0;
    b_color.b = 0;

    // You need to manually pick correct fill points based on new rotated positions.
    // These are approximated manually by trial, feel free to adjust as needed.

    f_color = {0, 255, 0};   boundary_fill(150, 100); // green
    f_color = {255, 0, 0};   boundary_fill(150, 130); // red
    f_color = {255, 255, 0}; boundary_fill(120, 130); // yellow
    f_color = {0, 0, 255};   boundary_fill(180, 130); // blue
    f_color = {255, 255, 255}; boundary_fill(180, 180); // white
}


void renderFunction1() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    // Set boundary color (Yellow)
    glColor3f(0, 0, 0);

    // Draw rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2f(90, 90);
    glVertex2f(90, 210);
    glVertex2f(210, 210);
    glVertex2f(210, 90);
    glEnd();

    // Draw internal grid lines
    glBegin(GL_LINES);
    glVertex2f(120, 90);
    glVertex2f(120, 210);
    glVertex2f(150, 90);
    glVertex2f(150, 210);
    glVertex2f(180, 90);
    glVertex2f(180, 210);
    glVertex2f(90, 120);
    glVertex2f(210, 120);
    glVertex2f(90, 150);
    glVertex2f(210, 150);
    glVertex2f(90, 180);
    glVertex2f(210, 180);
    glEnd();

    glFlush();

    // Set fill color to green
    f_color.r = 0;
    f_color.g = 255;
    f_color.b = 0;

//white
    b_color.r = 0;
    b_color.g = 0;
    b_color.b = 0;

    // Start boundary fill from inside the rectangle
    boundary_fill(91,91);
   
    f_color.r = 255;
    f_color.g = 0;
    f_color.b = 0;
    boundary_fill(121, 121);
   
    f_color.r = 255;
    f_color.g = 255;
    f_color.b = 0;
    boundary_fill(91, 121);
   
    f_color.r = 0;
    f_color.g = 0;
    f_color.b = 255;
    boundary_fill(181, 121);
   
    f_color.r = 5;
    f_color.g = 50;
    f_color.b = 50;
    boundary_fill(181, 181); 

}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("OpenGL Boundary Fill");
    glOrtho(0, 500, 0, 500, -1, 1);
    glutDisplayFunc(renderFunction1);
    glutMainLoop();

    return 0;
}