/*

Copyright (C) 2013  Gaetan Guidet

This file is part of gmath.

gmath is free software; you can redistribute it and/or modify it
under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at
your option) any later version.

gmath is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
USA.

*/

#include <gmath/gmath.h>
#include <gmath/curve.h>
#ifdef __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif

// ---

TCurve<float> gCurve;
Polynomial gPolies[2];
double gMinX = -1.0;
double gMaxX = 6.0;
double gMinY = -5.0;
double gMaxY = 5.0;
double gSampleStep = 0.01;
int gResolX = 512;
int gResolY = 512;
float gWeightIncr = 0.1f;
size_t gCurKey = 0;
bool gCurOut = true;

void display()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  // draw coordsys
  glColor3d(0.5, 0.5, 0.5);
  glBegin(GL_LINES);
  glVertex2d(gMinX, 0.0);
  glVertex2d(gMaxX, 0.0);
  glVertex2d(0.0, gMinY);
  glVertex2d(0.0, gMaxY);
  glEnd();
  
  float t, v, tstart = 0.0, tend = 0.0;
  double pw = 2.0 * (gMaxX - gMinX) / double(gResolX);
  double ph = 2.0 * (gMaxY - gMinY) / double(gResolY);
  
  
  // draw curve
  glColor3d(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  tstart = gCurve.tmin();
  tend = gCurve.tmax();
  t = tstart;
  while (t <= tend)
  {
    v = gCurve.eval(t, gCurve.isWeighted() ? gPolies : 0);
    glVertex2d(t, v);
    t += gSampleStep;
  }
  glEnd();
  
  // draw keys
  glColor3d(0.8, 0.2, 0.0);
  glBegin(GL_QUADS);
  for (size_t i=0; i<gCurve.numKeys(); ++i)
  {
    const TCurve<float>::Key &k = gCurve.getKey(i);
    glVertex2d(k.t - pw, k.v - ph);
    glVertex2d(k.t + pw, k.v - ph);
    glVertex2d(k.t + pw, k.v + ph);
    glVertex2d(k.t - pw, k.v + ph);
  }
  glEnd();
  
  // draw tangents points
  glColor3d(0, 0.2, 0.8);
  for (size_t i=0; i<gCurve.numKeys(); ++i)
  {
    const TCurve<float>::Key &k = gCurve.getKey(i);
    
    float indt = (i > 0 ? k.t - gCurve.getKey(i-1).t : 0.0f);
    float outdt = (i+1 < gCurve.numKeys() ? gCurve.getKey(i+1).t - k.t : 0.0f);
    
    if (indt <= 0.0f) indt = outdt;
    if (outdt <= 0.0f) outdt = indt;
    
    // scale for vizualization
    indt *= 0.3f;
    outdt *= 0.3f;
    
    if (gCurve.isWeighted())
    {
      t = k.t - indt * k.iw;
      v = k.v - indt * k.iw * k.it;
      glBegin(GL_QUADS);
      glVertex2d(t - pw, v - ph);
      glVertex2d(t + pw, v - ph);
      glVertex2d(t + pw, v + ph);
      glVertex2d(t - pw, v + ph);
      glEnd();
      
      glBegin(GL_LINES);
      glVertex2d(t, v);
      glVertex2d(k.t, k.v);
      glEnd();
      
      t = k.t + outdt * k.ow;
      v = k.v + outdt * k.ow * k.ot;
      glBegin(GL_QUADS);
      glVertex2d(t - pw, v - ph);
      glVertex2d(t + pw, v - ph);
      glVertex2d(t + pw, v + ph);
      glVertex2d(t - pw, v + ph);
      glEnd();
      
      glBegin(GL_LINES);
      glVertex2d(t, v);
      glVertex2d(k.t, k.v);
      glEnd();
    }
    else
    {
      t = k.t - indt;
      v = k.v - indt * k.it;
      glBegin(GL_QUADS);
      glVertex2d(t - pw, v - ph);
      glVertex2d(t + pw, v - ph);
      glVertex2d(t + pw, v + ph);
      glVertex2d(t - pw, v + ph);
      glEnd();
      
      glBegin(GL_LINES);
      glVertex2d(t, v);
      glVertex2d(k.t, k.v);
      glEnd();
      
      t = k.t + outdt;
      v = k.v + outdt * k.ot;
      glBegin(GL_QUADS);
      glVertex2d(t - pw, v - ph);
      glVertex2d(t + pw, v - ph);
      glVertex2d(t + pw, v + ph);
      glVertex2d(t - pw, v + ph);
      glEnd();
      
      glBegin(GL_LINES);
      glVertex2d(t, v);
      glVertex2d(k.t, k.v);
      glEnd();
    }
  }
  glEnd();
    
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  gResolX = w;
  gResolY = h;
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(gMinX, gMaxX, gMinY, gMaxY, -1, 1);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glutPostRedisplay();
}

void keyboard(unsigned char key, int, int)
{
  if (key == 27)
  {
    exit(0);
  }
  else if (key == 'w')
  {
    gCurve.setWeighted(!gCurve.isWeighted());
    glutPostRedisplay();
  }
  else if (key == '+')
  {
    if (gCurOut) {
      gCurve.setOutWeight(gCurKey, gCurve.getOutWeight(gCurKey) + gWeightIncr);
      std::cout << "[" << gCurKey << "] Out weight = " << gCurve.getOutWeight(gCurKey) << std::endl;
    } else {
      gCurve.setInWeight(gCurKey, gCurve.getInWeight(gCurKey) + gWeightIncr);
      std::cout << "[" << gCurKey << "] In weight = " << gCurve.getInWeight(gCurKey) << std::endl;
    }
    glutPostRedisplay();
  }
  else if (key == '-')
  {
    if (gCurOut) {
      gCurve.setOutWeight(gCurKey, gCurve.getOutWeight(gCurKey) - gWeightIncr);
      std::cout << "[" << gCurKey << "] Out Weight = " << gCurve.getOutWeight(gCurKey) << std::endl;
    } else {
      gCurve.setInWeight(gCurKey, gCurve.getInWeight(gCurKey) - gWeightIncr);
      std::cout << "[" << gCurKey << "] In Weight = " << gCurve.getInWeight(gCurKey) << std::endl;
    }
    glutPostRedisplay();
  }
  else if (key == 'n')
  {
    if (gCurOut)
    {
      if (gCurKey+1 < gCurve.numKeys())
      {
        gCurKey += 1;
        gCurOut = false;
      }
    }
    else
    {
      if (gCurKey+1 < gCurve.numKeys())
      {
        gCurOut = true;
      }
    }
    std::cout << "Weight target: Key " << gCurKey << (gCurOut ? " out weight" : " in weight") << std::endl;
  }
  else if (key == 'p')
  {
    //std::cout << gCurve << std::endl;
    if (gCurOut)
    {
      if (gCurKey > 0)
      {
        gCurOut = false;
      }
    }
    else
    {
      if (gCurKey > 0)
      {
        gCurKey -= 1;
        gCurOut = true;
      }
    }
    std::cout << "Weight target: Key " << gCurKey << (gCurOut ? " out weight" : " in weight") << std::endl;
  }
  else if (key == 'I')
  {
    gWeightIncr *= 10.0f;
    std::cout << "Weight increment: " << gWeightIncr << std::endl;
  }
  else if (key == 'i')
  {
    gWeightIncr *= 0.1f;
    if (gWeightIncr < 0.001f)
    {
      gWeightIncr = 0.001f;
    }
    std::cout << "Weight increment: " << gWeightIncr << std::endl;
  }
  else
  {
    std::cout << "Key " << int(key) << " pressed" << std::endl;
  }
}

void initGL()
{
  glClearColor(0, 0, 0, 1);
  glClearDepth(1);
  glDepthFunc(GL_LESS);
}

int main(int argc, char **argv)
{
  std::cout << "Set curve weighted" << std::endl;
  gCurve.setWeighted(true);

  std::cout << "Insert key at t = 0.0" << std::endl;
  gCurve.insert(0.0f, 0.0f);
  std::cout << "Insert key at t = 0.2" << std::endl;
  gCurve.insert(0.2f, 2.0f);
  std::cout << "Insert key at t = 0.9" << std::endl;
  gCurKey = gCurve.insert(0.9f, -3.0f);
  std::cout << "Insert key at t = 2.5" << std::endl;
  gCurve.insert(2.5f, 4.0f);
  std::cout << "Insert key at t = 3.6" << std::endl;
  gCurve.insert(3.6f, 2.9f);
  std::cout << "Insert key at t = 4.3" << std::endl;
  gCurve.insert(4.3f, 1.1f);
  std::cout << "Insert key at t = 5.0" << std::endl;
  gCurve.insert(5.0f, 0.0f);
  
  //gCurve.updateMaxWeights(ki);
  //gCurve.setOutWeight(ki, 2.0f);
  //std::cout << "Set weight of " << ki << "th key" << std::endl;
  //gCurve.setOutWeight(ki, 2.0f);
  // Max weight is somewhere between 3.7 and 3.8 (3.7 is fine, 3.8 is clamping)
  
  std::cout << gCurve << std::endl;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
  glutInitWindowPosition(50, 50);
  glutInitWindowSize(gResolX, gResolY);
  glutCreateWindow("Splines");
  initGL();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  
  return 0;
}
