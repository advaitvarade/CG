#include<GL\freeglut.h>
int framecount=0;
void drawWindMill(){
    glColor3f(0,1,1);
    glBegin(GL_QUADS);
    glVertex2i(-5,0);
    glVertex2i(5,0);
    glVertex2i(5,-100);
    glVertex2i(-5,-100);
    glEnd();

    glRotated(2*framecount,0,0,1);

    glColor3f(1,0,0);
    for(int i=0;i<4;i++){
        
        glRotated(90,0,0,1);
        glBegin(GL_TRIANGLES);
        glVertex2f(0,0);
        glVertex2i(50,10);
        glVertex2i(50,-10);
        glEnd();
    }
    
}
void display(){
    glClearColor(1,1,1,1);
    glClear(GL_COLOR_BUFFER_BIT);
    glPushMatrix();
    drawWindMill();
    glPopMatrix();
    glutSwapBuffers();
}
void doframe(int v){
    framecount++;
    glutPostRedisplay();
    glutTimerFunc(10,doframe,0);
}

int main(int argc,char**argv){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(500,500);
    glutCreateWindow("animation");
    gluOrtho2D(-250,250,-250,250);
    glutDisplayFunc(display);
    glutTimerFunc(10, doframe, 0);
    glutMainLoop();
    return 0;
}