#include<GL/glut.h>
#include<GL/glu.h>
#include<cmath>
#include<algorithm>
using namespace std;
void putpixel(int x,int y){
    glBegin(GL_POINTS);
    glVertex2f(x,y);
    glEnd();
}
void Bresenhams(int x1,int y1, int x2,int y2){
    bool s=false;
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);
    int sx=x2>x1?1:-1;
    int sy=y2>y1?1:-1;
    if(dy>dx){
        swap(dx,dy);
        s=true;
    }
    int x=x1;
    int y=y1;
    int p=2*dy-dx;
    for(int i=0;i<=dx;i++){
        putpixel(x,y);
        if(p>=0){
            if(s==true){
                x=x+sx;
            }
            else{
                y=y+sy;
            }
            p=p+2*dy-2*dx;
        }
        if(s==true){
            y=y+sy;
        }
        else{
            x=x+sx;
        }
        p=p+2*dy;
        
    }

}


void Bresenhams_Dotted(int x1,int y1,int x2,int y2){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);;

    int sx=x1>x2?-1:1;
    int sy=y1>y2?-1:1;

    bool swap=false;
    if(dy>dx){
        int temp=dy;;
        dy=dx;
        dx=temp;
        swap=true;
    }

    int p=2*dy-dx;
    int x=x1;
    int y=y1;
    for(int i=0;i<=dx;i++){
        if(i%2==0)
            putpixel(x,y);
        if(p>=0){
            if(swap){
                x=x+sx;
            }
            else{
                y=y+sy;
            }
            p=p+2*dy-2*dx;
        }
        if(swap){
            y=y+sy;
        }
        else{
            x=x+sx;
        }
        p=p+2*dy;
    }
}
void Bresenhams_Dashed(int x1,int y1,int x2,int y2){
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);;

    int sx=x1>x2?-1:1;
    int sy=y1>y2?-1:1;

    bool swap=false;
    if(dy>dx){
        int temp=dy;;
        dy=dx;
        dx=temp;
        swap=true;
    }

    int p=2*dy-dx;
    int x=x1;
    int y=y1;
    for(int i=0;i<=dx;i++){
        if((i/5)%2==0)
            putpixel(x,y);
        if(p>=0){
            if(swap){
                x=x+sx;
            }
            else{
                y=y+sy;
            }
            p=p+2*dy-2*dx;
        }
        if(swap){
            y=y+sy;
        }
        else{
            x=x+sx;
        }
        p=p+2*dy;
    }
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    Bresenhams(0,0,30,30);
    Bresenhams_Dotted(30,0,0,-30);
    Bresenhams_Dashed(0,0,50,50);
    glBegin(GL_LINES);
    glVertex2f(250,0);
    glVertex2f(-250,0);
    glVertex2f(0,250);
    glVertex2f(0,-250);
    glEnd();
    glFlush();

}

int main(int args,char ** argv){
    glutInit(&args,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Bresh");
    gluOrtho2D(-250,250,-250,250);
    glClearColor(1,1,1,0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}