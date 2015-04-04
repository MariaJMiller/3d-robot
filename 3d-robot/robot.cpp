//
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

void makeHead() {

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glPushMatrix();
    glColor3d(1, 0.5, 0.5);
    glTranslated(-2.0, 1.5, -6);
    glutSolidSphere(1, 50, 50);
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    const float ar = (float) width / (float) height;
    
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    
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
        case 'q': break;    // Quit
            
    }
}

void idle(void) {
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    
    glutCreateWindow("3D Robot");
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(keyboard);
    glutIdleFunc(idle);
    
    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    
    
    glutMainLoop();
    return EXIT_SUCCESS;
}