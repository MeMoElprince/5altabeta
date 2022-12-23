#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>
using namespace std;



float speed=10;
int Gamex=20,Gamey=20;
int step=2,cntr=0,eatenCounter=0,length=3;
double x[400]={Gamex/2,Gamex/2+1,Gamex/2+2},y[400]={Gamey/2,Gamex/2,Gamex/2};
int xrand=(rand()%Gamex)+1,yrand=(rand()%Gamey)+1;
bool Over=false,eaten=true;

void MainGame();

queue<int> q;
map<pair<int,int>, bool> mp;

void single_move(){
    if(step==1)x[0]--;
    else if(step==2)y[0]++;
    else if(step==3)x[0]++;
    else if(step==4)y[0]--;
}
int pos=0,posCntr=0;

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

void addEyetoHead(){
    if(pos%2==0){
        // When Up or Down
        glColor3f(1,1,1);
        glRectd(x[0]+0.09,y[0]+0.5,x[0]+0.4,y[0]+0.8);
        glColor3f(1,1,1);
        glRectd(x[0]+0.8,y[0]+0.5,x[0]+0.5,y[0]+0.8);
    }else{
        // When Right or Left
        glColor3f(1,1,1);
        glRectd(x[0]+0.3,y[0]+0.2,x[0]+0.6,y[0]+0.5);
        glColor3f(1,1,1);
        glRectd(x[0]+0.3,y[0]+0.6,x[0]+0.6,y[0]+0.9);
    }
}

void Snake(){
    mp.clear();
    for(int i=length - 1;i>0;i--){
        x[i]=x[i-1];
        y[i]=y[i-1];
    }

    // giving priority of the moves
    if(q.size()){
        int temp = q.front();
        if(temp==1 and step != 3){
                pos=1;

                x[0]--, step = temp;

        }
        else if(temp==2 and step != 4){
                pos=2;

                y[0]++, step = temp;

        }
        else if(temp==3 and step != 1){
                pos=3;
                x[0]++, step = temp;
        }
        else if(temp==4 and step != 2){
                pos=4;
                y[0]--, step = temp;
        }
        else {
                single_move();
        }
        addEyetoHead();
        q.pop();
    }else{
        addEyetoHead();
        single_move();
    }
    if(x[0]>=Gamex)x[0]=0;
    if(x[0]<0)x[0]=Gamex;
    if(y[0]<0)y[0]=Gamey-1;
    if(y[0]>=Gamey)y[0]=0;

    for(int i=0;i<length;i++){
        glColor3f(1,0,0);
        glRectd(x[i],y[i],x[i]+1,y[i]+1);
        mp[{x[i], y[i]}] = true;
    }

    // if x increase of decrease

    // if y

    for(int i=2;i<length;i++){
        if(x[i]==x[0] and y[i]==y[0])Over=true;
    }

    if(x[0]==xrand and y[0]==yrand){
        eaten=true;
        length++;
        cntr++;
        //sndPlaySound("Coin.wav",SND_ASYNC);
    }

    if(posCntr==0){
        glColor3f(1,1,1);
        glRectd(x[0]+0.3,y[0]+0.2,x[0]+0.5,y[0]+0.5);
        glColor3f(1,1,1);
        glRectd(x[0]+0.3,y[0]+0.6,x[0]+0.5,y[0]+0.9);
        posCntr++;
    }else{
        addEyetoHead();
    }



    if(eatenCounter%2==0 && eaten == true && cntr <= 40)speed *= 1.001;

}

void keyboard(int k,int x,int y){
    // 1 l
    // 2 u
    // 3
    /*if(wait == 1){
        wait = 0;
        return;
    }*/
    if(k==GLUT_KEY_RIGHT){
        q.push(3);
    }else if(k==GLUT_KEY_LEFT){
        q.push(1);
    }else if(k==GLUT_KEY_UP){
        q.push(2);
    }else if(k==GLUT_KEY_DOWN){
        q.push(4);
    }
}

void food(){
    if(eaten==true){
        xrand=(rand()%Gamex),yrand=(rand()%Gamey);
        while(mp[{xrand,yrand}] == true){
            int flag = (rand() % 2);
            if(flag == 1){
                xrand = (xrand + 1) % Gamex;
            }else{
                yrand = (yrand + 1) % Gamey;
            }
        }
        eaten=false;
        eatenCounter++;
    }

    glColor3f(0,1,0);
    glRectd(xrand,yrand,xrand+1,yrand+1);

}


void reshape(int a,int b){
    glViewport(0,0,(GLsizei)a,(GLsizei)b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,Gamex,0,Gamey,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/speed,timer,0);
}

void MainGame(){
    glClear(GL_COLOR_BUFFER_BIT);
    Snake();
    food();
    counter();
    glutSwapBuffers();
    if(Over==true){
        char c[20]={0},res[9]="Score : ";
        itoa(cntr,c,10);
        strcat(res,c);
        MessageBox(NULL,res,"Don't Cry :(",0);
        // Try to add MaxScore
        exit(0);
    }
}

int main(int argc, char** argv)
{
    //Initialize GLUT and create The Window
    glutInit(&argc, argv);
    glutInitWindowPosition(80,50);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutCreateWindow("Game");

    //Create Main Functions
    glutDisplayFunc(MainGame);
    glutSpecialFunc(keyboard);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    //sndPlaySound("music.wav", SND_ASYNC);


    //change Color of Window
    glClearColor(0,0,0,0);
    glutMainLoop();
    return 0;
}

