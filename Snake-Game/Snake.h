#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED


#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "SnakeModel.h"



using namespace std;

class Snake
{
	public:
	
		int N;
		double r[200][2];
		double th[200];
		double dir;
		
		// Constructor
		Snake()
		{
			N = 40;
			a = n;
			n = 40;
			l = 2;
			r[1][0]= 0;
			r[1][1]=-40;
			dir = 0;
			
			getRandApple();
			blink=0;
			
			for(int i=0;i<N;i++)
			{
				th[i] = gait(i);
				
			}
			
			th[0]=PI/8;
			score = 0;
		}
		
		bool collided();
		void draw();
		void update();
		int score;
		
		
	private:
		int a;
		int n;
		int blink;
		double headX;
		double headY;
		double headTH;
		void head();
		double l;	
		double gait(int i);
		double width(int i);
		double addTh(int i, int j);
		
		void Apple();
		void getRandApple();
		double AppX;
		double AppY;
}; 

// Checks Collision with walls
bool Snake::collided()
{
	if(headX<-1*LIMIT || headX>LIMIT || headY<-1*LIMIT || headY>LIMIT)
	{
		return true;
	}else return false;
	
}

// Snake Gait Input Funtion 
double Snake::gait(int i)
{
	i = i%(n+1);    
	return 4.5*PI/n*sin(4*PI/(n+1)*i)+dir;
}

// Shape of the Snake Body
double Snake::width(int i)  
{
	double a = 1.5;
	double b = 0.004-0.003/15.0*(N-65);
	double t = N*2.0/3.0;
	return a*exp(-1*b*pow(i-t,2));
}

// Shape of the Snake head
void Snake::head()
{
	//glColor4f(1.0,0.0,0.0,1.0);
	glLineWidth(2);
	
	double a = 2;
	
	glTranslatef(headX,headY,0);
	glRotatef(180/PI*headTH,0,0,1); 
	glBegin(GL_POLYGON);
		glVertex2d(-1,0.3*a);
		glVertex2d(0,0.6*a);
		glVertex2d(0.5,0.8*a);
		glVertex2d(2,0.6*a);
		glVertex2d(4,0.1*a);
		glVertex2d(4.5,0.3);
		glVertex2d(4.5,-0.3);
		glVertex2d(4,-0.1*a);
		glVertex2d(2,-0.6*a);
		glVertex2d(0.5,-0.8*a);
		glVertex2d(0,-0.6*a);
		glVertex2d(-1,-0.7*a);
	glEnd();
    
	glLoadIdentity();

}


// From Kinematical Model of the Snake
void Snake::update()
{	
	r[0][0] = r[1][0];
	r[0][1] = r[1][1];
	
	a=(a+1)%(n+1);
	th[0]+=th[1];
	
	for(int i=1;i<N-1;i++)
	{
		th[i]=th[i+1];
	}
	
	th[N-1]=gait(a);
	
	headX = r[N-1][0];
	headY = r[N-1][1];
	headTH = addTh(0,N-1);		
}


double Snake::addTh(int i, int j){

	double sum=0;
	for(int index=i;index<=j;index++){
		sum+=th[index];
	}
	
	return sum;
}


void Snake::draw()
{
	// Mathematical Constraint Equation
	for(int i=1;i<N;i++)
	{
		double tempX=0;
		double tempY=0;
		for(int j=0;j<i;j++)
		{
			tempX+=l*cos(addTh(0,j));
			tempY+=l*sin(addTh(0,j));	
		}
		
		r[i][0]=r[0][0]+tempX;
		r[i][1]=r[0][1]+tempY;
	}
	
	for(int i=1; i<N-1; i++){

		
		
		double x1=r[i][0],x2=r[i+1][0];
		double y1=r[i][1],y2=r[i+1][1];
		double w = width(i)/2;
		double v[2]={x2-x1,y2-y1};
		double pv[2]={-v[1],v[0]};
		
		glColor4f(0.0,0.8,0.1,0.8);
		
		glBegin(GL_POLYGON);
			glVertex2d(x1+w*pv[0],y1+w*pv[1]);
			glVertex2d(x2+w*pv[0],y2+w*pv[1]);
			glVertex2d(x2-w*pv[0],y2-w*pv[1]);
			glVertex2d(x1-w*pv[0],y1-w*pv[1]);
		glEnd();
		
		glColor4f(0.0,0.9,0.3,0.5);
		
		glBegin(GL_LINE_LOOP);
			glVertex2d(x1+w*pv[0],y1+w*pv[1]);
			glVertex2d(x2+w*pv[0],y2+w*pv[1]);
			glVertex2d(x2-w*pv[0],y2-w*pv[1]);
			glVertex2d(x1-w*pv[0],y1-w*pv[1]);
		glEnd();

    }
    
 
    for(int i=N-2; i>N/4; i--){

		glLineWidth(3);
		glColor4f(0.0,1.0,0.0,0.8);
     
		glBegin(GL_LINES);
			glVertex2d(r[i][0],r[i][1]);
			glVertex2d(r[i+1][0],r[i+1][1]);
		glEnd();
    }
 
    
    head();
    Apple();
}

void Snake::Apple()
{	
	blink=(blink+1)%FPS;
	
	if(pow(headX-AppX,2)+pow(headY-AppY,2)<15)
	{
		getRandApple();
		score++;
		
	// Incrementing snake length
		N+=2;
		headX = r[N-1][0];
		headY = r[N-1][1];
		headTH = addTh(0,N-1);
	}
	
	if(blink < FPS/2){
	
		glColor4f(0.9,0.0,0.0,0.9);
		glPointSize(20);
		glBegin(GL_POINTS);
			glVertex2d(AppX,AppY);
		glEnd();
	}
	
}

void Snake::getRandApple()
{
	srand(time(NULL));
	
	int hlim = LIMIT-GRIDWIDTH*2;
	int llim = -1*LIMIT+GRIDWIDTH*2; 
	
	AppX = rand()%(hlim-llim)+llim;
	AppY = rand()%(hlim-llim)+llim;
}

#endif
