#include "GfxRenderer.hpp"

#include <GL/glut.h>

/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees 
   and is provided without guarantee or warrantee expressed or 
   implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
   will write the equivalent Direct3D immediate mode program. */
   GLfloat light_diffuse[] = {1.0, 0.0, 0.0, 1.0};  /* Red diffuse light. */
   GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};  /* Infinite light location. */
   GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
     {-1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0},
     {0.0, -1.0, 0.0}, {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0} };
   GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
     {0, 1, 2, 3}, {3, 2, 6, 7}, {7, 6, 5, 4},
     {4, 5, 1, 0}, {5, 6, 2, 1}, {7, 4, 0, 3} };
   GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */
   
void drawBox(void)
{
    int i;

    for (i = 0; i < 6; i++) {
        glBegin(GL_QUADS);
        glNormal3fv(&n[i][0]);
        glVertex3fv(&v[faces[i][0]][0]);
        glVertex3fv(&v[faces[i][1]][0]);
        glVertex3fv(&v[faces[i][2]][0]);
        glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void drawReferenceObjects (void)
{
    glBegin(GL_QUADS); 
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(-0.8f, 0.1f);     // Define vertices in counter-clockwise (CCW) order
        glVertex2f(-0.2f, 0.1f);     //  so that the normal (front-face) is facing you
        glVertex2f(-0.2f, 0.7f);
        glVertex2f(-0.8f, 0.7f);

        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(-0.7f, -0.6f);
        glVertex2f(-0.1f, -0.6f);
        glVertex2f(-0.1f,  0.0f);
        glVertex2f(-0.7f,  0.0f);

        glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
        glVertex2f(-0.9f, -0.7f);
        glColor3f(1.0f, 1.0f, 1.0f); // White
        glVertex2f(-0.5f, -0.7f);
        glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
        glVertex2f(-0.5f, -0.3f);
        glColor3f(1.0f, 1.0f, 1.0f); // White
        glVertex2f(-0.9f, -0.3f);
    glEnd();
 
    glBegin(GL_TRIANGLES);          // Each set of 3 vertices form a triangle
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(0.1f, -0.6f);
        glVertex2f(0.7f, -0.6f);
        glVertex2f(0.4f, -0.1f);

        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(0.3f, -0.4f);
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(0.9f, -0.4f);
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(0.6f, -0.9f);
    glEnd();
 
    glBegin(GL_POLYGON);            // These vertices form a closed polygon
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        glVertex2f(0.4f, 0.2f);
        glVertex2f(0.6f, 0.2f);
        glVertex2f(0.7f, 0.4f);
        glVertex2f(0.6f, 0.6f);
        glVertex2f(0.4f, 0.6f);
        glVertex2f(0.3f, 0.4f);
    glEnd();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);   // Clear the color buffer with current clearing color
    drawReferenceObjects();
    
      glutSwapBuffers();
   }

void init (void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
}

/* Handler for window re-size event. Called back when the window first appears and
   whenever the window is re-sized with its new width and height */
void reshape (GLsizei width, GLsizei height)
{
    // Compute aspect ratio of the new window
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
  
    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);
  
    // Set the aspect ratio of the clipping area to match the viewport
    glMatrixMode(GL_PROJECTION);  // To operate on the Projection matrix
    glLoadIdentity();             // Reset the projection matrix
    if (width >= height) {
      // aspect >= 1, set the height from -1 to 1, with larger width
       gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
       // aspect < 1, set the width to -1 to 1, with larger height
      gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
 }
  
void GfxRenderer::StartGfxRenderer()
{
    mGfxThread = new std::thread (&GfxRenderer::StartGlut, this);
}

void GfxRenderer::StopGfxRenderer()
{
    mGfxThread->join();
}

void GfxRenderer::StartGlut ()
{
    int argc = 0;
    glutInit(&argc, nullptr);
    //glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitDisplayMode(GLUT_DOUBLE);
    glutCreateWindow("PieJam");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    init();
    glutMainLoop();
}

