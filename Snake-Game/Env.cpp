#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "SnakeModel.h"


void drawEnv() {
    glColor4f(0.6, 0.0, 0.7, 0.7);
    glLineWidth(20);

    glBegin(GL_LINE_LOOP);
    glVertex2f(-1 * LIMIT - MARGIN / 2, -1 * LIMIT - MARGIN / 2);
    glVertex2f(LIMIT + MARGIN / 2, -1 * LIMIT - MARGIN / 2);
    glVertex2f(LIMIT + MARGIN / 2, LIMIT + MARGIN / 2);
    glVertex2f(-1 * LIMIT - MARGIN / 2, LIMIT + MARGIN / 2);
    glEnd();


    for (int i = -1 * LIMIT; i < LIMIT; i += GRIDWIDTH) {
        for (int j = -1 * LIMIT; j < LIMIT; j += GRIDWIDTH) {
            glColor4f(0.5, 0.5, 0.5, 0.2);
            glLineWidth(2);

            glBegin(GL_LINE_LOOP);
            glVertex2f(i, j);
            glVertex2f(i + GRIDWIDTH, j);
            glVertex2f(i + GRIDWIDTH, j + GRIDWIDTH);
            glVertex2f(i, j + GRIDWIDTH);
            glEnd();
        }
    }
}

