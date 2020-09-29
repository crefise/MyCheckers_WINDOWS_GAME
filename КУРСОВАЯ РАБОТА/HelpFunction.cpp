#include "HelpFunction.h"
#include <gl/glut.h>

void drawString(void* font, const char* text, float x, float y)
{
    if (!text)
    {
        return;
    }
    glRasterPos2f(x, y);
    while (*text)
    {
        glutBitmapCharacter(font, *text);
        text++;
    }
}