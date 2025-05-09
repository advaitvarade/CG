#include<iostream>
#include<GL\freeglut.h>
#include<math.h>
using namespace std;
int inc=3;
void koch(int inc,float x1,float y1,float x5,float y5){
    if(inc==0){
        glVertex2f(x1,y1);
        glVertex2f(x5,y5);
    }
    else{
        float dx=(x5-x1)/3;
        float dy=(y5-y1)/3;

        float x2=x1+dx;
        float y2=y1+dy;

        float x3=(0.5)*(x5+x1)+sqrt(3)*(y1-y5)/6;
        float y3=(0.5)*(y5+y1)+sqrt(3)*(x5-x1)/6;

        float x4=x1+2*dx;
        float y4=y1+2*dy;

        koch(inc-1,x1,y1,x2,y2);
        koch(inc-1,x2,y2,x3,y3);
        koch(inc-1,x3,y3,x4,y4);
        koch(inc-1,x4,y4,x5,y5);
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glBegin(GL_LINES);
    koch(inc,150,50,50,250);
    koch(inc,50,250,250,250);
    glEnd();
    glFlush(); 
}
int main(int argc,char ** argv){
    cout<<"Enter the inc"<<endl;
    cin>>inc;
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("koch");
    gluOrtho2D(0,500,0,500);
    glClearColor(1,1,1,1);
    glutDisplayFunc(display);
    glutMainLoop();
}