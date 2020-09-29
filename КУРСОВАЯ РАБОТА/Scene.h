#pragma once
#include "Checkers.h"
#include "BoardBox.h"
#define _CRT_SECURE_NO_WARNINGS
extern double 	angleX;
extern double angleY;
class Scene
{
public:
	int button;
	Scene(int w, int h);
	BoardBox* getBox();
	void renderScene();
	void drawScene();
	void setheight(int);
	void setwidth(int);
	void activizationCheckers(Checkers* checkers);
	void resetActivizationCheckers(Checkers* checkers);
	void activizationNeigbords(BoardBox* box, int move);
	void resetActivizationBox(BoardBox* box);
	void moveCheckers(BoardBox* FirstBox, BoardBox* SecondBox, int& move);
	bool killCheckers(BoardBox*, BoardBox*, int&);
	bool CanKill(BoardBox*,int);
	bool WhoCanKill(BoardBox* box, int move);
	bool findCheckers(int x, int y, int& number, BoardBox* box, int move);
	bool findBox(int x, int y, int& number, BoardBox* box, BoardBox* activeBox, int move);
	bool findFarBox(int x, int y, int& number, BoardBox* box, BoardBox* activeBox, int move);
	void MyMouse(int button, int state, int x, int y);
	void on_motion(int x, int y);
	void keyboard(unsigned char key, int x, int y);
	bool GameOver();
	double mouseX, mouseY;
	void initializationScene(int w,int h);
	void on_special(int key, int x, int y);
	void on_timer(int value);
private:
	double  zMe;
	BoardBox* box;
	int height, width;
	int angleX, angleY;
	Checkers* activeCheckers;
	BoardBox* activeBox;
	double activizationColor[3] = { 0.6,0.6,0.1 };
	double colorresetRED[3] = { 0.8,0.0,0.0 };
	double colorresetBLUE[3] = { 0.0,0.0,0.6 };
	double colorresetBlack[3] = { 0.1,0.1,0.1 };
	int move;
	int REDCHECKERS, BLUECHECHERS;
	int time;
	char text[256];
	char text1[256];
	char gameovertext[256];
	int tick;
	int alltime;
	int gamecount;
};
