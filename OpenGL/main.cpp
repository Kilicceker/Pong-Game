
#include <GL/freeglut_std.h>
#include <GL/freeglut.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <iostream>

#define WINDOW_W 800
#define WINDOW_H 500
static int player_one = 0;
static int player_two = 0;
static GLfloat left_1 = -49.5;
static GLfloat left2 = 48.5;

static GLfloat top_1 = 7.0;
static GLfloat top_2 = 7.0;

static GLfloat bottom_1 = -7.0;
static GLfloat bottom_2 = -7.0;

static GLfloat right_1 = -48.5;
static GLfloat right_2 = 49.5;


static GLfloat moveXFactor = 0.2;
static GLfloat moveYFactor = 0.1;
static const int FPS = 60;

struct _ball
{
	GLfloat radius = 1.5;
	GLfloat X = 0.0;
	GLfloat Y = 0.0;
	float directionX = 0.5;
	float directionY = 0.5;
}ball;

void drawString(float x, float y, float z, const char* string) {
	glRasterPos3f(x, y, z);

	for (const char* c = string; *c != '\0'; c++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *c);  // Updates the position
	}
}
void reshape(GLint w, GLint h)
{
	glViewport(0, 0, w, h);
	GLfloat aspect = (GLfloat)w / (GLfloat)h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -50.0 / aspect, 50.0 / aspect, -1.0, 1.0);
}

void draw_circle(float x, float y, float radius) {
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(x, y, 0.0f);
	static const int circle_points = 100;
	static const float angle = 2.0f * 3.1416f / circle_points;

	// this code (mostly) copied from question:
	glBegin(GL_POLYGON);
	double angle1 = 0.0;
	glVertex2d(radius * cos(0.0), radius * sin(0.0));
	int i;
	for (i = 0; i < circle_points; i++)
	{
		glVertex2d(radius * cos(angle1), radius * sin(angle1));
		angle1 += angle;
	}
	glEnd();
	glPopMatrix();
}
void display2() {
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	drawString(-40.0, 27.0, 0.0, "Player One is winner");
	glFlush();
	glutSwapBuffers();
}
void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if  (player_two!=5 && player_one!=5) {
	glRectf(left_1, top_1, right_1, bottom_1);
	glRectf(left2, top_2, right_2, bottom_2);
	draw_circle(ball.X, ball.Y, ball.radius);
	std::string playerone = std::to_string(player_one);
	std::string playertwo = std::to_string(player_two);
	char const* pchar = playerone.c_str();
	char const* pchartwo = playertwo.c_str();
	drawString(-40.0, 27.0, 0.0, "Player One - ");
	drawString(-23.0, 27.0, 0.0, pchar);
	drawString(17, 27.0, 0.0, "Player Two - ");
	drawString(34.0, 27.0, 0.0, pchartwo);
	}
	
	else if (player_one == 5) {
		drawString(-10.0, 0.0, 0.0, "Winner Player One ");
	}
	else if(player_two==5)
	{ drawString(-10.0, 0.0, 0.0, "Winner Player Two "); }
	glFlush();
	glutSwapBuffers();
}

void timer(int v)
{

	
	draw_circle(ball.X, ball.Y, ball.radius);
	if (ball.X<50 && ball.Y<31 && ball.X > -50 && ball.Y > -31) {

		ball.Y += ball.directionY;
		ball.X -=  ball.directionX;
		draw_circle(ball.X, ball.Y, ball.radius);
	}
	if (ball.Y <= -30) {
		ball.directionY *= -1;
		
	}
	if (ball.Y >= 30) {
		ball.directionY *= -1;

	}
	if (ball.X -ball.radius ==right_1 && ball.Y<top_1 && ball.Y>bottom_1) {

		ball.directionX *= -1;
	}
	if (ball.X+ ball.radius == right_2 && ball.Y<top_2 && ball.Y>bottom_2) {

		ball.directionX *= -1;
	}
	if (ball.X-ball.radius<=-50) {

		ball.X = 0;
		ball.Y = 0;
		ball.directionX *= -1;
		left_1 = -49.5;
		left2 = 48.5;

		top_1 = 7.0;
		top_2 = 7.0;

		bottom_1 = -7.0;
		bottom_2 = -7.0;

		right_1 = -48.5;
		right_2 = 49.5;
		player_two += 1;

	}
	if (ball.X + ball.radius >= 50) {

		ball.X = 0;
		ball.Y = 0;
		ball.directionX *= -1;
		left_1 = -49.5;
		left2 = 48.5;

		top_1 = 7.0;
		top_2 = 7.0;

		bottom_1 = -7.0;
		bottom_2 = -7.0;

		right_1 = -48.5;
		right_2 = 49.5;
		player_one += 1;

	}

	
	glutPostRedisplay();

	glutTimerFunc(1500/ FPS, timer, v);
}



 


void keyboardFunc(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		if (top_1+ 0.8 < 31.0)
		{
			top_1 = top_1 + 1;
			bottom_1 = bottom_1 + 1;
			
		}
		break;
	case 'W':
		if (top_1 < 31)
		{
			top_1 = top_1 + 1;
			bottom_1 = bottom_1 + 1;
		}
		break;
	case 's':
		if (bottom_1 > -31)
		{
			top_1 = top_1 - 1;
			bottom_1 = bottom_1 - 1;
			
		}
		break;
	case 'S':
		if (bottom_1 > -31)
		{
			top_1 = top_1 - 1;
			bottom_1 = bottom_1 - 1;

		}
		break;
	case 'O':
		if (top_2 < 31)
		{
			top_2 = top_2 + 1;
			bottom_2 = bottom_2 + 1;
		}
		break;
	case 'o':
		if (top_2 < 31)
		{
			top_2 = top_2 + 1;
			bottom_2 = bottom_2 + 1;
		}
		break;
	case 'l':
		if (bottom_2 > -31)
		{
			top_2 = top_2 - 1;
			bottom_2 = bottom_2 - 1;

		}
		break;
	case 'L':
		if (bottom_2 > -31)
		{
			top_2 = top_2 - 1;
			bottom_2 = bottom_2 - 1;

		}
		break;
	}
	}





int main(int argc, char** argv)
{
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(260, 140);
	glutInitWindowSize(WINDOW_W, WINDOW_H);
	glutCreateWindow("Pong Game");
	glutReshapeFunc(reshape);
	
	glutDisplayFunc(display);
	glutTimerFunc(100, timer, 0);
	
	
	glutKeyboardFunc(keyboardFunc);
	glutMainLoop();
}