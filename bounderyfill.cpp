#include<GL\freeglut.h>
#include<GL\gl.h>
#include<math.h>
using namespace std;
bool isrotated=false;
float cx=75,cy=75;
class pixel{
    public:
    GLubyte r,g,b;
};
pixel f_color,b_color;
void rotatepoint(float x,float y,int degree, float cx,float cy,float &rx,float &ry ){
    float angle=degree *(M_PI/180.0);
    float dx = x-cx;
    float dy = y-cy;
    rx=cx+dx*cos(angle)-dy*sin(angle);
    ry=cy+dx*sin(angle)+dy*cos(angle);
}
void rotateline(float x1,float y1,float x2,float y2,int angle){
    float rx1,ry1,rx2,ry2;
    rotatepoint(x1,y1,angle,cx,cy,rx1,ry1);
    rotatepoint(x2,y2,angle,cx,cy,rx2,ry2);
    glBegin(GL_LINES);
    glVertex2f(rx1,ry1);
    glVertex2f(rx2,ry2);
    glEnd();
}
void bounderyfill(int x, int y){
    pixel c;
    glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&c);
    if((c.r!=b_color.r || c.g!=b_color.g ||c.b!=b_color.b)&&(c.r!=f_color.r || c.g!=f_color.g ||c.b!=f_color.b) ){
        glColor3ub(f_color.r,f_color.g,f_color.b);

        glBegin(GL_POINTS);
        glVertex2i(x,y);
        glEnd();
        glFlush();

        bounderyfill(x+1, y);
        bounderyfill(x, y+1);
        bounderyfill(x-1, y);
        bounderyfill( x, y-1);
    }
}
void drawRotatedSquare(int angle){
    rotateline(50,50,100,50,angle);
    rotateline(100,50,100,100,angle);
    rotateline(100,100,50,100,angle);
    rotateline(50,100,50,50,angle);
    b_color.r=0;
    b_color.g=0;
    b_color.b=0;

    f_color.r=0;
    f_color.g=0;
    f_color.b=255;
   
    bounderyfill(75,75);
}
void drawsquare(){
    glBegin(GL_LINES);
    glVertex2i(50, 50);
    glVertex2i(100, 50);

    glVertex2i(100, 50);
    glVertex2i(100, 100);

    glVertex2i(100, 100);
    glVertex2i(50, 100);

    glVertex2i(50, 100);
    glVertex2i(50, 50);
    glEnd();
}
void Display(){
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear( GL_COLOR_BUFFER_BIT);
    glColor3ub(0,0,0);
    int angle=45;
    if(!isrotated){
        drawsquare();
    }
    else{
        drawRotatedSquare(angle);
    }
    glFlush();
}
void keyboard(unsigned char key, int, int) {
    switch (key) {
        // Translation
        case 'w':
            isrotated=true;
            glutPostRedisplay();
            break;
        case 'q': 
            isrotated = false;
            glutPostRedisplay();
            break;
    }
    
}
int main(int argc,char ** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(500,500);
    glutCreateWindow("bdf");
    glOrtho(0,500,0,500,-1,1);
    glutDisplayFunc(Display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}