#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

void drawStars(double x, double y)
{
    glBegin (GL_POLYGON); 
        glVertex3f(0.0 * 8 + x,0.2 * 8 + y,0.0);
        glVertex3f(0.1 * 8 + x,0.1* 8+ y,0.0);
        glVertex3f(0.2 * 8 + x,0.05 * 8 + y,0.0);
        glVertex3f(0.1 * 8 + x,0.0 * 8 + y,0.0);
        glVertex3f(0.2 * 8 + x,-0.1 * 8 + y,0.0);
        glVertex3f(0.0 * 8 + x,0.0* 8 + y,0.0);
        glVertex3f(-0.2* 8 + x,-0.1 * 8 + y,0.0);
        glVertex3f(-0.1* 8 + x,0.0 * 8 + y,0.0);
        glVertex3f(-0.2* 8 + x,0.05 * 8 + y,0.0);
        glVertex3f(-0.1* 8 + x,0.1 * 8 + y,0.0);
  glEnd();
}
void drawCircleFilled (double centerX, double centerY, double radiusX, double radiusY)
{
    const float DEG2RAD = 3.14159 / 180;
    glBegin(GL_TRIANGLE_FAN);
        glVertex2d (centerX, centerY);
        for (int i = -1; i < 360; i++) 
        {
            float degInRad = i * DEG2RAD;
            glVertex2d (centerX + cos (degInRad) * radiusX, 
                            centerY + sin (degInRad) * radiusY);
        }
        
    glEnd();
}

void drawCloud(int x, int y)
{    
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x, y, 25, 15);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x + 10, y + 10, 7, 7);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x + 10, y - 10, 7, 7);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x - 10, y - 10, 7, 7);
    glColor3f(255.0, 255.0, 255.0);
    drawCircleFilled(x - 10, y + 10, 7, 7);
}
