#include<GL\freeglut.h>
#include<math.h>
GLfloat num[4][2]={{-25,-25},{25,-25},{25,25},{-25,25}}; 
int tx=0,ty=0;
int xshear=0,yshear=0;
float angle=0.0f;
int sx=1,sy=1;
float refX=1;
float refY=1;
void transformation(){
    for(int i=0;i<4;i++){
        float x=num[i][0];
        float y=num[i][1];

        float rotx=x*cos(angle)-y*sin(angle);
        float roty=x*sin(angle)+y*cos(angle);

        float transx=rotx+tx;
        float transy=roty+ty;

        float shearx=transx+xshear*transx;
        float sheary=transy+yshear*transy;

        float scalex=shearx*sx;
        float scaley=sheary*sy;

        float reftx=refX*scalex;
        float refty=refY*scaley;

        glVertex2f(reftx,refty);
    }
}
void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,0,0);
    glBegin(GL_LINE_LOOP);
    transformation();
    glEnd();
    glFlush();

}
void keyboard(unsigned char key,int ,int){
    switch(key){
        case 'r': angle=angle+(M_PI/6);break;
        case 'd': tx=tx+10; break;
        case 'a': tx=tx-10;break;
        case 's': ty=ty-10;break;
        case 'w': ty=ty+10;break;
        case '1': sx=sx+2;sy=sy+2;break;
        case '2': sx=sx-2;sy=sy-2;break;
        case '3': refX=refX*-1;

    }
    glutPostRedisplay();
}

int main(int argc,char** argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(100,100);
    glutCreateWindow("2D transformation");
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}