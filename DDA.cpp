
#include<GL/glu.h>
#include<GL/gl.h>
#include<stdio.h>
#include<cmath>
#include<GL\freeglut.h>
void putPoint(int x,int y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void DDA(int x1,int y1,int x2,int y2){
    int dx=abs(x2-x1);
    int dy=abs(y2-y2);
    int steps=dx>dy?dx:dy;
    float xinc=dx/(float)steps;
    float yinc=dy/(float)steps;
    int x=x1;
    int y=y1;
    for(int i=0;i<=steps;i++){
        putPoint(round(x),round(y));
        x=x+xinc;
        y=y+yinc;
    }
}
void DDA_DOTTED(int x1,int y1,int x2, int y2){
    int dy;
    int dx;
    dx=x2-x1;
    dy=y2-y1;
    int steps=dx<dy?abs(dy):abs(dx);
    float incx=dx/(float)steps;
    float incy=dy/(float)steps;
    float x=x1;
    float y=y1;
    for(int i=0;i<=steps;i++){
        if(i%2==0)
            putPoint(round(x),round(y));
        x=x+incx;
        y=y+incy;
    }
}
void DDA_DASH(int x1,int y1,int x2, int y2){
    int dy;
    int dx;
    dx=x2-x1;
    dy=y2-y1;
    int steps=dx<dy?abs(dy):abs(dx);
    float incx=dx/(float)steps;
    float incy=dy/(float)steps;
    float x=x1;
    float y=y1;
    for(int i=0;i<=steps;i++){
        if((i/5)%2==0)
            putPoint(round(x),round(y));
        x=x+incx;
        y=y+incy;
    }
}
void fun1(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.4,0.4,0.2);
    DDA(100,0,100,100);
    DDA_DASH(0,0,100,100);
    DDA_DOTTED(50,50,-100,-100);
    glFlush();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutCreateWindow("new window");
    gluOrtho2D(-250,250,-250,250);
    glClearColor(1.0,1.0,1.0,0);
    glutDisplayFunc(fun1);
    glutMainLoop();
    return 0;
}