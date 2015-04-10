//  robot.cpp
//  3d-robot
//
//  Created by Maria Miller on 4/3/15.
//  Copyright (c) 2015 Maria Miller. All rights reserved.
//

#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

struct rotation {
    GLdouble x;
    GLdouble y;
    GLdouble z;
};

rotation bodyRotate;
rotation armRotate;

// Movement
float rightRun = 0.0f;
float leftRun = 0.0f;
float ypos = 0.0f;
float angle = 50.0f;
float armPos = 2.0f;
bool moved = false;
bool jumped = false;

// Color
int red = 1;
int green = 1;
int blue = 0;

int eyeRed = 1;
int eyeGreen = 1;
int eyeBlue = 1;

GLfloat ambient_light[]  = { 0, 0, 0, 1.0f };
GLfloat diffuse_light[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat specular_light[] = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat light_position[] = { -10.0f, 0, -2.0f, 1.0f};

GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_diffuse[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
GLfloat high_shininess[] = { 10.0f };

void init() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
     
}

static void createRobot() {
    
    // Create body
    glPushMatrix();
    glTranslatef(0, 0, 0);
    glColor3f(red, green, blue);
    glScalef(3, 3, 2);
    glutSolidCube(1);
    glPopMatrix();

    // Create head
    glPushMatrix();
    glTranslatef(0, 2, 0);
    glColor3f(red, green, blue);
    glScalef(1.5, 1, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Create right leg
    glPushMatrix();
    glTranslatef(-1, -2.5, 0);
    glRotatef(rightRun, 1.0f, 0, 0);
    glColor3f(red, green, blue);
    glScalef(1, 2.5, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Create left leg
    glPushMatrix();
    glTranslatef(1, -2.5, 0);
    glRotatef(leftRun, 1.0f, 0, 0);
    glColor3f(red, green, blue);
    glScalef(1, 2.5, 1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Right arm
    glPushMatrix();
    glTranslatef(-armPos, 1, 0);
    //glRotatef(leftRun, 2.0f, 0, 0);
    glRotatef(angle, 0, 0, 1.0f);
    glColor3f(red, green, blue);
    glScalef(0.3, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    // Left arm
    glPushMatrix();
    glTranslatef(armPos, 1, 0);
    //glRotatef(rightRun, 1.0f, 0, 0);
    glRotatef(-angle, 0, 0, 1.0f);
    glColor3f(red, green, blue);
    glScalef(0.3, 1.8, 0.5);
    glutSolidCube(1);
    glPopMatrix();
    
    // Right eye
    glPushMatrix();
    glTranslatef(-0.5, 2, 0.5);
    glColor3f(eyeRed, eyeGreen, eyeBlue);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
    // Left eye
    glPushMatrix();
    glTranslatef(0.5, 2, 0.5);
    glColor3f(eyeRed, eyeGreen, eyeBlue);
    glScalef(0.1, 0.1, 0.1);
    glutSolidCube(1);
    glPopMatrix();
    
}

// Move arms and legs
static void run () {

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
        rightRun = 0;
        leftRun = 0;
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

// Change color of robot
static void changeColor() {
    
    for (int i = 0; i < 3; i++) {
        specular_light[i] = 0;
    }
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);

    red = rand() % 2;
    green = rand() % 2;
    blue = rand() % 2;
    
}

// Blink eyes by switching from white to black to white.
static void blink() {
    // Change specular light so color changes are seen.
    for (int i = 0; i < 3; i++) {
        specular_light[i] = 0;
    }
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    
    if (eyeRed == 1) {
        eyeRed = 0;
        eyeGreen = 0;
        eyeBlue = 0;
    } else {
        eyeRed = 1;
        eyeGreen = 1;
        eyeBlue = 1;
    }
}

// Increase diffusive reflection
static void diffuseReflect() {

    float value = 0.1f;
    
    for (int i = 0; i < 4; i++) {
        value = 0.1f;
        if (diffuse_light[i] >= 1)
            diffuse_light[i] = 0;
        
        else
            diffuse_light[i] += value;
    
    }
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
}

static void specularReflect() {
   
    float value = 0.1f;
    
    for (int i = 0; i < 3; i++) {
        value = 0.1f;
        if (specular_light[i] >= 1)
            specular_light[i] = 0;
        
        else
            specular_light[i] += value;
    }
    
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
}

static void increaseShiny() {
    if (high_shininess[0] >= 100)
        high_shininess[0] = 0.0f;
    else
        high_shininess[0] += 10.0f;
    
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

// Wave arms by moving angle from 50 to 20
static void waveArms() {
    
    if (angle == 50)
        angle = 20;
    else
        angle = 50;
    
}

static void reshape(int width, int height) {
    
    glViewport(0, 0, width, height);
}

void keyboard(int key, int x, int y) {
    switch(key) {
        case 'b':           // Blink eyes
            blink();
            break;
        case 'c':           // Change color
            changeColor();
            break;
        case 'd':           // Increase diffusive reflection
            diffuseReflect();
            break;
        case 's':           // Increase specular reflection
            specularReflect();
            break;
        case 'h':           // Increase shiny
            increaseShiny();
            break;
        case 'j':           // Jump
            jump();
            break;
        case 'r':           // Run
            run();
            break;
        case 't':           // Turn Around
            rightRun = 0;
            leftRun = 0;
            ypos = 0;
            bodyRotate.y+=5;
            moved = false;
            break;
        case 'w':           // Wave arms
            waveArms();
            break;
        case 'q':           // Quit
            exit(0);
            break;
            
    }
    glutPostRedisplay();
}

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10.0f, 10.0f, -10.0f, 10.0f, -10.0f, 10.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Isometric view
    glRotatef(45.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);
    
    /*
    glMatrixMode(GL_PROJECTION);
    
    glLoadIdentity();
    GLint viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    double aspect = (double)viewport[2] / (double)viewport[3];
    gluPerspective(60, aspect, 1, 40);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    */
    // Move back
    //glTranslatef(-6, 0, 0);
    
    // Create the robot
    glRotatef(bodyRotate.y, 0, 1.0f, 0);
    createRobot();
    
    glutSwapBuffers();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(700, 700);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow("3D Robot");
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);

    // Random
    srand (time(NULL));
    
    init();
    
    glutMainLoop();
    
    return EXIT_SUCCESS;
}