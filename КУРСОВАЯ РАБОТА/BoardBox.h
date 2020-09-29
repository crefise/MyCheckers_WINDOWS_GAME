#pragma once
#include "Checkers.h"
class BoardBox
{
public:
	BoardBox(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4, double xCenter, double yCenter, bool checkersIs, char colorChecker);
	void drawBoardBox();
	Checkers* getCheckers();
	bool getcheckersIs();
	BoardBox* getleftBoxForRed();
	BoardBox* getrightBoxForRed();
	BoardBox* getleftBoxForBlue();
	BoardBox* getrightBoxForBlue();
	void setleftBoxForRed(BoardBox*);
	void setrightBoxForRed(BoardBox*);
	void setleftBoxForBlue(BoardBox*);
	void setrightBoxForBlue(BoardBox*);
	void setcolor(double[]);
	double getx1();
	double getx2();
	double getx3();
	double getx4();
	double gety1();
	double gety2();
	double gety3();
	double gety4();
	void setCheckers(Checkers*);
	void setCheckersIs(bool);
	double getxCenter();
	double getyCenter();
	void removeCheckers();
private:
	Checkers* checkers;
	bool checkersIs;
	double x1, x2, x3, x4, y1, y2, y3, y4;
	double xCenter, yCenter;
	BoardBox* leftBoxForRed;
	BoardBox* rightBoxForRed;
	BoardBox* leftBoxForBlue;
	BoardBox* rightBoxForBlue;
	double color[3];
};

