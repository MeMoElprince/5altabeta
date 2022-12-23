#include <bits/stdc++.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <mmsystem.h>
#include <GL/gl.h>
#include <GL/glut.h>
using namespace std;


float speed=15;
int Gamex=20,Gamey=20,length=0;
int step=0,cntr=0;
int x=Gamex/2,y=0;
int xrand=(rand()%Gamex),yrand=Gamey+2;
bool Over=false,eaten=true;
int addtoSpeed=0,ff=0;

// current color
int curr_r = 1, curr_g = 0, curr_b = 0;

int randColorfood=0,randColorbox=0,res1=0,res2=0;
int rfood,gfood,bfood;
int rbox,gbox,bbox;

void render(float x,float y,void *font,char *string){
    char *t;
    glRasterPos2f(x,y);
    for(t=string;*t!='\0';t++){
        glutBitmapCharacter(font,*t);
    }
}

void counter(){
    glColor3f(1,1,1);
    char c[400]={0};
    itoa(cntr,c,10);
    render(Gamex-1,Gamey-1,GLUT_BITMAP_TIMES_ROMAN_24,c);
}

void Box(){
    if(step==1 and x-2>0)x-=4,step=0;
    else if(step==3 and x+1<Gamex-1)x+=4,step=0;
    if(rbox==0 and gbox==0 and bbox==0 )rbox=1;
    glColor3f(1,gbox,bbox);
    curr_r = 1, curr_g = gbox, curr_b = bbox;
    glRectd(x-2,y,x+2,y+1);
    if(y==yrand and (x-1==xrand or x-2==xrand or x==xrand or x+1==xrand)){
        if(gfood==gbox and bfood==bbox){//Same Color
            eaten=true;
            cntr++;
            rbox=(rand()%2);
            gbox=(rand()%2);
            bbox=(rand()%2);
            //cout<<'\a';
        }else
            Over=true;
    }
}
int holder = -1;
void food(){
    if(eaten==true or yrand<0){
        holder = -1;
        rfood=(rand()%2);
        gfood=(rand()%2);
        bfood=(rand()%2);
        double res = 2 + rand() % 17 ;

        xrand = res,yrand=Gamey+2;
        if(eaten==true){
            if(ff!=0)sndPlaySound("Coin.wav",SND_ASYNC);
            addtoSpeed++;
            ff++;
        }
        eaten=false;
        if(addtoSpeed==2){
            speed+=3;
            addtoSpeed=0;
        }
    }
    if(rfood==0 and gfood==0 and bfood==0)rfood=1;
    // Probability to respawn the current color
    int test = (rand() % 6);
    if(test <= 1 && (holder == -1 || holder == 1)){
        holder = 1;
        gfood = curr_g;
        bfood = curr_b;
        glColor3f(1,curr_g,curr_b);
    }else{
        holder = 0;
    }

    glColor3f(1,gfood,bfood);
    glRectd(xrand,yrand,xrand+1,yrand+1);
    yrand--;
    length++;
}



void keyboard(int k,int x,int y){
    // 1 Left
    // 3 Right
    if(k==GLUT_KEY_LEFT){
        step=1;
    }
    else if(k==GLUT_KEY_RIGHT){
        step=3;
    }


}
void reshape(int a,int b){
    glViewport(0,0,(GLsizei)a,(GLsizei)b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,Gamex,0,Gamey);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/speed,timer,0);
}


void MainGame(){
    glClear(GL_COLOR_BUFFER_BIT);
    food();
    Box();
    counter();
    glutSwapBuffers();
    if(Over==true){
        char c[20]={0},res[9]="Score : ";
        itoa(cntr,c,10);
        strcat(res,c);
        sndPlaySound("GameOver.wav",SND_SYNC);
        MessageBox(NULL,res,"Don't Cry :(",0);

        exit(0);
    }
}

int main(int argc, char** argv)
{
    //Initialize GLUT and creat The Window
    glutInit(&argc, argv);
    glutInitWindowPosition(80,50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutCreateWindow("Game");

    //Create Main Functions
    glutDisplayFunc(MainGame);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutTimerFunc(0,timer,0);


    //change Color of Window
    glClearColor(0,0,0,0);


    glutMainLoop();


    return 0;
}

