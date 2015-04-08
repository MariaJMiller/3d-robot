//  robot.cpp
//  3d-robot
//
//  Created by Maria Miller on 4/3/15.
//  Copyright (c) 2015 Maria Miller. All rights reserved.
//

#include <cstdio>
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

rotation bodyRotate;
rotation armRotate;
color robotColor;
color eyeColor;

static int rightRun = 0;
static int leftRun = 0;
int ypos = 0;
bool moved = false;
bool jumped = false;

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
    
    eyeColor.r = 1;
    eyeColor.g = 1;
    eyeColor.b = 1;
    
    // Create body
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(2, 2.5, 1);
    glutSolidCube(5);
    glPopMatrix();

    // Create head
    glPushMatrix();
    glTranslatef(0, 8, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glutSolidCube(5);
    glPopMatrix();
    
    // Create right leg
    glPushMatrix();
    glTranslatef(-3, -12, 0);
    glRotatef(rightRun, 1.0f, 0, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.7, 2.2, 1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Create left leg
    glPushMatrix();
    glTranslatef(3, -12, 0);
    glRotatef(leftRun, 1.0f, 0, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.7, 2.2, 1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Right arm
    glPushMatrix();
    glTranslatef(-7, 0, 0);
    glRotatef(leftRun, 1.0f, 0, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.5, 1.8, 0.5);
    glutSolidCube(5);
    glPopMatrix();
    
    // Left arm
    glPushMatrix();
    glTranslatef(7, 0, 0);
    glRotatef(rightRun, 1.0f, 0, 0);
    glColor3f(robotColor.r, robotColor.g, robotColor.b);
    glScalef(0.5, 1.8, 0.5);
    glutSolidCube(5);
    glPopMatrix();
    
    // Right eye
    glPushMatrix();
    glTranslatef(-0.75, 8.5, 2.5);
    glColor3f(eyeColor.r, eyeColor.g, eyeColor.b);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(5);
    glPopMatrix();
    
    // Left eye
    glPushMatrix();
    glTranslatef(0.75, 8.5, 2.5);
    glColor3f(eyeColor.r, eyeColor.g, eyeColor.b);
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
    glTranslatef(-4, 8+ypos, -40);
    
    // Create the robot
    glRotatef(bodyRotate.y, 0, 1.0f, 0);
    createRobot();
    
    glutSwapBuffers();
}

static void run () {
    printf("RUN ");
    if (!moved) {
        rightRun = 25;
        leftRun = -25;
        moved = true;
    }
    
    if (rightRun == 25) {
        while (rightRun != -25) {
            rightRun--;
            leftRun++;
        }
    }
    
    else if (rightRun == -25) {
        while (rightRun != 25) {
            rightRun++;
            leftRun--;
        }
    }
    
}

static void jump() {
    
    if (!jumped) {
        ypos++;
        rightRun--;
        leftRun++;

        if (ypos == 10)
            jumped = true;
        
    }
    
    if (jumped) {
        ypos--;
        rightRun++;
        leftRun--;
        
        if (ypos == 0)
            jumped = false;
    }
}

static void reshape(int width, int height) {
    
    glViewport(0, 0, width, height);
}

void keyboard(int key, int x, int y) {
    switch(key) {
        case 'b': break;    // Blink eyes
        case 'c':           // Change color
            robotColor.r++;
            break;
        case 'd': break;    // Increase diffusive reflection
        case 's': break;    // Increase specular reflection
        case 'h': break;    // Increase shiny
        case 'j':           // Jump
            jump();
            break;
        case 'r':           // Run
            run();
            break;
        case 't':
            rightRun = 0;
            leftRun = 0;
            bodyRotate.y++;
            break;    // Turn around
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
    glutSpecialFunc(keyboard);
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}