
#include "peintre.h"
#include <GL/gl.h>
#include <math.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

void Peintre::snakeBox(int x1, int y1, int x2, int y2)	//Yılanı oluşturan kutuların çizilmesini sağlayan fonksiyon.
{
  glColor3f(1.0,0.0,0.0);
  glBegin(GL_QUADS);
  glVertex2d(x1, y1);
  glVertex2d(x2, y1);
  glVertex2d(x2, y2);
  glVertex2d(x1, y2);
  glEnd();
}

void Peintre::obstacleBox(int x1, int y1, int x2, int y2) //Engellerin çizilmesini sağlayan fonksiyon.
{
  glColor3f(255.0,255.0,255.0);
  glBegin(GL_QUADS);
  glVertex2d(x1, y1);
  glVertex2d(x2, y1);
  glVertex2d(x2, y2);
  glVertex2d(x1, y2);
  glEnd();
}

void Peintre::foodBox(int x1, int y1, int x2, int y2)	//Yiyeceklerin çizilmesini sağlayan fonksiyon.
{
  	glColor3f(1.0, 1.0, 0.0);
	glBegin(GL_QUADS);
	glVertex2d(x1, y1);
	glVertex2d(x2, y1);
	glVertex2d(x2, y2);
	glVertex2d(x1, y2);
	glEnd();

}


