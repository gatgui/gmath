/*
MIT License

Copyright (c) 2011 Gaetan Guidet

This file is part of gmath.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <gmath/all.h>
#ifdef __APPLE__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif

using namespace gmath;

typedef NURBS<2> NURBS2;
typedef NURBS<3> NURBS3;

// ---

bool gShowDerivative;
NURBS2 gCurve;
NURBS2 gDCurve;
double gMinX = -10.0;
double gMaxX = 10.0;
double gMinY = -10.0;
double gMaxY = 10.0;
double gSampleStep = 0.01;
int gResolX = 512;
int gResolY = 512;
double gFrameParam = 0.18;

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
  
  Vector<2> p, t, n;
  float u, ustart = 0.0, uend = 0.0;
  NURBS2 *curve = (gShowDerivative ? &gDCurve : &gCurve);
  
  // draw polyline
  glColor3d(0.8, 0.2, 0.0);
  glBegin(GL_LINE_STRIP);
  for (int i=0; i<curve->getNumCVs(); ++i)
  {
    p = curve->getCV(i);
    glVertex2d(p[0], p[1]);
  }
  glEnd();
  
  // draw curve
  glColor3d(1, 1, 1);
  glBegin(GL_LINE_STRIP);
  curve->getDomain(ustart, uend);
  u = ustart;
  while (u <= uend)
  {
    if (!curve->eval(u, p))
    {
      std::cerr << "*** Error evaluation curve at u = " << u << std::endl;
    }
    glVertex2d(p[0], p[1]);
    u += gSampleStep;
  }
  glEnd();
  
  // draw control points
  double pw = 2.0 * (gMaxX - gMinX) / double(gResolX);
  double ph = 2.0 * (gMaxY - gMinY) / double(gResolY);
  glColor3d(0, 0.2, 0.8);
  glBegin(GL_QUADS);
  for (int i=0; i<curve->getNumCVs(); ++i)
  {
    p = curve->getCV(i);
    glVertex2d(p[0] - pw, p[1] - ph);
    glVertex2d(p[0] + pw, p[1] - ph);
    glVertex2d(p[0] + pw, p[1] + ph);
    glVertex2d(p[0] - pw, p[1] + ph);
  }
  glEnd();
  
  // draw frame
  curve->eval(gFrameParam, p);
  curve->getTangent(gFrameParam, t);
  curve->getNormal(gFrameParam, n);
  
  glColor3d(0, 0.8, 0.2);
  glBegin(GL_LINES);
  glVertex2d(p[0], p[1]);
  glVertex2d(p[0]+t[0], p[1]+t[1]);
  glVertex2d(p[0], p[1]);
  glVertex2d(p[0]+n[0], p[1]+n[1]);
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
  NURBS2 *curve = (gShowDerivative ? &gDCurve : &gCurve);
  
  if (key == 27)
  {
    exit(0);
  }
  else if (key == 'c')
  {
    gCurve.buildKnotsUniform(true, true);
    gCurve.derivate(gDCurve);
    glutPostRedisplay();
  }
  else if (key == 'o')
  {
    gCurve.buildKnotsUniform(false, true);
    gCurve.derivate(gDCurve);
    glutPostRedisplay();
  }
  else if (key == 'i')
  {
    curve->insertKnot(0.5, 3);
    glutPostRedisplay();
  }
  else if (key == 's')
  {
    curve->trimAfter(0.5);
    curve->buildKnotsUniform(true);
    glutPostRedisplay();
  }
  else if (key == 'p')
  {
    std::cout << *curve << std::endl;
  }
  else if (key == 'd')
  {
    gShowDerivative = !gShowDerivative;
    glutPostRedisplay();
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
  NURBS2 nurbs(3);
  NURBS2 dnurbs(2);
  
  Vector<3> p;
  Vector<2> T, N, P;
  NURBS2::CVArray cvs;
  
  p[2] = 1.0;
  
  p[0] = -3.0; p[1] = -7.0;
  cvs.push_back(p);
  p[0] = -9.0; p[1] = -1.0;
  cvs.push_back(p);
  p[0] = 0.0; p[1] = 0.0;// p[2] = 5.0;
  cvs.push_back(p);
  p[0] = 3.0; p[1] = 9.0;// p[2] = 2.0;
  cvs.push_back(p);
  p[0] = 8.0; p[1] = 4.0;
  cvs.push_back(p);
  p[0] = 5.0; p[1] = -7.0;// p[2] = 3.0;
  cvs.push_back(p);
  p[0] = 3.0; p[1] = -1.0;
  cvs.push_back(p);
  p[0] = 0.0; p[1] = -5.0;
  cvs.push_back(p);
  
  nurbs.setCVs(cvs);
  nurbs.buildKnotsUniform(true);
  //nurbs.buildKnotsCentripetal();
  
  std::cout << nurbs << std::endl;
  
  std::cout << "Length = " << nurbs.getLength() << std::endl;
  
  std::cout << "Param at length 20.0 = " << nurbs.getParamAtLength(20.0, 0.01) << std::endl;
  
  nurbs.derivate(dnurbs);
  std::cout << "Derivate: " << dnurbs << std::endl;
  
  nurbs.getTangent(0.5, T);
  nurbs.getNormal(0.5, N);
  
  std::cout << "Tangent @ 0.5 = " << T << std::endl;
  std::cout << "Normal @ 0.5 = " << N << std::endl;
  
  if (nurbs.eval(0.5, P))
  {
    std::cout << "C(0.5) = " << P << std::endl;
  }
  else
  {
    std::cout << "Could not eval" << std::endl;
  }
  
  gCurve = nurbs;
  gDCurve = dnurbs;
  
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
