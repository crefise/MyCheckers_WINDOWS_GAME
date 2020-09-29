#include "BoardBox.h"
#include <gl/glut.h>
#include "HelpFunction.h"
double colorRED[3] = { 0.8,0.0,0.0 };
double colorBLUE[3] = { 0.0,0.0,0.6 };
BoardBox::BoardBox(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, double xCenter, double yCenter, bool checkersIs, char colorCheckers) {
	checkers = NULL;
	this->x1 = x1;
	this->x2 = x2;
	this->x3 = x3;
	this->x4 = x4;

	this->y1 = y1;
	this->y2 = y2;
	this->y3 = y3;
	this->y4 = y4;

	this->color[0] = 0.1;
	this->color[1] = 0.1;
	this->color[2] = 0.1;

	this->xCenter = xCenter;
	this->yCenter = yCenter;

	this->checkersIs = checkersIs;
	if (this->checkersIs == true)
	{
		if (colorCheckers == 'r')
			this->checkers = new Checkers(xCenter, yCenter, colorCheckers, colorRED);
		else
			this->checkers = new Checkers(xCenter, yCenter, colorCheckers, colorBLUE);
	}


}
void  BoardBox::drawBoardBox() {
	glColor3f(color[0], color[1], color[2]);
	glBegin(GL_QUADS);
	glVertex3f(x1, y2, 0.002);
	glVertex3f(x2, y2, 0.002);
	glVertex3f(x3, y3, 0.002);
	glVertex3f(x4, y4, 0.002);
	glEnd();
	if (checkersIs == true)
	{
		checkers->drawCheckers();
	}
}
Checkers* BoardBox::getCheckers() {
	return this->checkers;
}
bool BoardBox::getcheckersIs() {
	return this->checkersIs;
}
void BoardBox::setleftBoxForRed(BoardBox* leftBoxForRed) {
	this->leftBoxForRed = leftBoxForRed;
}
void BoardBox::setrightBoxForRed(BoardBox* rightBoxForRed) {
	this->rightBoxForRed = rightBoxForRed;
}
void BoardBox::setleftBoxForBlue(BoardBox* leftBoxForBlue) {
	this->leftBoxForBlue = leftBoxForBlue;
}
void BoardBox::setrightBoxForBlue(BoardBox* rightBoxForBlue) {
	this->rightBoxForBlue = rightBoxForBlue;
}
BoardBox* BoardBox::getleftBoxForRed() {
	return leftBoxForRed;
}
BoardBox* BoardBox::getrightBoxForRed() {
	return rightBoxForRed;
}
BoardBox* BoardBox::getleftBoxForBlue() {
	return leftBoxForBlue;
}
BoardBox* BoardBox::getrightBoxForBlue() {
	return rightBoxForBlue;
}
void BoardBox::setcolor(double color[]) {
	this->color[0] = color[0];
	this->color[1] = color[1];
	this->color[2] = color[2];
}
double BoardBox::getx1() { return x1; }
double BoardBox::getx2() { return x2; }
double BoardBox::getx3() { return x3; }
double BoardBox::getx4() { return x4; }
double BoardBox::gety1() { return y1; }
double BoardBox::gety2() { return y2; }
double BoardBox::gety3() { return y3; }
double BoardBox::gety4() { return y4; }
void BoardBox::setCheckers(Checkers* checkers) {
	this->checkers = checkers;
}
void BoardBox::setCheckersIs(bool is) {
	checkersIs = is;
}
double BoardBox::getxCenter() {
	return xCenter;
}
double BoardBox::getyCenter() {
	return yCenter;
}
void BoardBox::removeCheckers() {
	delete[]this->checkers;
	this->checkersIs = false;
}