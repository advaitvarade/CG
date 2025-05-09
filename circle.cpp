#include<iostream>
#include<GL/freeglut.h>
#include<GL/gl.h>
#include<math.h>
using namespace std;
void rotatePoint(double degree,float x,float y,float xc,float yc,float& rx,float & ry){
    double radian=degree*(M_PI/180.0);
    float dx=x-xc;
    float dy=y-yc;
    rx= xc+dx*cos(radian)-dy*sin(radian);
    ry= yc+dx*sin(radian)+dy*cos(radian);
}
void plotpixel(int xc,int yc,int x,int y){
    glBegin(GL_POINTS);
    glVertex2f(xc+x,yc+y);
    glVertex2f(xc+y,yc+x);
    glVertex2f(xc-x,yc+y);
    glVertex2f(xc+y,yc-x);
    glVertex2f(xc+x,yc-y);
    glVertex2f(xc-y,yc+x);
    glVertex2f(xc-x,yc-y);
    glVertex2f(xc-y,yc-x);
    glEnd();
}
void breshCircle(int xc,int yc,int r){
    int x=0,y=r;
    int d=3-2*r;
    while(y>=x){
        plotpixel(xc,yc,x,y);
        if(d<0){
            d=d+4*x+6;
        }
        else{
            d=d+4*(x-y)+10;
            y--;
        }
        x++;
    }
}
void displayCircle1(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    int xc,yc;
    cout<<"Enter value";
    cin>>xc>>yc;
    breshCircle(xc,yc,100);
    breshCircle(xc,yc,80);
    float x =xc;
    float y =yc+110;
    for(int i=0;i<33;i++){
        breshCircle(x,y,10);
        rotatePoint(11,x,y,xc,yc,x,y);
    }
    glFlush();
}
void displayCircle2(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    float xc,yc;
    cout<<"Enter value";
    cin>>xc>>yc;
    breshCircle(xc,yc,100);
    breshCircle(xc,yc,50);
    float x=xc,y=yc+50;
    for(int i=0;i<12;i++){
        breshCircle(x,y,50);
        rotatePoint(30,x,y,xc,yc,x,y);
    }
    glFlush();
}
void displayCircle3(){
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,1,1);
    glTranslated(0,-100,0);
    breshCircle(0,0,50);
    breshCircle(0,-70,20);
    glPushMatrix();
    glRotated(33,0,0,1);
    breshCircle(0,-70,20);  
    glRotated(293,0,0,1);
    breshCircle(0,-70,20);
    glPopMatrix();
    breshCircle(0,-110,20);
    int x= 50,y=50;
    for(int i=0;i<5;i++){
        breshCircle(x,y,20);
        breshCircle(-x,y,20);
        x=x+30;
        y=y+30;
    }
    
    glFlush();
}
int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(50,50);
    glutCreateWindow("circle");
    glOrtho(-250,250,-250,250,-1,1);
    glutDisplayFunc(displayCircle3);
    glutMainLoop();
}