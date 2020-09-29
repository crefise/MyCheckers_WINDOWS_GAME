#pragma once
class Checkers
{
public:
	Checkers(double xCenter, double yCenter, char colorCheckers, double color[]);
	void drawCheckers();
	double getxCenter();
	double getyCenter();
	void setxCenter(double);
	void setyCenter(double);
	void setcolor(double[]);
	char getcolorCheckers();
	bool isLedy();
	void setLedy(bool);
private:
	char colorCheckers;
	double xCenter, yCenter;
	double color[3];
	bool ledy;

};

