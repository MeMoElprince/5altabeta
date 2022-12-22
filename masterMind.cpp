#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cmath>
// #include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
// #include <windows.h>
// #include <mmsystem.h>
// #include <GL/glui.h>
using namespace std;
 
 
 
float speed=10;
int lvl = 0;
bool won = 1, over = 0;
 
void MainGame();
void newrow();
 
map<int, bool> mp, vis;
vector<vector<double>> build;
vector<vector<int>> color(11, vector<int>(4)), correctness(11, vector<int>(4, 0));
vector<int> ans(4);
 
void render(float x, float y, void *font, char *string){
    char *c;
    glRasterPos2f(x, y);
    for(c = string; *c != '\0'; c++){
        glutBitmapCharacter(font, *c);
    }
}
void text(string s, float x, float y, int cc){
    glColor3f(cc, cc, cc);
    char t[100] = {0};
    snprintf(t, s.size() + 1, s.c_str());
    render(x, y, GLUT_BITMAP_TIMES_ROMAN_24, t);
}
 
void pressed(){
    int inplace = 0, correct = 0;
    for(int i=0; i<4; i++){
        for(int j = 0; j<4; j++){
            correct += (ans[j] == color[lvl][i]);
        }
    }
    for(int i=0; i<4; i++){
        inplace += (ans[i] == color[lvl][i]);
    }
    if(inplace == 4 || lvl == 9){
        over = 1;
        won = (inplace == 4 ? 1 : 0);
    }
    correct -= inplace;
    int idx = 2;
    for(int i=0; i<4; i++, idx = (idx + 1) % 4){
        if(inplace){
            correctness[lvl][idx] = 1;
            inplace--;
            continue;
        }
        if(correct){
            correctness[lvl][idx] = 2;
            correct--;
            continue;
        }
    }
    lvl++;
    if(!over)
        newrow();
}
 
void emptyrect(int x, int y, int cc)
{
    glColor3f(cc,cc,cc);
    glBegin(GL_LINE_LOOP);
        glVertex2i(x, y);
        glVertex2i(x + 61,y);
        glVertex2i(x + 61,y + 46);
        glVertex2i(x,y + 46);
    glEnd();
    glFlush();
}
void newrow(){
    vis.clear();
    for(int i=0; i<4; i++){
        if(lvl == 0){
            vis[i] = 1;
            color[lvl][i] = i;
        }else{
            color[lvl][i] = color[lvl - 1][i];
            vis[color[lvl - 1][i]] = 1;
        }
    }
}
void display(){
    glColor3f(1,1, 1);
    glRectd(490, 375, 590, 425);
    text("Guess", 508, 393, 0);
    text("Hidden:", 30, 42, 1);
    int currx = 30, curry = 140, ex = 30, ey = 140;
    for(int i=0; i<10; i++){
        for(int j=0; j<4; j++){
            emptyrect(ex, ey, 1);
            ex += 90;
        }
        emptyrect(ex + 15, ey, 0);
        ex = 30;
        ey += 55;
    }
    for(int i = 135, j = 0; i<=135 + (90*3); i += 90, j++){
            emptyrect(i, 27, 0);
        if(over == 0){
            text("?", i + 24, 42, 1);
        }else{
            double r, g, b;
            r = build[ans[j]][0];
            g = build[ans[j]][1];
            b = build[ans[j]][2];
            glColor3f(r,g, b);
            glRectd(i, 27, i + 60, 27 + 46 - 1);
        }
    }
    glColor3f(0,0, 0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(390, 100);
        glVertex2i(390,701);
        glVertex2i(480,701);
        glVertex2i(480, 100);
    glEnd();
    glBegin(GL_LINE_LOOP);
        glVertex2i(0, 100);
        glVertex2i(701,100);
    glEnd();
    for(int j=0; j <= lvl - over && j < 10; j++){
    for(int i=0; i<4; i++){
        double r, g, b;
        r = build[color[j][i]][0];
        g = build[color[j][i]][1];
        b = build[color[j][i]][2];
        glColor3f(r,g, b);
        glRectd(currx + (90 * i), curry, currx +(90 * i) + 60, curry + 45);
    }
    curry += 55;
    }
    curry = 147;
    for(int i=0; i <= lvl - over && i < 10; i++){
        for(int j=0; j<4; j++){
            double r, g, b;
            if(correctness[i][j] == 0) r = g = b = 1;
            else if(correctness[i][j] == 1) r = g = b = 0;
            else r = g = b = 0.5;
            glColor3f(r,g, b);
            glRectd(417 + (25 * (j % 2)), curry + (20 * (j >= 2)), 417 + (25 * (j % 2)) + 10, curry + 10 + (20 * (j >= 2)));
        }
        curry += 55;
    }
}
bool active = 0;
void MouseClicks(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        y = 700 - y;
        int curr_linex = 30, curr_liney = 140 + (55 * lvl);
        if(x >= 490 && x <= 590 && y >= 375 && y <=425)
            pressed();
        for(int i=0; i<4; i++){
            if(x >= curr_linex && x <= curr_linex + 60 && y >= curr_liney && y <= curr_liney + 45){
                int w = (color[lvl][i] + 1) % build.size();
                vis[color[lvl][i]] = 0;
                while(vis[w] == 1){
                    w = (w + 1) % build.size();
                }
                vis[w] = 1;
                color[lvl][i] = w;
            }
            curr_linex += 90;
        }
    }
}
 
 
void reshape(int a,int b){
    for(int i=0; i<(1<<3); i++){
        vector<double> temp(3);
        for(int j=0; j<3; j++){
            if((1<<j) & i)
                temp[j] = 1;
        }
        if(temp[0] != 1 || temp[1] != 1 || temp[2] != 1)
        build.push_back(temp);
    }
    build.push_back({0.5,0.5,0.5});
    build.push_back({0.5,0.2,0.1});
    build.push_back({0.8,0.5,0.4});
    for(int i=0; i<ans.size(); i++){
        int chosen = (rand() % build.size());
        while(mp[chosen] == 1){
            chosen = (rand() % build.size());
        }
        mp[chosen] = 1;
        ans[i] = chosen;
    }
    newrow();
    glViewport(0,0,(GLsizei)a,(GLsizei)b);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0,600,0,700,-1,1);
    glMatrixMode(GL_MODELVIEW);
}
 
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/speed,timer,0);
}
 
 
void MainGame(){
    glClear(GL_COLOR_BUFFER_BIT);
    display();
    glutSwapBuffers();
    if(over == true){
        string s;
        s = (won == 1 ? "Good Job! you did it." : "Hard Luck, You Lost");
        // MessageBox(NULL,s.c_str(),"Game Over.",0);
        exit(0);
    }
}
 
int main(int argc, char** argv)
{
    //Initialize GLUT and create The Window
    glutInit(&argc, argv);
    glutInitWindowPosition(80,50);
    glutInitWindowSize(600, 700);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutCreateWindow("Mastermind");
 
    //Create Main Functions
    glutDisplayFunc(MainGame);
    glutMouseFunc(MouseClicks);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,timer,0);
    //sndPlaySound("music.wav", SND_ASYNC);
 
 
    //change Color of Window
    glClearColor(0.1, 0.3, 0.2, 1);
    glutMainLoop();
    return 0;
}