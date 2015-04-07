//  robot.cpp
//  3d-robot
//
//  Created by Maria Miller on 4/3/15.
//  Copyright (c) 2015 Maria Miller. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

struct rotation {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

struct color {
    GLdouble r;
    GLdouble g;
    GLdouble b;
};

rotation headRotate;
rotation bodyRotate;
rotation armRotate;
rotation legRotate;
color robotColor;
color eyeColor;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
}

static void createRobot() {
    
    static float angle = 0;
    
    robotColor.r = 0;
    robotColor.g = 1;
    robotColor.b = 0;
    
    // Create body
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glRotatef(angle, bodyRotate.x, bodyRotate.y, bodyRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glutSolidCube(10);
    glPopMatrix();

    // Create head
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glRotatef(angle, headRotate.x, headRotate.y, headRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glutSolidCube(5);
    glPopMatrix();
    
    // Create right leg
    glPushMatrix();
    glTranslatef(-3, -11, 0);
    glRotatef(angle, legRotate.x, legRotate.y, legRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.7, 2.2, 1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Create left leg
    glPushMatrix();
    glTranslatef(3, -11, 0);
    glRotatef(angle, legRotate.x, legRotate.y, legRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.7, 2.2, 1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Right arm
    glPushMatrix();
    glTranslatef(-8, 0, 0);
    glRotatef(angle, armRotate.x, armRotate.y, armRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.5, 1.8, 0.5);
    glutSolidCube(5);
    glPopMatrix();
    
    // Left arm
    glPushMatrix();
    glTranslatef(8, 0, 0);
    glRotatef(angle, armRotate.x, armRotate.y, armRotate.z);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.5, 1.8, 0.5);
    glutSolidCube(5);
    glPopMatrix();
    
    // Right eye
    glPushMatrix();
    glTranslatef(-0.75, 8, 4);
    glColor3f(1, 1, 1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Left eye
    glPushMatrix();
    glTranslatef(0.75, 8, 4);
    glColor3f(1, 1, 1);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(5);
    glPopMatrix();
    
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Move back
    glTranslatef(-5, 10, -40);
    
    // Create the robot
    createRobot();
    
    glutSwapBuffers();
}


static void reshape(int width, int height) {
    
    glViewport(0, 0, width, height);
}

void keyboard(int key, int x, int y) {
    switch(key) {
        case 'b': break;    // Blink eyes
        case 'c': break;    // Change color
        case 'd': break;    // Increase diffusive reflection
        case 's': break;    // Increase specular reflection
        case 'h': break;    // Increase shiny
        case 'j': break;    // Jump
        case 't': break;    // Turn around
        case 'w': break;    // Wave arms
        case 'q': exit(0); break;    // Quit
            
    }
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("3D Robot");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}