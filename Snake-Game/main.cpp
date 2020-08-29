#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

#include <string.h>
#include <iostream>
#include <sstream>

#include "SnakeModel.h"
#include "Snake.h"

using namespace std;

void display(),setup();
void reshapeCallback(int,int),timer(int);
void keyboardCallback(int,int,int), mouseCallback(int,int,int,int);
void text();

bool PAUSED=false;

Snake snake;


int main(int argc, char**argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA);
	glutInitWindowPosition(50,50);
	glutInitWindowSize(CELLWIDTH*COLUMNS,CELLWIDTH*ROWS);
	glutCreateWindow("Realistic Snake Gait Game");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshapeCallback);
	glutTimerFunc(0,timer,0);
	glutSpecialFunc(keyboardCallback);
	glutMouseFunc(mouseCallback);
	
	setup();
	glutMainLoop();
	
	return 0;
}

void reshapeCallback(int w, int h)
{
	glViewport(0,0,(GLsizei)w,(GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glOrtho(-1*LIMIT-MARGIN,LIMIT+MARGIN,-1*LIMIT-MARGIN,LIMIT+MARGIN,-1.0,1.0);
	glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
	glutPostRedisplay();
	glutTimerFunc(1000/FPS,timer,0);
}

void keyboardCallback(int key,int,int)
{
	if(key==GLUT_KEY_RIGHT)
	{
		snake.dir = RIGHT;
		PAUSED = false;
	} 
	else if (key==GLUT_KEY_LEFT)
	{
		snake.dir = LEFT;
		PAUSED = false;
	}
	else if(key==GLUT_KEY_UP)
	{
		snake.dir = FORWARD;
		PAUSED = false;
	}
	else snake.dir = FORWARD;
	
}

void mouseCallback(int button,int state, int x, int y)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		PAUSED=!PAUSED;
	}
	
}

void text()
{
	char message[80];
	
	stringstream str;
	str<< snake.score;
	string temp_str = str.str();
	char * score = (char*) temp_str.c_str();
	
	strcpy(message,"score: ");
	strcat(message,score);
	
	glColor4f(1,1,1,1);
	glRasterPos2d(LIMIT-25, LIMIT-10);
	
	int len=strlen(message);


	for ( int i = 0; i < len; ++i )
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
	}
	
	
	if(snake.collided())
	{
		strcpy(message,"Game Over !! :(");
		len=strlen(message);
		glColor4f(1,1,1,1);
		glRasterPos2d(-15, 0);


		for ( int i = 0; i < len; ++i )
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, message[i]);
		}
	}
}


void setup()
{
	glClearColor(0.0,0.0,0.0,1.0);
	glEnable(GL_BLEND);
	glEnable( GL_POINT_SMOOTH );
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	drawEnv();
	if(!PAUSED && !snake.collided()) snake.update();
	snake.draw();
	text();
	glFlush();
}

