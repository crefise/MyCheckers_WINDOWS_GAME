#include "Scene.h"
#include <gl/glut.h>
#include <iostream>
#include "HelpFunction.h"
#include <time.h>
#include <fstream>
#include <string>

void Scene::renderScene() 
{
	//glOrtho(-12, 1, -1, 1, -1, 1);
	if (GameOver()) {
		if (BLUECHECHERS == 0)
			sprintf(this->text, "Game over. WINNER RED Time: %d sec.   F2 - Restart game   Esc - Exit", time);
		else
			sprintf(this->text, "Game over. WINNER BLUE Time: %d sec.   F2 - Restart game   Esc - Exit", time);

	}
	else {
		sprintf(this->text, "F2 - Restart game   Esc - Exit              Time: %d sec.", time);
	}
	sprintf(this->text1, "Game count : %d", this->gamecount);


	glViewport(1, 1, width, height);
	if (GameOver()) {
		if(BLUECHECHERS==0)
			glClearColor(0.2, 0, 0, 1);
		else
			glClearColor(0, 0, 0.2, 1);
	}
	else {
		glClearColor(0, 0.5, 0.5, 0);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1, 0, 1, -1, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (GameOver()) {
		if (BLUECHECHERS == 0) {
			glColor3f(1.0, 0.0, 0.0);
		}
		else {
			glColor3f(0.0, 0.0, 1.0);
		}
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
	}
	else {
		glColor3f(0, 1, 0);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, text, 0.01, 0.95);
	}
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, text1, 0.01, 0.05);
	glPopMatrix();


	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(-1,1,-1,1,-1,1);
	gluPerspective(60, width / height, 1, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//glOrtho(-1, 1, -1, 1, -1, 1);
	glTranslatef(0, 0, zMe);	 
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(angleY, 1.0f, 0.0f, 0.0f); 
	glEnable(GL_DEPTH_TEST);
	drawScene();
	glFlush();
	glutSwapBuffers();

}
Scene::Scene(int w, int h) {
	initializationScene(w, h);
}
void Scene::drawScene() {
	// Встановлюємо параметри джерела світла:
	double w = width;
	double h = height;
	glColor3f(0.3, 0.2, 0.1); //Доска в общем
	if (GameOver()) {
		if (BLUECHECHERS == 0)
			glColor3f(0.9, 0, 0);
		else
			glColor3f(0, 0, 0.9);
	}
	else {
		glColor3f(0.3, 0.2, 0.1);
	}
	glBegin(GL_QUADS);
	glVertex3f(-1.0, -1.0, 0.000000);
	glVertex3f(1.0, -1.0, 0.000000);
	glVertex3f(1.0, 1.0, 0.000000);
	glVertex3f(-1.0, 1.0, 0.000000);
	glEnd();
	glColor3f(0.3, 0.4, 0.3); //Левая грань
	glBegin(GL_QUADS);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, -1.0, 0.0);
	glVertex3f(-1.0, -1.0, -0.2);
	glVertex3f(-1.0, 1.0, -0.2);
	glEnd();


	glBegin(GL_QUADS);//верхняя грань
	glVertex3f(1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, 0.0);
	glVertex3f(-1.0, 1.0, -0.2);
	glVertex3f(1.0, 1.0, -0.2);
	glEnd();

	glBegin(GL_QUADS);//правая грань
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, 1.0, 0.0);
	glVertex3d(1.0, 1.0, -0.2);
	glVertex3d(1.0, -1.0, -0.2);
	glEnd();

	glBegin(GL_QUADS); //передная грань
	glVertex3d(-1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, 0.0);
	glVertex3d(1.0, -1.0, -0.2);
	glVertex3d(-1.0, -1.0, -0.2);
	glEnd();


	glBegin(GL_QUADS);
	glVertex3f(-1., -1.0, -0.200000);
	glVertex3f(1.0, -1.0, -0.200000);
	glVertex3f(1.0, 1.0, -0.200000);
	glVertex3f(-1.0, 1.0, -0.200000);
	glEnd();


	glColor3f(0.8, 0.8, 0.8); //Внутренная часть доски
	glBegin(GL_QUADS);
	glVertex3f(-0.8, -0.8, 0.001);
	glVertex3f(0.8, -0.8, 0.001);
	glVertex3f(0.8, 0.8, 0.001);
	glVertex3f(-0.8, 0.8, 0.001);
	glEnd();

	
	for (int i = 0; i < 32; i++)
	{
		this->box[i].drawBoardBox();
	}
}
BoardBox* Scene::getBox() {
	return this->box;
}
void Scene::setheight(int height) {
	this->height = height;
}
void Scene::setwidth(int width) {
	this->width = width;
}
void Scene::activizationCheckers(Checkers* checkers) {
	checkers->setcolor(activizationColor);
	checkers->drawCheckers();
}
void Scene::resetActivizationCheckers(Checkers* checkers) {
	if (checkers->getcolorCheckers() == 'r')
		checkers->setcolor(colorresetRED);
	else
		checkers->setcolor(colorresetBLUE);
	checkers->drawCheckers();
}
void Scene::activizationNeigbords(BoardBox* box, int move) {
	int anticolor;
	if (move == 1)
		anticolor = 'b';
	else
		anticolor = 'r';
	if (CanKill(box,move)&&box->getcheckersIs()&&!box->getCheckers()->isLedy()) {
		if (box->getleftBoxForRed() != NULL && box->getleftBoxForRed()->getleftBoxForRed() != NULL && box->getleftBoxForRed()->getcheckersIs() && !box->getleftBoxForRed()->getleftBoxForRed()->getcheckersIs() && box->getleftBoxForRed()->getCheckers()->getcolorCheckers() == anticolor&&move==1)
		{
			box->getleftBoxForRed()->getleftBoxForRed()->setcolor(activizationColor);
			box->getleftBoxForRed()->getleftBoxForRed()->drawBoardBox();
		}
		if (box->getrightBoxForRed() != NULL && box->getrightBoxForRed()->getrightBoxForRed() != NULL && box->getrightBoxForRed()->getcheckersIs() && !box->getrightBoxForRed()->getrightBoxForRed()->getcheckersIs() && box->getrightBoxForRed()->getCheckers()->getcolorCheckers() == anticolor&&move==1)
		{
			box->getrightBoxForRed()->getrightBoxForRed()->setcolor(activizationColor);
			box->getrightBoxForRed()->getrightBoxForRed()->drawBoardBox();
		}
		if (box->getleftBoxForBlue() != NULL && box->getleftBoxForBlue()->getleftBoxForBlue() != NULL && box->getleftBoxForBlue()->getcheckersIs() && !box->getleftBoxForBlue()->getleftBoxForBlue()->getcheckersIs() && box->getleftBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor&&move==-1)
		{
			box->getleftBoxForBlue()->getleftBoxForBlue()->setcolor(activizationColor);
			box->getleftBoxForBlue()->getleftBoxForBlue()->drawBoardBox();
		}
		if (box->getrightBoxForBlue() != NULL && box->getrightBoxForBlue()->getrightBoxForBlue() != NULL && box->getrightBoxForBlue()->getcheckersIs() && !box->getrightBoxForBlue()->getrightBoxForBlue()->getcheckersIs() && box->getrightBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor&&move==-1)
		{
			box->getrightBoxForBlue()->getrightBoxForBlue()->setcolor(activizationColor);
			box->getrightBoxForBlue()->getrightBoxForBlue()->drawBoardBox();
		}
	}
	if(!CanKill(box,move) && box->getcheckersIs() && !box->getCheckers()->isLedy())
	{
		if (move == 1&&(activeBox->getCheckers()->getcolorCheckers()=='r')) {
			if (box->getleftBoxForRed() != NULL && !box->getleftBoxForRed()->getcheckersIs()) {
				box->getleftBoxForRed()->setcolor(activizationColor);
				box->getleftBoxForRed()->drawBoardBox();
			}
			if (box->getrightBoxForRed() != NULL && !box->getrightBoxForRed()->getcheckersIs()) {
				box->getrightBoxForRed()->setcolor(activizationColor);
				box->getrightBoxForRed()->drawBoardBox();
			}
		}
		if(move ==-1 && (activeBox->getCheckers()->getcolorCheckers() == 'b' )) {
			if (box->getleftBoxForBlue() != NULL && !box->getleftBoxForBlue()->getcheckersIs()) {
				box->getleftBoxForBlue()->setcolor(activizationColor);
				box->getleftBoxForBlue()->drawBoardBox();
			}
			if (box->getrightBoxForBlue() != NULL && !box->getrightBoxForBlue()->getcheckersIs()) {
				box->getrightBoxForBlue()->setcolor(activizationColor);
				box->getrightBoxForBlue()->drawBoardBox();
			}
		}
	}
	BoardBox* HelpBoxLeftRed = box, * HelpBoxRightRed = box, * HelpBoxLeftBlue = box, * HelpBoxRightBlue = box;
	if (!CanKill(box, move) && box->getcheckersIs() && box->getCheckers()->isLedy()) {
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs())
				break;
			HelpBoxLeftRed->setcolor(activizationColor);
			HelpBoxLeftRed->drawBoardBox();
		}
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs())
				break;
			HelpBoxRightRed->setcolor(activizationColor);
			HelpBoxRightRed->drawBoardBox();
		}
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs())
				break;
			HelpBoxLeftBlue->setcolor(activizationColor);
		}
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs())
				break;
			HelpBoxRightBlue->setcolor(activizationColor);
			HelpBoxRightBlue->drawBoardBox();
		}

	}
	if (CanKill(box, move) && box->getcheckersIs() && box->getCheckers()->isLedy()) {
		int enemy = 0;
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs())
				enemy++;
			if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1&&!HelpBoxLeftRed->getcheckersIs())
			{
				HelpBoxLeftRed->setcolor(activizationColor);
				HelpBoxLeftRed->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs())
				enemy++;
			if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxRightRed->getcheckersIs())
			{
				HelpBoxRightRed->setcolor(activizationColor);
				HelpBoxRightRed->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs())
				enemy++;
			if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxLeftBlue->getcheckersIs())
			{
				HelpBoxLeftBlue->setcolor(activizationColor);
				HelpBoxLeftBlue->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs())
				enemy++;
			if (HelpBoxRightBlue->getcheckersIs() && HelpBoxRightBlue->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxRightBlue->getcheckersIs())
			{
				HelpBoxRightBlue->setcolor(activizationColor);
				HelpBoxRightBlue->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}

	}
}
void Scene::resetActivizationBox(BoardBox* box) {
	box->setcolor(colorresetBlack);
	box->drawBoardBox();
	if (CanKill(box,move)&&!box->getCheckers()->isLedy()) {
		if (box->getleftBoxForRed() != NULL && box->getleftBoxForRed()->getleftBoxForRed() != NULL && box->getleftBoxForRed()->getcheckersIs() && !box->getleftBoxForRed()->getleftBoxForRed()->getcheckersIs())
		{
			box->getleftBoxForRed()->getleftBoxForRed()->setcolor(colorresetBlack);
			box->getleftBoxForRed()->getleftBoxForRed()->drawBoardBox();
		}
		if (box->getrightBoxForRed() != NULL && box->getrightBoxForRed()->getrightBoxForRed() != NULL && box->getrightBoxForRed()->getcheckersIs() && !box->getrightBoxForRed()->getrightBoxForRed()->getcheckersIs())
		{
			box->getrightBoxForRed()->getrightBoxForRed()->setcolor(colorresetBlack);
			box->getrightBoxForRed()->getrightBoxForRed()->drawBoardBox();
		}
		if (box->getleftBoxForBlue() != NULL && box->getleftBoxForBlue()->getleftBoxForBlue() != NULL && box->getleftBoxForBlue()->getcheckersIs() && !box->getleftBoxForBlue()->getleftBoxForBlue()->getcheckersIs())
		{
			box->getleftBoxForBlue()->getleftBoxForBlue()->setcolor(colorresetBlack);
			box->getleftBoxForBlue()->getleftBoxForBlue()->drawBoardBox();
		}
		if (box->getrightBoxForBlue() != NULL && box->getrightBoxForBlue()->getrightBoxForBlue() != NULL && box->getrightBoxForBlue()->getcheckersIs() && !box->getrightBoxForBlue()->getrightBoxForBlue()->getcheckersIs())
		{
			box->getrightBoxForBlue()->getrightBoxForBlue()->setcolor(colorresetBlack);
			box->getrightBoxForBlue()->getrightBoxForBlue()->drawBoardBox();
		}
	}
	if(!CanKill(box, move) && !box->getCheckers()->isLedy()){
		if (box->getleftBoxForRed() != NULL) {
			box->getleftBoxForRed()->setcolor(colorresetBlack);
			box->getleftBoxForRed()->drawBoardBox();
		}
		if (box->getrightBoxForRed() != NULL) {
			box->getrightBoxForRed()->setcolor(colorresetBlack);
			box->getrightBoxForRed()->drawBoardBox();
		}

		if (box->getleftBoxForBlue() != NULL) {
			box->getleftBoxForBlue()->setcolor(colorresetBlack);
			box->getleftBoxForBlue()->drawBoardBox();
		}
		if (box->getrightBoxForBlue() != NULL) {
			box->getrightBoxForBlue()->setcolor(colorresetBlack);
			box->getrightBoxForBlue()->drawBoardBox();
		}
	}
	BoardBox* HelpBoxLeftRed = box, * HelpBoxRightRed = box, * HelpBoxLeftBlue = box, * HelpBoxRightBlue = box;
	if (CanKill(box, move) && box->getCheckers()->isLedy()) {
		char anticolor;
		if (box->getCheckers()->getcolorCheckers() == 'r')
			anticolor = 'b';
		else
			anticolor = 'r';
		int enemy = 0;
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs())
				enemy++;
			if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxLeftRed->getcheckersIs())
			{
				HelpBoxLeftRed->setcolor(colorresetBlack);
				HelpBoxLeftRed->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs())
				enemy++;
			if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxRightRed->getcheckersIs())
			{
				HelpBoxRightRed->setcolor(colorresetBlack);
				HelpBoxRightRed->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs())
				enemy++;
			if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxLeftBlue->getcheckersIs())
			{
				HelpBoxLeftBlue->setcolor(colorresetBlack);
				HelpBoxLeftBlue->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
		enemy = 0;
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs())
				enemy++;
			if (HelpBoxRightBlue->getcheckersIs() && HelpBoxRightBlue->getCheckers()->getcolorCheckers() != anticolor)
				break;
			if (enemy == 1 && !HelpBoxRightBlue->getcheckersIs())
			{
				HelpBoxRightBlue->setcolor(colorresetBlack);
				HelpBoxRightBlue->drawBoardBox();
			}
			if (enemy == 2)
				break;
		}
	}
	if (!CanKill(box, move) && box->getCheckers()->isLedy()) {
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs())
				break;
			HelpBoxLeftRed->setcolor(colorresetBlack);
			HelpBoxLeftRed->drawBoardBox();
		}
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs())
				break;
			HelpBoxRightRed->setcolor(colorresetBlack);
			HelpBoxRightRed->drawBoardBox();
		}
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs())
				break;
			HelpBoxLeftBlue->setcolor(colorresetBlack);
		}
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs())
				break;
			HelpBoxRightBlue->setcolor(colorresetBlack);
			HelpBoxRightBlue->drawBoardBox();
		}
	}

}
void Scene::moveCheckers(BoardBox* FirstBox, BoardBox* SecondBox, int& move) {
		if (move == 1) {
			resetActivizationBox(FirstBox);
			SecondBox->setCheckersIs(true);
			SecondBox->setCheckers(FirstBox->getCheckers());
			FirstBox->setCheckersIs(false);
			SecondBox->getCheckers()->setxCenter(SecondBox->getxCenter());
			SecondBox->getCheckers()->setyCenter(SecondBox->getyCenter());
			FirstBox->setcolor(colorresetBlack);
			FirstBox->setCheckers(NULL);
			resetActivizationBox(SecondBox);
			resetActivizationCheckers(SecondBox->getCheckers());
		}
		else
		{
			resetActivizationBox(FirstBox);
			SecondBox->setCheckersIs(true);
			SecondBox->setCheckers(FirstBox->getCheckers());
			FirstBox->setCheckersIs(false);
			SecondBox->getCheckers()->setxCenter(SecondBox->getxCenter());
			SecondBox->getCheckers()->setyCenter(SecondBox->getyCenter());
			FirstBox->setcolor(colorresetBlack);
			FirstBox->setCheckers(NULL);
			resetActivizationBox(SecondBox);
			resetActivizationCheckers(SecondBox->getCheckers());
		}

		if (SecondBox->getCheckers()->getcolorCheckers() == 'r' && (SecondBox == &box[31] || SecondBox == &box[30] || SecondBox == &box[29] || SecondBox == &box[28]))
			SecondBox->getCheckers()->setLedy(true);
		if (SecondBox->getCheckers()->getcolorCheckers() == 'b' && (SecondBox == &box[0] || SecondBox == &box[1] || SecondBox == &box[2] || SecondBox == &box[3]))
			SecondBox->getCheckers()->setLedy(true);

	move *= -1;
}
bool Scene::killCheckers(BoardBox* FirstBox, BoardBox* SecondBox, int& move) {
	BoardBox* KilledBox = NULL;
	char anticolor;
	if (move == 1)
		anticolor = 'b';
	else
		anticolor = 'r';
	resetActivizationBox(FirstBox);
	BoardBox* HelpBoxLeftRed = FirstBox, * HelpBoxRightRed = FirstBox, * HelpBoxLeftBlue = FirstBox, * HelpBoxRightBlue = FirstBox;
	if (FirstBox->getCheckers()->isLedy()) {
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed->getCheckers()->getcolorCheckers() == anticolor)
				KilledBox = HelpBoxLeftRed;
			if (HelpBoxLeftRed == SecondBox)
				goto END;
		}
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed->getCheckers()->getcolorCheckers() == anticolor)
				KilledBox = HelpBoxRightRed;
			if (HelpBoxRightRed == SecondBox)
				goto END;
					}
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue->getCheckers()->getcolorCheckers() == anticolor)
				KilledBox = HelpBoxLeftBlue;
			if (HelpBoxLeftBlue == SecondBox)
				goto END;
		}
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs() && HelpBoxRightBlue->getCheckers()->getcolorCheckers() == anticolor)
				KilledBox = HelpBoxRightBlue;
			if (HelpBoxRightBlue == SecondBox)
				goto END;

		}

	}
	else {
		if (FirstBox->getleftBoxForRed() != NULL && FirstBox->getleftBoxForRed()->getleftBoxForRed() != NULL && FirstBox->getleftBoxForRed()->getleftBoxForRed() == SecondBox)
			KilledBox = FirstBox->getleftBoxForRed();
		if (FirstBox->getrightBoxForRed() != NULL && FirstBox->getrightBoxForRed()->getrightBoxForRed() != NULL && FirstBox->getrightBoxForRed()->getrightBoxForRed() == SecondBox)
			KilledBox = FirstBox->getrightBoxForRed();
		if (FirstBox->getleftBoxForBlue() != NULL && FirstBox->getleftBoxForBlue()->getleftBoxForBlue() != NULL && FirstBox->getleftBoxForBlue()->getleftBoxForBlue() == SecondBox)
			KilledBox = FirstBox->getleftBoxForBlue();
		if (FirstBox->getrightBoxForBlue() != NULL && FirstBox->getrightBoxForBlue()->getrightBoxForBlue() != NULL && FirstBox->getrightBoxForBlue()->getrightBoxForBlue() == SecondBox)
			KilledBox = FirstBox->getrightBoxForBlue();
	}
END:
	if (KilledBox==NULL) {
		return false;
	}
	SecondBox->setCheckersIs(true);
	SecondBox->setCheckers(FirstBox->getCheckers());
	FirstBox->setCheckersIs(false);
	KilledBox->removeCheckers();
	SecondBox->getCheckers()->setxCenter(SecondBox->getxCenter());
	SecondBox->getCheckers()->setyCenter(SecondBox->getyCenter());
	FirstBox->setcolor(colorresetBlack);
	KilledBox->setcolor(colorresetBlack);
	FirstBox->setCheckers(NULL);
	KilledBox->setCheckers(NULL);
	resetActivizationBox(SecondBox);
	resetActivizationCheckers(SecondBox->getCheckers());

	std::cout << REDCHECKERS;
	std::cout << BLUECHECHERS;

	if (anticolor == 'r')
		REDCHECKERS--;
	if (anticolor == 'b')
		BLUECHECHERS--;


	if (CanKill(SecondBox, move)) {
		return true;
	}
	if (SecondBox->getCheckers()->getcolorCheckers() == 'r' && (SecondBox == &box[31] || SecondBox == &box[30] || SecondBox == &box[29] || SecondBox == &box[28]))
		SecondBox->getCheckers()->setLedy(true);
	if (SecondBox->getCheckers()->getcolorCheckers() == 'b' && (SecondBox == &box[0] || SecondBox == &box[1] || SecondBox == &box[2] || SecondBox == &box[3]))
		SecondBox->getCheckers()->setLedy(true);


	move *= -1;
	return true;

}
bool Scene::CanKill(BoardBox* box,int move) {
	char anticolor;
	if (!box->getcheckersIs())
		return false;

	if (box->getCheckers()->getcolorCheckers() == 'r')
		anticolor = 'b';
	else
		anticolor = 'r';

	if (box->getCheckers()->isLedy()) {
		BoardBox* HelpBoxLeftRed = box, * HelpBoxRightRed = box, * HelpBoxLeftBlue = box, * HelpBoxRightBlue = box;
		while (1)
		{
			HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
			if (HelpBoxLeftRed == NULL)
				break;
			if (HelpBoxLeftRed->getcheckersIs() && !HelpBoxLeftRed->getCheckers()->getcolorCheckers() == anticolor)
				break;
			if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed->getCheckers()->getcolorCheckers() == anticolor)
				if (HelpBoxLeftRed->getleftBoxForRed() != NULL && !HelpBoxLeftRed->getleftBoxForRed()->getcheckersIs())
					return true;
		}
		while (1)
		{
			HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
			if (HelpBoxRightRed == NULL)
				break;
			if (HelpBoxRightRed->getcheckersIs() && !HelpBoxRightRed->getCheckers()->getcolorCheckers() == anticolor)
				break;
			if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed->getCheckers()->getcolorCheckers() == anticolor)
				if (HelpBoxRightRed->getrightBoxForRed() != NULL && !HelpBoxRightRed->getrightBoxForRed()->getcheckersIs())
					return true;
		}
		while (1)
		{
			HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
			if (HelpBoxLeftBlue == NULL)
				break;
			if (HelpBoxLeftBlue->getcheckersIs() && !HelpBoxLeftBlue->getCheckers()->getcolorCheckers() == anticolor)
				break;
			if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue->getCheckers()->getcolorCheckers() == anticolor)
				if (HelpBoxLeftBlue->getleftBoxForBlue() != NULL && !HelpBoxLeftBlue->getleftBoxForBlue()->getcheckersIs())
					return true;
		}
		while (1)
		{
			HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
			if (HelpBoxRightBlue == NULL)
				break;
			if (HelpBoxRightBlue->getcheckersIs() && !HelpBoxRightBlue->getCheckers()->getcolorCheckers() == anticolor)
				break;
			if (HelpBoxRightBlue->getcheckersIs() && HelpBoxRightBlue->getCheckers()->getcolorCheckers() == anticolor)
				if (HelpBoxRightBlue->getrightBoxForBlue() != NULL && !HelpBoxRightBlue->getrightBoxForBlue()->getcheckersIs())
					return true;
		}
	}
	else
	{
		if (move == 1)
		{
			if (box->getleftBoxForRed() != NULL)
			{
				if (box->getleftBoxForRed()->getleftBoxForRed() != NULL)
				{
					if (box->getleftBoxForRed()->getcheckersIs() && box->getleftBoxForRed()->getCheckers()->getcolorCheckers() == anticolor && !box->getleftBoxForRed()->getleftBoxForRed()->getcheckersIs())
					{
						return true;
					}
				}

			}
			if (box->getrightBoxForRed() != NULL)
			{
				if (box->getrightBoxForRed()->getrightBoxForRed() != NULL)
				{
					if (box->getrightBoxForRed()->getcheckersIs() && box->getrightBoxForRed()->getCheckers()->getcolorCheckers() == anticolor && !box->getrightBoxForRed()->getrightBoxForRed()->getcheckersIs())
					{
						return true;
					}
				}
			}
		}
		else 
		{
			if (box->getleftBoxForBlue() != NULL)
			{
				if (box->getleftBoxForBlue()->getleftBoxForBlue() != NULL)
				{
					if (box->getleftBoxForBlue()->getcheckersIs() && box->getleftBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor && !box->getleftBoxForBlue()->getleftBoxForBlue()->getcheckersIs())
					{
						return true;
					}
				}

			}
			if (box->getrightBoxForBlue() != NULL)
			{
				if (box->getrightBoxForBlue()->getrightBoxForBlue() != NULL)
				{
					if (box->getrightBoxForBlue()->getcheckersIs() && box->getrightBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor && !box->getrightBoxForBlue()->getrightBoxForBlue()->getcheckersIs())
					{
						return true;
					}
				}
			}
			
		}
		}

		return false;
}
bool Scene::findCheckers(int x, int y, int& number, BoardBox* box, int move)
{


	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;

	for (int i = 0; i < 32; i++)
	{
		double wx;
		double wy;
		double wz;
		// Світові x, y, z поточного стрижня:
		if (box[i].getcheckersIs()) {
			wx = box[i].getCheckers()->getxCenter();
			wy = box[i].getCheckers()->getyCenter();
			wz = 0.00;
		}
		else {
			continue;
		}


		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}

	if (minDist < 800) // знайшли найближчий стрижень
	{
		if (move == 1 && box[jMin].getCheckers()->getcolorCheckers() == 'r' || move == -1 && box[jMin].getCheckers()->getcolorCheckers() == 'b')
		{
			number = jMin;
			return true;
		}
		return false;
	}
	else
	{
		return false;
	}


}
bool Scene::findBox(int x, int y, int& number, BoardBox* box, BoardBox* activeBox, int move)
{
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;

	for (int i = 0; i < 32; i++)
	{
		double wx;
		double wy;
		double wz;
		// Світові x, y, z поточного стрижня:

		wx = box[i].getxCenter();
		wy = box[i].getyCenter();
		wz = 0.0;


		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}

	if (minDist < 800) // знайшли найближчий стрижень
	{
		number = jMin;

		if (activeBox->getCheckers()->isLedy())
		{
			BoardBox* HelpBoxLeftRed = activeBox, * HelpBoxRightRed = activeBox, * HelpBoxLeftBlue = activeBox, * HelpBoxRightBlue = activeBox;
			while (1)
			{
				HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
				if (HelpBoxLeftRed == NULL)
					break;
				if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed != activeBox)
					break;
				if (HelpBoxLeftRed == &box[number] && !HelpBoxLeftRed->getcheckersIs())
					return true;
			}
			while (1)
			{
				HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
				if (HelpBoxRightRed == NULL)
					break;
				if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed != activeBox)
					break;
				if (HelpBoxRightRed == &box[number]&&!HelpBoxRightRed->getcheckersIs())
					return true;
			}
			while (1)
			{
				HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
				if (HelpBoxLeftBlue == NULL)
					break;
				if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue != activeBox)
					break;
				if (HelpBoxLeftBlue == &box[number]&&!HelpBoxLeftBlue->getcheckersIs())
					return true;
			}
			while (1)
			{
				HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
				if (HelpBoxRightBlue == NULL)
					break;
				if (HelpBoxRightBlue->getcheckersIs() && HelpBoxLeftBlue != activeBox)
					break;
				if (HelpBoxRightBlue == &box[number]&&!HelpBoxRightBlue->getcheckersIs())
					return true;
			}
			return false;
		}
		else
		{
			if (activeBox->getleftBoxForBlue() == &box[number] || activeBox->getrightBoxForBlue() == &box[number] || activeBox->getleftBoxForRed() == &box[number] || activeBox->getrightBoxForRed() == &box[number])
			{
				if (move == 1)
				{
					if (activeBox->getleftBoxForRed() == &box[number] && !box[number].getcheckersIs())
						return true;
					if (activeBox->getrightBoxForRed() == &box[number] && !box[number].getcheckersIs())
						return true;
				}
				else
				{
					if (activeBox->getleftBoxForBlue() == &box[number] && !box[number].getcheckersIs())
						return true;
					if (activeBox->getrightBoxForBlue() == &box[number] && !box[number].getcheckersIs())
						return true;
				}
			}
		}
	}
	return false;
}
bool Scene::findFarBox(int x, int y, int& number, BoardBox* box, BoardBox* activeBox, int move) {
	char anticolor;
	if (move == 1)
		anticolor = 'b';
	else
		anticolor = 'r';
	int viewport[4];
	int iMin = -1, jMin = -1;
	double mvMatrix[16], projMatrix[16];
	double minDist = 1000;

	for (int i = 0; i < 32; i++)
	{
		double wx;
		double wy;
		double wz;
		// Світові x, y, z поточного стрижня:

		wx = box[i].getxCenter();
		wy = box[i].getyCenter();
		wz = 0.0;


		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix);
		glGetDoublev(GL_PROJECTION_MATRIX, projMatrix);
		double dx, dy, dz;
		gluProject(wx, wy, wz, mvMatrix, projMatrix, viewport, &dx, &dy, &dz);
		dy = viewport[3] - dy - 1;
		double d = (x - dx) * (x - dx) + (y - dy) * (y - dy);
		if (d < minDist)
		{
			minDist = d;
			jMin = i;
		}
	}

	if (minDist < 800) // знайшли найближчий стрижень
	{
		number = jMin;
		char anticolor;
		if (activeBox->getCheckers()->getcolorCheckers() == 'r')
			anticolor = 'b';
		else
			anticolor = 'r';
		if (activeBox->getCheckers()->isLedy()) {
			BoardBox* HelpBoxLeftRed = activeBox, * HelpBoxRightRed = activeBox, * HelpBoxLeftBlue = activeBox, * HelpBoxRightBlue = activeBox;
			int enemy=0;
			while (1)
			{
				HelpBoxLeftRed = HelpBoxLeftRed->getleftBoxForRed();
				if (HelpBoxLeftRed == NULL)
					break;
				if (HelpBoxLeftRed->getcheckersIs() && !HelpBoxLeftRed->getCheckers()->getcolorCheckers() == anticolor)
					break;
				if (HelpBoxLeftRed->getcheckersIs() && HelpBoxLeftRed->getCheckers()->getcolorCheckers() == anticolor)
					enemy++;
				if (enemy > 1)
					break;
				if (HelpBoxLeftRed == &box[number] && !HelpBoxLeftRed->getcheckersIs())
					return true;
			}
			enemy = 0;
			while (1)
			{
				HelpBoxRightRed = HelpBoxRightRed->getrightBoxForRed();
				if (HelpBoxRightRed == NULL)
					break;
				if (HelpBoxRightRed->getcheckersIs() && !HelpBoxRightRed->getCheckers()->getcolorCheckers() == anticolor)
					break;
				if (HelpBoxRightRed->getcheckersIs() && HelpBoxRightRed->getCheckers()->getcolorCheckers() == anticolor)
					enemy++;
				if (enemy > 1)
					break;
				if (HelpBoxRightRed == &box[number] && !HelpBoxRightRed->getcheckersIs())
					return true;
			}
			enemy = 0;
			while (1)
			{
				HelpBoxLeftBlue = HelpBoxLeftBlue->getleftBoxForBlue();
				if (HelpBoxLeftBlue == NULL)
					break;
				if (HelpBoxLeftBlue->getcheckersIs() && !HelpBoxLeftBlue->getCheckers()->getcolorCheckers() == anticolor)
					break;
				if (HelpBoxLeftBlue->getcheckersIs() && HelpBoxLeftBlue->getCheckers()->getcolorCheckers() == anticolor)
					enemy++;
				if (enemy > 1)
					break;
				if (HelpBoxLeftBlue == &box[number] && !HelpBoxLeftBlue->getcheckersIs())
					return true;
			}
			enemy = 0;
			while (1)
			{
				HelpBoxRightBlue = HelpBoxRightBlue->getrightBoxForBlue();
				if (HelpBoxRightBlue == NULL)
					break;
				if (HelpBoxRightBlue->getcheckersIs() && !HelpBoxRightBlue->getCheckers()->getcolorCheckers() == anticolor)
					break;
				if (HelpBoxRightBlue->getcheckersIs() && HelpBoxRightBlue->getCheckers()->getcolorCheckers() == anticolor)
					enemy++;
				if (enemy > 1)
					break;
				if (HelpBoxRightBlue == &box[number] && !HelpBoxRightBlue->getcheckersIs())
					return true;
			}
			return false;
		}
		else {
			if (move == 1) {
				if (activeBox->getleftBoxForRed() != NULL && activeBox->getleftBoxForRed()->getleftBoxForRed() != NULL && (&box[number] == activeBox->getleftBoxForRed()->getleftBoxForRed()) && activeBox->getleftBoxForRed()->getcheckersIs() && !activeBox->getleftBoxForRed()->getleftBoxForRed()->getcheckersIs() && activeBox->getleftBoxForRed()->getCheckers()->getcolorCheckers() == anticolor)
					return true;
				if (activeBox->getrightBoxForRed() != NULL && activeBox->getrightBoxForRed()->getrightBoxForRed() != NULL && (&box[number] == activeBox->getrightBoxForRed()->getrightBoxForRed()) && activeBox->getrightBoxForRed()->getcheckersIs() && !activeBox->getrightBoxForRed()->getrightBoxForRed()->getcheckersIs() && activeBox->getrightBoxForRed()->getCheckers()->getcolorCheckers() == anticolor)
					return true;
				return false;
			}
			else {
				if (activeBox->getleftBoxForBlue() != NULL && activeBox->getleftBoxForBlue()->getleftBoxForBlue() != NULL && (&box[number] == activeBox->getleftBoxForBlue()->getleftBoxForBlue()) && activeBox->getleftBoxForBlue()->getcheckersIs() && !activeBox->getleftBoxForBlue()->getleftBoxForBlue()->getcheckersIs() && activeBox->getleftBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor)
					return true;
				if (activeBox->getrightBoxForBlue() != NULL && activeBox->getrightBoxForBlue()->getrightBoxForBlue() != NULL && (&box[number] == activeBox->getrightBoxForBlue()->getrightBoxForBlue()) && activeBox->getrightBoxForBlue()->getcheckersIs() && !activeBox->getrightBoxForBlue()->getrightBoxForBlue()->getcheckersIs() && activeBox->getrightBoxForBlue()->getCheckers()->getcolorCheckers() == anticolor)
					return true;
				return false;
			}
		}
	}
	else
	{
		return false;
	}

}
bool Scene::WhoCanKill(BoardBox* box, int move) {
	for (int i = 0; i < 32; i++)
	{
		if (!box[i].getcheckersIs())
			continue;
		if ((move == 1 && box[i].getCheckers()->getcolorCheckers() == 'b') || move == -1 && box[i].getCheckers()->getcolorCheckers() == 'r')
			continue;
		if (CanKill(&box[i],move))
			return true;
	}
	return false;
}
void Scene::MyMouse(int button, int state, int x, int y) {

	int number;
	this->mouseX = x;
	this->mouseY = y;
	if ((state == GLUT_UP))
	{
		this->button = 0;
	}
	if ((button == GLUT_RIGHT_BUTTON) & (state == GLUT_DOWN))
	{
		this->button = 1;
		return;
	}
	if ((button == GLUT_LEFT_BUTTON) & (state == GLUT_DOWN))
	{
		if (GameOver()) {
			return;
		}
		this->button = -1;
		if (activeBox != NULL && findFarBox(x, y, number, this->getBox(), activeBox, move)&&CanKill(activeBox,move)) {
			if (killCheckers(activeBox, &this->getBox()[number], move)) {
				activeBox = NULL;
				activeCheckers = NULL;
				return;
			}
		}
		if (activeBox != NULL && findBox(x, y, number, this->getBox(), activeBox, move) && !CanKill(activeBox,move)) {
			moveCheckers(activeBox, &this->getBox()[number], move);
			activeBox = NULL;
			activeCheckers = NULL;
			return;
		}
		if (findCheckers(x, y, number, this->getBox(), move))
		{
			if (activeCheckers != NULL)
				resetActivizationCheckers(activeCheckers);//Если шашка до этого была выбрана, то ресетаем ее
			if (activeBox != NULL)
				resetActivizationBox(activeBox);// Ресетает выбраные до этого квадраты.
			if (WhoCanKill(this->getBox(), move))
			{
				if (CanKill(&this->getBox()[number],move))
				{
					activeBox = &this->getBox()[number];
					activeCheckers = this->getBox()[number].getCheckers();
					activizationCheckers(activeCheckers); //Светим выбраную шашку
					activizationNeigbords(activeBox, move); //Светим соседей выбраной шашки
					return;
				}
			}
			if (!WhoCanKill(this->getBox(), move)) {
				activeBox = &this->getBox()[number];
				activeCheckers = this->getBox()[number].getCheckers();
				activizationCheckers(activeCheckers); //Светим выбраную шашку
				activizationNeigbords(activeBox, move); //Светим соседей выбраной шашки
			}
		}
		return;
	}
}
void Scene::on_motion(int x, int y) {
	switch (this->button)
	{
	case 1:
	{
		this->angleX += x - this->mouseX;
		this->angleY += y - this->mouseY;
		this->mouseX = x;
		this->mouseY = y;
		std::cout << angleX;
		std::cout << angleY;
	}
	default:
		break;
	}
}
void Scene::keyboard(unsigned char key, int x, int y) {
	switch (key)
	{
	case '=':
	{
		if (this->zMe > -2.4)
			break;
		this->zMe += 0.1;
		break;
	}
	case '-':
	{
		this->zMe += -0.1;
		break;
	}
	case 27:
	{
		exit(0);
	}
	}

}
bool Scene::GameOver() {
	if (BLUECHECHERS == 0) {
		std::cout << "redwin";
		return true;
	} 
	if (REDCHECKERS == 0) {
		std::cout << "bluewin";
		return true;
	}
	return false;
}
void Scene::initializationScene(int w,int h) {


	std::ifstream outFile;
	outFile.open("fileInfo.txt");
	if (!outFile)
		std::cout << "ErrorFile";
	outFile >> this->gamecount;
	std::cout << std::endl << gamecount << std::endl;
	outFile.close();

	this->gamecount++;

	std::ofstream inFile;
	inFile.open("fileInfo.txt");
	if (!inFile)
		std::cout << "ErrorFile";
	inFile << this->gamecount;
	inFile.close();





	this->width = w;
	this->height = h;
	time = 0;
	tick = 0;
	this->zMe = -3;

	this->box = new BoardBox[32]{
		BoardBox(-0.8,-0.6,-0.6,-0.8,-0.8,-0.8,-0.6,-0.6,-0.7,-0.7,true,'r'),
		BoardBox(-0.4,-0.2,-0.2,-0.4,-0.8,-0.8,-0.6,-0.6,-0.3,-0.7,true,'r'),
		BoardBox(-0.0,0.2,0.2,-0.0,-0.8,-0.8,-0.6,-0.6,0.1,-0.7,true,'r'),
		BoardBox(0.4,0.6,0.6,0.4,-0.8,-0.8,-0.6,-0.6,0.5,-0.7,true,'r'),

		BoardBox(-0.6,-0.4,-0.4,-0.6,-0.6,-0.6,-0.4,-0.4,-0.5,-0.5,true,'r'),
		BoardBox(-0.2,-0.0,-0.0,-0.2,-0.6,-0.6,-0.4,-0.4,-0.1,-0.5,true,'r'),
		BoardBox(0.2,0.4,0.4,0.2,-0.6,-0.6,-0.4,-0.4,0.3,-0.5,true,'r'),
		BoardBox(0.6,0.8,0.8,0.6,-0.6,-0.6,-0.4,-0.4,0.7,-0.5,true,'r'),

		BoardBox(-0.8,-0.6,-0.6,-0.8,-0.4,-0.4,-0.2,-0.2,-0.7,-0.3,true,'r'),
		BoardBox(-0.4,-0.2,-0.2,-0.4,-0.4,-0.4,-0.2,-0.2,-0.3,-0.3,true,'r'),
		BoardBox(-0.0,0.2,0.2,-0.0,-0.4,-0.4,-0.2,-0.2,0.1,-0.3,true,'r'),
		BoardBox(0.4,0.6,0.6,0.4,-0.4,-0.4,-0.2,-0.2,0.5,-0.3,true,'r'),

		BoardBox(-0.6,-0.4,-0.4,-0.6,-0.2,-0.2,0.0,0.0,-0.5,-0.1,false,'r'),
		BoardBox(-0.2,-0.0,-0.0,-0.2,-0.2,-0.2,0.0,0.0,-0.1,-0.1,false,'r'),
		BoardBox(0.2,0.4,0.4,0.2,-0.2,-0.2,0.0,0.0,0.3,-0.1,false,'r'),
		BoardBox(0.6,0.8,0.8,0.6,-0.2,-0.2,0.0,0.0,0.7,-0.1,false,'r'),

		BoardBox(-0.8,-0.6,-0.6,-0.8,0.0,0.0,0.2,0.2,-0.7,0.1,false,'r'),
		BoardBox(-0.4,-0.2,-0.2,-0.4,0.0,0.0,0.2,0.2,-0.3,0.1,false,'r'),
		BoardBox(-0.0,0.2,0.2,-0.0,0.0,0.0,0.2,0.2,0.1,0.1,false,'r'),
		BoardBox(0.4,0.6,0.6,0.4,0.0,0.0,0.2,0.2,0.5,0.1,false,'r'),

		BoardBox(-0.6,-0.4,-0.4,-0.6,0.2,0.2,0.4,0.4,-0.5,0.3,true,'b'),
		BoardBox(-0.2,-0.0,-0.0,-0.2,0.2,0.2,0.4,0.4,-0.1,0.3,true,'b'),
		BoardBox(0.2,0.4,0.4,0.2,0.2,0.2,0.4,0.4,0.3,0.3,true,'b'),
		BoardBox(0.6,0.8,0.8,0.6,0.2,0.2,0.4,0.4,0.7,0.3,true,'b'),

		BoardBox(-0.8,-0.6,-0.6,-0.8,0.4,0.4,0.6,0.6,-0.7,0.5,true,'b'),
		BoardBox(-0.4,-0.2,-0.2,-0.4,0.4,0.4,0.6,0.6,-0.3,0.5,true,'b'),
		BoardBox(-0.0,0.2,0.2,-0.0,0.4,0.4,0.6,0.6,0.1,0.5,true,'b'),
		BoardBox(0.4,0.6,0.6,0.4,0.4,0.4,0.6,0.6,0.5,0.5,true,'b'),

		BoardBox(-0.6,-0.4,-0.4,-0.6,0.6,0.6,0.8,0.8,-0.5,0.7,true,'b'),
		BoardBox(-0.2,-0.0,-0.0,-0.2,0.6,0.6,0.8,0.8,-0.1,0.7,true,'b'),
		BoardBox(0.2,0.4,0.4,0.2,0.6,0.6,0.8,0.8,0.3,0.7,true,'b'),
		BoardBox(0.6,0.8,0.8,0.6,0.6,0.6,0.8,0.8,0.7,0.7,true,'b'),
	};////Itinalization boxes

				//initalization neighbord

	box[0].setleftBoxForRed(NULL);
	box[0].setrightBoxForRed(&box[4]);
	box[0].setleftBoxForBlue(NULL);
	box[0].setrightBoxForBlue(NULL);

	box[1].setleftBoxForRed(&box[4]);
	box[1].setrightBoxForRed(&box[5]);
	box[1].setleftBoxForBlue(NULL);
	box[1].setrightBoxForBlue(NULL);

	box[2].setleftBoxForRed(&box[5]);
	box[2].setrightBoxForRed(&box[6]);
	box[2].setleftBoxForBlue(NULL);
	box[2].setrightBoxForBlue(NULL);

	box[3].setleftBoxForRed(&box[6]);
	box[3].setrightBoxForRed(&box[7]);
	box[3].setleftBoxForBlue(NULL);
	box[3].setrightBoxForBlue(NULL);




	box[4].setleftBoxForRed(&box[8]);
	box[4].setrightBoxForRed(&box[9]);
	box[4].setleftBoxForBlue(&box[1]);
	box[4].setrightBoxForBlue(&box[0]);

	box[5].setleftBoxForRed(&box[9]);
	box[5].setrightBoxForRed(&box[10]);
	box[5].setleftBoxForBlue(&box[2]);
	box[5].setrightBoxForBlue(&box[1]);

	box[6].setleftBoxForRed(&box[10]);
	box[6].setrightBoxForRed(&box[11]);
	box[6].setleftBoxForBlue(&box[3]);
	box[6].setrightBoxForBlue(&box[2]);

	box[7].setleftBoxForRed(&box[11]);
	box[7].setrightBoxForRed(NULL);
	box[7].setleftBoxForBlue(NULL);
	box[7].setrightBoxForBlue(&box[3]);




	box[8].setleftBoxForRed(NULL);
	box[8].setrightBoxForRed(&box[12]);
	box[8].setleftBoxForBlue(&box[4]);
	box[8].setrightBoxForBlue(NULL);

	box[9].setleftBoxForRed(&box[12]);
	box[9].setrightBoxForRed(&box[13]);
	box[9].setleftBoxForBlue(&box[5]);
	box[9].setrightBoxForBlue(&box[4]);

	box[10].setleftBoxForRed(&box[13]);
	box[10].setrightBoxForRed(&box[14]);
	box[10].setleftBoxForBlue(&box[6]);
	box[10].setrightBoxForBlue(&box[5]);

	box[11].setleftBoxForRed(&box[14]);
	box[11].setrightBoxForRed(&box[15]);
	box[11].setleftBoxForBlue(&box[7]);
	box[11].setrightBoxForBlue(&box[6]);




	box[12].setleftBoxForRed(&box[16]);
	box[12].setrightBoxForRed(&box[17]);
	box[12].setleftBoxForBlue(&box[9]);
	box[12].setrightBoxForBlue(&box[8]);

	box[13].setleftBoxForRed(&box[17]);
	box[13].setrightBoxForRed(&box[18]);
	box[13].setleftBoxForBlue(&box[10]);
	box[13].setrightBoxForBlue(&box[9]);

	box[14].setleftBoxForRed(&box[18]);
	box[14].setrightBoxForRed(&box[19]);
	box[14].setleftBoxForBlue(&box[11]);
	box[14].setrightBoxForBlue(&box[10]);

	box[15].setleftBoxForRed(&box[19]);
	box[15].setrightBoxForRed(NULL);
	box[15].setleftBoxForBlue(NULL);
	box[15].setrightBoxForBlue(&box[11]);




	box[16].setleftBoxForRed(NULL);
	box[16].setrightBoxForRed(&box[20]);
	box[16].setleftBoxForBlue(&box[12]);
	box[16].setrightBoxForBlue(NULL);

	box[17].setleftBoxForRed(&box[20]);
	box[17].setrightBoxForRed(&box[21]);
	box[17].setleftBoxForBlue(&box[13]);
	box[17].setrightBoxForBlue(&box[12]);

	box[18].setleftBoxForRed(&box[21]);
	box[18].setrightBoxForRed(&box[22]);
	box[18].setleftBoxForBlue(&box[14]);
	box[18].setrightBoxForBlue(&box[13]);

	box[19].setleftBoxForRed(&box[22]);
	box[19].setrightBoxForRed(&box[23]);
	box[19].setleftBoxForBlue(&box[15]);
	box[19].setrightBoxForBlue(&box[14]);



	box[20].setleftBoxForRed(&box[24]);
	box[20].setrightBoxForRed(&box[25]);
	box[20].setleftBoxForBlue(&box[17]);
	box[20].setrightBoxForBlue(&box[16]);

	box[21].setleftBoxForRed(&box[25]);
	box[21].setrightBoxForRed(&box[26]);
	box[21].setleftBoxForBlue(&box[18]);
	box[21].setrightBoxForBlue(&box[17]);

	box[22].setleftBoxForRed(&box[26]);
	box[22].setrightBoxForRed(&box[27]);
	box[22].setleftBoxForBlue(&box[19]);
	box[22].setrightBoxForBlue(&box[18]);

	box[23].setleftBoxForRed(&box[27]);
	box[23].setrightBoxForRed(NULL);
	box[23].setleftBoxForBlue(NULL);
	box[23].setrightBoxForBlue(&box[19]);




	box[24].setleftBoxForRed(NULL);
	box[24].setrightBoxForRed(&box[28]);
	box[24].setleftBoxForBlue(&box[20]);
	box[24].setrightBoxForBlue(NULL);

	box[25].setleftBoxForRed(&box[28]);
	box[25].setrightBoxForRed(&box[29]);
	box[25].setleftBoxForBlue(&box[21]);
	box[25].setrightBoxForBlue(&box[20]);

	box[26].setleftBoxForRed(&box[29]);
	box[26].setrightBoxForRed(&box[30]);
	box[26].setleftBoxForBlue(&box[22]);
	box[26].setrightBoxForBlue(&box[21]);

	box[27].setleftBoxForRed(&box[30]);
	box[27].setrightBoxForRed(&box[31]);
	box[27].setleftBoxForBlue(&box[23]);
	box[27].setrightBoxForBlue(&box[22]);




	box[28].setleftBoxForRed(NULL);
	box[28].setrightBoxForRed(NULL);
	box[28].setleftBoxForBlue(&box[25]);
	box[28].setrightBoxForBlue(&box[24]);

	box[29].setleftBoxForRed(NULL);
	box[29].setrightBoxForRed(NULL);
	box[29].setleftBoxForBlue(&box[26]);
	box[29].setrightBoxForBlue(&box[25]);

	box[30].setleftBoxForRed(NULL);
	box[30].setrightBoxForRed(NULL);
	box[30].setleftBoxForBlue(&box[27]);
	box[30].setrightBoxForBlue(&box[26]);

	box[31].setleftBoxForRed(NULL);
	box[31].setrightBoxForRed(NULL);
	box[31].setleftBoxForBlue(NULL);
	box[31].setrightBoxForBlue(&box[27]);

	activeBox = NULL;
	activeCheckers = NULL;
	this->angleX = 0;
	this->angleY = -50;



	move = 1;
	REDCHECKERS = 12, BLUECHECHERS = 12;
}
void Scene::on_special(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_F2:
		initializationScene(width,height);
		break;
	}
}
void Scene::on_timer(int value)
{
	tick++;
	if (tick >= 2) // нарахували наступну секунду
	{
		if (!GameOver())// секунди нарощуються, якщо гру не закінчено
		{
			time++;
		}
		tick = 0;   // скинули лічильник
	}
	drawScene();     // здійснюємо перемалювання вікна
}