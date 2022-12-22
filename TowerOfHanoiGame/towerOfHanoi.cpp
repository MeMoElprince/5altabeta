#include <GL/glut.h>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
// #include <windows.h>
// #include <mmsystem.h>
using namespace std;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);	// Set display window colour to white

	glMatrixMode(GL_PROJECTION);		// Set projection parameters


}

void quads(float a, float b, float c, float d, float e, float f, float g, float h){

    glBegin(GL_QUADS); //Begin quadrilateral coordinates

	//Trapezoid
	glVertex2f(a, b);
	glVertex2f(c,d);
	glVertex2f(e, f);
	glVertex2f(g, h);

	glEnd(); //End quadrilateral coordinates

}

void triangle(float a, float b, float c, float d, float e, float f){
   glBegin(GL_TRIANGLES);
   //Triangle
	glVertex2f(a, b);
	glVertex2f(c, d);
	glVertex2f(e, f);

	glEnd();//End triangle coordinates

}
void display();
void reshape(int , int);
void keyboard(unsigned char , int , int );
void timer(int);

bool gameover = false;
bool moving = false;

const int NUM_DISKS = 4;
const int NUM_RODS = 3;
const float SPEED = 1.0;

float moving_disk_x;
float moving_disk_y;
float moving_disk_w;
float moving_disk_h = 5;

float disks[NUM_DISKS][4][2];
vector< deque< int > > rods(NUM_RODS);

int from_rod = -1;
int to_rod = -1;
int dir = 0; // 0 -> up ,     1 -> left or right   2 -> down
int steps = 0;

/*void init()
{

}
*/
// float x = 2 , y = 5;

void buildDisks() {
    for(int i = 0 ; i < NUM_DISKS; i++)
    {
        disks[i][0][0] = 20 + i * 2, disks[i][0][1] = 25;
        disks[i][1][0] = 20 + i * 2, disks[i][1][1] = 30;
        disks[i][2][0] = 40 - i * 2, disks[i][2][1] = 30;
        disks[i][3][0] = 40 - i * 2, disks[i][3][1] = 25;
        rods[0].push_back(i);
    }
}
bool music = 1, disable = 1;
void ss(int) {
     music = 1;
}



int main(int argc , char**argv)
{
    glutInit(&argc ,argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

    glutInitWindowPosition(200,100);
    glutInitWindowSize(600,600);

    glutCreateWindow("Tower Of Hanoi");
    buildDisks();
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    init();
    glutMainLoop();
}

float x_pos_rod = 27.5;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    if(music) {
        //  sndPlaySound("aa.wav", SND_ASYNC);
         music = 0;
         disable = 1;
    } else if(disable) {
        glutTimerFunc(60400 , ss, 0);
        disable = 0;
    }

    glColor3f(0.078f, 0.1176f, 0.341f);
    quads(0.0,0.0,0.0,15.0,100.0,15.0,100.0,0.0);
    glColor3f(0.3250f, 0.403f, 0.992f);
    quads(0.0,15.0,0.0,100.0,100.0,100.0,100.0,15.0);

    glBegin(GL_QUADS);
        // Board
        glColor3f(0.5, 0.5, 0.5);
        glVertex2f(15.0, 15.0);
        glVertex2f(15.0, 25.0);
        glVertex2f(80.0, 15.0);
        glVertex2f(80.0, 25.0);

        // 3 Rods
        glColor3f(1.0, 1.0, 0.0);
        for (int i = 0; i < 3; i++) {
            glVertex2f(x_pos_rod + 20 * i + 1, 25.0);
            glVertex2f(x_pos_rod + 5 + 20 * i - 1, 25.0);
            glVertex2f(x_pos_rod + 5 + 20 * i - 1, 60.0);
            glVertex2f(x_pos_rod + 20 * i + 1, 60.0);
        }

        // colors;
        float r[] = {1, 1, 0, 1};
        float g[] = {0, 1, 1, 0};
        float b[] = {0, 1, 0.5, 1};

        // Disks
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < int(rods[i].size()) - (moving && from_rod == i); j++) {
                glColor3f(r[rods[i][j]], g[rods[i][j]], b[rods[i][j]]);
                for (int k = 0; k < 4; k++) {
                    glVertex2f(disks[rods[i][j]][k][0] + i * 20, disks[rods[i][j]][k][1] + 5 * j);
                }
            }
        }
        if (moving) {
            glColor3f(r[rods[from_rod].back()], g[rods[from_rod].back()], b[rods[from_rod].back()]);
            glVertex2f(moving_disk_x, moving_disk_y);
            glVertex2f(moving_disk_x, moving_disk_y + moving_disk_h);
            glVertex2f(moving_disk_x + moving_disk_w, moving_disk_y + moving_disk_h);
            glVertex2f(moving_disk_x + moving_disk_w, moving_disk_y);
        }

    glEnd();

    glFlush();
    glutSwapBuffers();
}
void reshape(int w , int h)
{

    glViewport(0,0,(GLsizei)w,(GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,100,0,100);
    glMatrixMode(GL_MODELVIEW);
}

void timer(int )
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0); // 60 FPS

    if (moving)
    {
        switch (dir) {
            case 0:
                moving_disk_y += SPEED;
                if (moving_disk_y >= 65) dir = 1;
                break;
            case 1:
                if (to_rod < from_rod)
                    moving_disk_x -= SPEED;
                else
                    moving_disk_x += SPEED;
                if (moving_disk_x == disks[rods[from_rod].back()][0][0] + 20 * to_rod) dir = 2;
                break;
            case 2:
                moving_disk_y -= SPEED;
                if (moving_disk_y == disks[rods[from_rod].back()][0][1] + 5 * int(rods[to_rod].size())) {
                    moving = false;
                    rods[to_rod].push_back(rods[from_rod].back());
                    rods[from_rod].pop_back();
                    from_rod = -1;
                    to_rod = -1;
                    dir = 0;
                }
                break;
        }
    }
    gameover = (rods[2].size() == NUM_DISKS);
    if (gameover) {
        string smsg = "Number of Steps: " + to_string(steps);
        // LPTSTR msg = new TCHAR[smsg.size() + 1];
        // strcpy(msg, smsg.c_str());
        // MessageBox(NULL, msg, "GOOD JOB!", MB_ICONASTERISK | MB_OK);
        exit(0);
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
        case '1':
        case '2':
        case '3':
            if (moving) break;
            if (~from_rod) {
                to_rod = key - '1';
                 if (rods[to_rod].empty() || rods[to_rod].back() < rods[from_rod].back()) {
                    moving = true;
                    moving_disk_x = disks[rods[from_rod].back()][0][0] + from_rod * 20;
                    moving_disk_y = disks[rods[from_rod].back()][0][1] + (rods[from_rod].size() - 1) * 5;
                    moving_disk_w = disks[rods[from_rod].back()][3][0] - disks[rods[from_rod].back()][0][0];
                    steps++;
                }
                else {
                    from_rod = to_rod = -1;
                }
            }
            else {
                if (!rods[key - '1'].empty()) {
                    from_rod = key - '1';
                }
            }
            break;
        case 'q':
        case 'Q':
            exit(0);
            break;
    }

}
