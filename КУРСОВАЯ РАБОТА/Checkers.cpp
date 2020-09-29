#include "Checkers.h"
#include <gl/freeglut.h>
#include "HelpFunction.h"



Checkers::Checkers(double xCenter, double yCenter, char colorCheckers, double color[]) {
	this->xCenter = xCenter;
	this->yCenter = yCenter;
	this->colorCheckers = colorCheckers;
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
	this->ledy = false;
}
void Checkers::drawCheckers() {
	glColor3f(color[0], color[1], color[2]);
	GLUquadricObj* quadObj;
	quadObj = gluNewQuadric();
	glPushMatrix();
	gluQuadricDrawStyle(quadObj, GLU_FILL);
	glTranslated(xCenter, yCenter, 0.0);
	
	if (this->ledy)
	{
		gluCylinder(quadObj, 0.1, 0.1, 0.04, 100, 100);
		gluCylinder(quadObj, 0.0, 0.1, 0.04, 100, 100);
		glTranslated(0, 0, 0.03);
		if (colorCheckers == 'r')
		{
			glColor3f(0.3, color[1], color[2]);
		}
		else {
			glColor3f(color[0], color[1], 0.3);
		}
		gluCylinder(quadObj, 0.00, 0.1, 0.001, 100, 100);
	}
	else {
		gluCylinder(quadObj, 0.1, 0.1, 0.04, 100, 100);
		gluCylinder(quadObj, 0.0 , 0.1, 0.04, 100, 100);
		glTranslated(0, 0, 0.01);
		gluCylinder(quadObj, 0.08, 0.00, 0.001, 100, 100);
	}
	glPopMatrix();
	gluDeleteQuadric(quadObj);
	glColor3f(1.0, 1.0, 1.0);


}
double Checkers::getxCenter() {
	return xCenter;
}
double Checkers::getyCenter() {
	return yCenter;
}
void Checkers::setxCenter(double xCenter) {
	this->xCenter = xCenter;
}
void Checkers::setyCenter(double yCenter) {
	this->yCenter = yCenter;
}
void Checkers::setcolor(double color[]) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
char Checkers::getcolorCheckers() {
	return colorCheckers;
}

bool Checkers::isLedy() {
	return this->ledy;
}
void Checkers::setLedy(bool ledy) {
	this->ledy = ledy;
}