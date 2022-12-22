#include <GL/glut.h>
#include <bits/stdc++.h>
#include "draws.h"

using namespace std;
const double PI = acos(-1);
int arrow_x = -30;
int arrowNumber = 0; // 0 -> 5;
vector<int> arrow_y = {50, 30, 10, -10, -30, -50};

void backGround()
{
  glBegin(GL_POLYGON);
  glColor3f(0.09, 0.09, 0.09);
  glVertex2d(-100, -100);
  glVertex2d(100, -100);
  glColor3f(0.18, 0.18, 0.18);
  glVertex2d(100, -80);
  glVertex2d(-100, -80);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.18, 0.18, 0.18);
  glVertex2d(-100, -80);
  glVertex2d(100, -80);
  glColor3f(0.4, 0.4, 0.4);
  glVertex2d(100, 0);
  glVertex2d(-100, 0);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.4, 0.4, 0.4);
  glVertex2d(-100, 0);
  glVertex2d(100, 0);
  glColor3f(0.18, 0.19, 0.19);
  glVertex2d(100, 80);
  glVertex2d(-100, 80);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.18, 0.19, 0.19);
  glVertex2d(-100, 80);
  glVertex2d(100, 80);
  glColor3f(0.09, 0.09, 0.09);
  glVertex2d(100, 100);
  glVertex2d(-100, 100);
  glEnd();
}

void itemsBackGround()
{
  glBegin(GL_POLYGON);
  glColor3f(0.08, 0.08, 0.08);
  glVertex2d(-50, -70);
  glVertex2d(50, -70);
  glColor3f(0.15, 0.15, 0.15);
  glVertex2d(50, -40);
  glVertex2d(-50, -40);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.15, 0.15, 0.15);
  glVertex2d(-50, -40);
  glVertex2d(50, -40);
  glColor3f(0.15, 0.15, 0.15);
  glVertex2d(50, 40);
  glVertex2d(-50, 40);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.15, 0.15, 0.15);
  glVertex2d(-50, 40);
  glVertex2d(50, 40);
  glColor3f(0.08, 0.08, 0.08);
  glVertex2d(50, 70);
  glVertex2d(-50, 70);
  glEnd();
}

void itemsToSelectBackGround()
{
  glBegin(GL_POLYGON);
  glColor3f(0.1, 0.1, 0.1);
  glVertex2d(-40, -60);
  glVertex2d(40, -60);
  glColor3f(0.2, 0.2, 0.2);
  glVertex2d(40, -30);
  glVertex2d(-40, -30);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.2, 0.2, 0.2);
  glVertex2d(-40, -30);
  glVertex2d(40, -30);
  glColor3f(0.2, 0.2, 0.2);
  glVertex2d(40, 30);
  glVertex2d(-40, 30);
  glEnd();
  glBegin(GL_POLYGON);
  glColor3f(0.2, 0.2, 0.2);
  glVertex2d(-40, 30);
  glVertex2d(40, 30);
  glColor3f(0.1, 0.1, 0.1);
  glVertex2d(40, 60);
  glVertex2d(-40, 60);
  glEnd();
}

void itemsText()
{
  vector<string> items = {"Exit", "Snake Game", "Aim Game", "Tower of Hanoi Game", "DropDown Game", "Mastermind Game"};
  glColor3f(0.9, 0.9, 0.9);
  for (int i = -50, test = 0; test < items.size(); test++, i += 20)
  {
    int x = -15;
    glRasterPos2d(x, i);
    for (int j = 0; j < items[test].size(); j++)
    {
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, items[test][j]);
    }
  }
}

void textBorder()
{
  glBegin(GL_LINE_LOOP);
  glColor3f(0.9, 0.9, 0.9);
  glVertex2d(-40, -60);
  glVertex2d(40, -60);
  glVertex2d(40, 60);
  glVertex2d(-40, 60);
  glEnd();
}

void arrowTheme()
{
  glBegin(GL_POLYGON);
  glColor3f(190.0 / 255.0, 190.0 / 255.0, 190.0 / 255.0);
  glVertex2f(arrow_x - 2.5 + 4, arrow_y[arrowNumber] - 2.5);
  glVertex2f(arrow_x + 5 + 1.3, arrow_y[arrowNumber] + 2.5 / 2.0);
  glVertex2f(arrow_x - 2.5 + 4, arrow_y[arrowNumber] + 5);
  glVertex2f(arrow_x - 7.5 + 4, arrow_y[arrowNumber] + 5);
  glVertex2f(arrow_x - 5 + 4, arrow_y[arrowNumber] + 2.5 / 2.0);
  glVertex2f(arrow_x - 7.5 + 4, arrow_y[arrowNumber] - 2.5);
  glEnd();
}


void displayName()
{
    string name = "5altabeta";
    glRasterPos2d(-10, 80);
    for (int i = 0; i < name.size(); i++)
    {
      glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, name[i]);
    }
}


void display()
{
  glClear(GL_COLOR_BUFFER_BIT);
  // background colors
  backGround();
  // drawing items' background
  itemsBackGround();
  // drawing items to select
  itemsToSelectBackGround();
  // drawing items' text
  itemsText();
  // drawing border
  textBorder();
  // drawing arrow
  arrowTheme();
  // display project name
  displayName();
  //-----------------
  glFlush();
}

int menu;

void operation()
{
  if (arrowNumber == 5)
  {
    exit(0);
  }
  else if(arrowNumber == 4)
  {
    system("xdotool getactivewindow windowminimize");
    system("g++ SnakeGame/snakeGame.cpp -o snakeGame -lglut -lGL -lGLU && ./snakeGame");
  }
  else if(arrowNumber == 3)
  { 
    system("xdotool getactivewindow windowminimize");
    system("g++ AimGame/aimGame.cpp -o aimGame -lglut -lGL -lGLU && ./aimGame");
  }
  else if(arrowNumber == 2)
  {
    system("xdotool getactivewindow windowminimize");
    system("g++ TowerOfHanoiGame/towerOfHanoi.cpp -o towerOfHanoi -lglut -lGL -lGLU && ./towerOfHanoi");
  }
  else if(arrowNumber == 1)
  {
    system("xdotool getactivewindow windowminimize");
    system("g++ DropDownGame/dropDown.cpp -o dropDown -lglut -lGL -lGLU && ./dropDown");
  }
  else if(arrowNumber == 0)
  {
    system("xdotool getactivewindow windowminimize");
    system("g++ MasterMindGame/masterMind.cpp -o masterMind -lglut -lGL -lGLU && ./masterMind");
  }
}

void Specialkey(int key, int x, int y)
{
  switch (key)
  {
  case GLUT_KEY_UP:
    if (arrowNumber > 0)
    {
      arrowNumber--;
    }
    break;
  case GLUT_KEY_DOWN:
    if (arrowNumber < 5)
    {
      arrowNumber++;
    }
    break;
  }
  glutPostRedisplay();
}
void keyBoard(unsigned char key, int x, int y)
{
  if (key == 'w')
  {
    if (arrowNumber > 0)
    {
      arrowNumber--;
    }
  }
  else if (key == 's')
  {
    if (arrowNumber < 5)
    {
      arrowNumber++;
    }
  }
  else if (key == ' ')
  {
    operation();
  }
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(-100, 100, -100, 100);
  glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowPosition(1200, 100);
  glutInitWindowSize(800, 800);
  menu = glutCreateWindow("Main Menu");
  glutKeyboardFunc(keyBoard);
  glutSpecialFunc(Specialkey);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMainLoop();
}