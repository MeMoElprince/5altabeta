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
#include <GL/glut.h>
using namespace std;



float speed=10, total = 0, hits = 0, lx, ly;
bool check = 0;

void MainGame();
void done(int);
void ss(int);

map<pair<int,int>, bool> mp;
vector<pair<pair<int, int>, int>> v(3), build;

bool music = 1, disable = 1;

void ss(int){
    music = 1;
}

void display(){

    for(int i=0; i<3; i++){
        if(check == 1){
            if(lx >= v[i].first.first && lx <= v[i].first.first + 30 + (20 * v[i].second) && ly >= v[i].first.second && ly <= v[i].first.second + 30 + (20 * v[i].second)){
                sndPlaySound("Hit.wav", SND_ASYNC);
                mp[{v[i].first.first, v[i].first.second}] = 0;
                hits++;
                for(int j = (rand() % build.size()), w = 0; w < build.size(); j = (j+1)%build.size(), w++){
                    if(mp[{build[j].first.first, build[j].first.second}] == 0){
                        v[i].first.first = build[j].first.first;
                        v[i].first.second = build[j].first.second;
                        v[i].second = build[j].second;
                        mp[{v[i].first.first, v[i].first.second}] = 1;
                        break;
                    }
                }
            }
        }
    }
    total += check;
    check = 0;
    for(auto&i:v){
        glColor3f(1,0,0);
        glRectd(i.first.first, i.first.second, i.first.first + 30 + (20 * i.second), i.first.second + 30 + (20 * i.second));
    }
}
bool active = 0;
void MouseClicks(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        if(!active)
            glutTimerFunc(30000, done, 0), active = 1;
        check = true;
        lx = x;
        ly = 600 - y;
    }
}

void squares(){
    for(int i = 100; i <= 500; i += 90){
        for(int j = 100; j<= 500; j += 90){
            build.push_back({{i, j}, 2});
            build.push_back({{i, j}, 1});
            build.push_back({{i, j}, 0});
        }
    }
}

void reshape(int a,int b){
    squares();
    auto rng = std::default_random_engine {};
    shuffle(build.begin(), build.end(), rng);
    for(int i=rand() % build.size(), j = 0; j<3; i = (i + 1) % build.size(), j++){
        v[j].first.first = build[i].first.first;
        v[j].first.second = build[i].first.second;
        v[j].second = build[i].second;
        mp[{v[j].first.first, v[j].first.second}] = 1;
    }
    glViewport(0,0,(GLsizei)a,(GLsizei)b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,600,0,600,-1,1);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/speed,timer,0);
}

void done(int){
    string s = "Score : " + to_string((int)hits);
    string holder = to_string(100.0 * (hits / total)), temp = "";
    for(int i=0; i<holder.size(); i++){
        temp += holder[i];
        if(holder[i] == '.'){
            temp += holder[i+1];
            temp += holder[i+2];
            break;
        }
    }
    s += "\nAccuracy : " + temp + "%";
    MessageBox(NULL,s.c_str(),"Training Finished.",0);
    exit(0);
}


void MainGame(){
    glClear(GL_COLOR_BUFFER_BIT);
    display();
    glutSwapBuffers();
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
    glutMouseFunc(MouseClicks);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    //sndPlaySound("music.wav", SND_ASYNC);


    //change Color of Window
    glClearColor(0,0,0,0);
    glutMainLoop();
    return 0;
}

