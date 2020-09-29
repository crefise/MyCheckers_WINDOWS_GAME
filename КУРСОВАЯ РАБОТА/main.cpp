#include <gl/glut.h>
#include "Scene.h"										
#include <iostream>
#include "Checkers.h"
#include "HelpFunction.h"
using std::cout;
using std::endl;
double height = 600, width = 600;
Scene* scene;


void on_special(int key, int x, int y) {
	scene->on_special(key, x, y);
}
void on_size(int width, int height)
{
	scene->setwidth(width);
	if (height == 0)
		height = 1;
	scene->setheight(height);
}
void render() {
	scene->renderScene();
}
void mouse(int button, int state, int x, int y) {
	scene->MyMouse(button,state,x,y);
}
void on_motion(int x,int y) {
	scene->on_motion(x,y);
}
void keyboard(unsigned char key, int x, int y) {
	scene->keyboard(key,x,y);
}
void on_timer(int value) {
	scene->on_timer(value);
	glutTimerFunc(500, on_timer, 0);
}
void main(int argcp, char** argv) {
	Scene myScene(width, height);
	scene = &myScene;
	glutInit(&argcp, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width,height);
	glutCreateWindow("CHECKERS");
	glutDisplayFunc(render);
	glutIdleFunc(render);
	glutMouseFunc(mouse);
	glutMotionFunc(on_motion);
	glutReshapeFunc(on_size);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(on_special);
	glutTimerFunc(500, on_timer, 0);
	glutMainLoop();

}