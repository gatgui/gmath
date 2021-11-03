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

#ifndef __APPLE__
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#endif
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <gmath/fft.h>
#include "glext.h"

using namespace gmath;


struct GlobalData
{
   enum What
   {
      ORIGINAL = 0,
      FFT,
      INV_FFT
   };
   int w;
   int h;
   GLuint tid;
   float *texData;
   Complex<float> *imgData;
   Complex<float> *fftData;
   Complex<float> *ifftData;
   //bool showFFT;
   What what;
   float fftScale;
};

GlobalData gData;

typedef Complex<float> fComplex;

void Init()
{
   gData.texData = new float[512 * 512 * 4];
   gData.imgData = new fComplex[512 * 512];
   gData.fftData = new fComplex[512 * 512];
   gData.ifftData = new fComplex[512 * 512];
   gData.what = GlobalData::ORIGINAL;
   gData.fftScale = 1.0f;
   
#if 0
   for (int y=256-32; y<256+32; ++y)
   {
      for (int x=256-32; x<256+32; ++x)
      {
         gData.imgData[y*512+x].re = 1.0f;
         gData.imgData[y*512+x].im = 0.0f;
      }
   }
#else
#if 0
   // Pure Cosine Signal
   float amp = 1.0f;
   float freqScale = 8.0f;
   float phase = 0.0f;
   float scale = float(2 * M_PI / 512);
   float val;
   
   for (int x=0; x<512; ++x)
   {
      val = 0.5f + 0.5 * cos((x * scale) * freqScale + phase);
      for (int y=0; y<512; ++y)
      {
         gData.imgData[y*512+x].re = val;
         gData.imgData[y*512+x].im = 0.0f;
      }
   }
#else
   // Rotated Cosine Signal (45 degrees around center of image
   //float amp = 1.0f;
   //float scale = float(2 * M_PI / 512);
   float freqScale = 16.0f;
   float phase = 0.0f;
   float nx, ny;
   
   for (int y=0, dst=0; y<512; ++y)
   {
      ny = 0.5f + 0.5f * y / float(512);
      for (int x=0; x<512; ++x, ++dst)
      {
         nx = 0.5f + 0.5f * x / float(512);
         gData.imgData[dst].re = 0.5f + 0.5 * cos((nx + ny) * M_PI * freqScale + phase);
         gData.imgData[dst].im = 0.0f;
      }
   }
#endif
#endif
   
   FFT::Forward(512, 512, gData.imgData, gData.fftData);
   FFT::Inverse(512, 512, gData.fftData, gData.ifftData);
}

void UpdateTexture()
{
   if (gData.what != GlobalData::FFT)
   {
      fComplex *src = (gData.what == GlobalData::ORIGINAL ? gData.imgData : gData.ifftData);
      
      for (int y=0, soff=0, doff=0; y<512; ++y)
      {
         for (int x=0; x<512; ++x, soff+=1, doff+=4)
         {
            float val = src[soff].re;
            gData.texData[doff] = val;
            gData.texData[doff+1] = val;
            gData.texData[doff+2] = val;
            gData.texData[doff+3] = 255;
         }
      }
   }
   else
   {
      fComplex *src = gData.fftData;
      
      //float freqScale = 1.0f / 512.0f;
      
      for (int y=0, soff=0; y<512; ++y)
      {
         for (int x=0; x<512; ++x, soff+=1)
         {
            // shift so that 0 frequency is at the center of the image
            int x1 = (x + 256) % 512;
            int y1 = (y + 256) % 512;
            
            int doff = 4 * ((y1 * 512) + x1);
            
            float val = gData.fftScale * sqrt(src[soff].squaredNorm());
            gData.texData[doff] = val;
            gData.texData[doff+1] = val;
            gData.texData[doff+2] = val;
            gData.texData[doff+3] = 255;
         }
      }
   }
   
   glBindTexture(GL_TEXTURE_2D, gData.tid);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F_ARB, 512, 512, 0, GL_RGBA, GL_FLOAT, gData.texData);
   glBindTexture(GL_TEXTURE_2D, 0);
}

void InitGL()
{
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_TEXTURE_2D);
   glDisable(GL_LIGHTING);
   glDisable(GL_COLOR_MATERIAL);
   
   glClearColor(0.5, 0.5, 0.5, 1);
   
   glShadeModel(GL_SMOOTH);
   
   glDepthFunc(GL_LEQUAL);
   
   glPixelStorei(GL_PACK_ALIGNMENT, 1);
   
   glGenTextures(1, &(gData.tid));
   glBindTexture(GL_TEXTURE_2D, gData.tid);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glBindTexture(GL_TEXTURE_2D, 0);
   
   UpdateTexture();
}

void Exit()
{
   glDeleteTextures(1, &(gData.tid));
   delete[] gData.texData;
   delete[] gData.imgData;
   delete[] gData.fftData;
}

void Display()
{
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   
   glPushMatrix();
   
   glBindTexture(GL_TEXTURE_2D, gData.tid);
   
   glBegin(GL_QUADS);
   glColor3f(1.0f, 1.0f, 1.0f);
   glTexCoord2f(0.0f, 0.0f); glVertex3f(0.1f, 0.1f, 0.0f);
   glTexCoord2f(1.0f, 0.0f); glVertex3f(0.9f, 0.1f, 0.0f);
   glTexCoord2f(1.0f, 1.0f); glVertex3f(0.9f, 0.9f, 0.0f);
   glTexCoord2f(0.0f, 1.0f); glVertex3f(0.1f, 0.9f, 0.0f);
   glEnd();
   
   glBindTexture(GL_TEXTURE_2D, 0);
   
   glPopMatrix();
   
   glutSwapBuffers();
}

void Reshape(int w, int h)
{
   gData.w = w;
   gData.h = h;
   
   glViewport(0, 0, w, h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0, 1, 0, 1, -1, 1);
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
   glutPostRedisplay();
}

void Keyboard(unsigned char key, int, int)
{
   switch (key)
   {
   case 27:
      exit(0);
   case 'f':
      switch (gData.what)
      {
      case GlobalData::FFT:
         std::cout << "Dispaly: Inverse FFT" << std::endl;
         gData.what = GlobalData::INV_FFT;
         break;
      case GlobalData::INV_FFT:
         std::cout << "Dispaly: Original" << std::endl;
         gData.what = GlobalData::ORIGINAL;
         break;
      case GlobalData::ORIGINAL:
      default:
         std::cout << "Dispaly: FFT" << std::endl;
         gData.what = GlobalData::FFT;
         break;
      }
      UpdateTexture();
      glutPostRedisplay();
      break;
   case '+':
      if (gData.what == GlobalData::FFT)
      {
         gData.fftScale *= 2.0f;
         std::cout << "FFT scale = " << gData.fftScale << std::endl;
         UpdateTexture();
         glutPostRedisplay();
      }
      break;
   case '-':
      if (gData.what == GlobalData::FFT)
      {
         gData.fftScale *= 0.5f;
         if (gData.fftScale < 1.0f)
         {
            gData.fftScale = 1.0f;
         }
         std::cout << "FFT scale = " << gData.fftScale << std::endl;
         UpdateTexture();
         glutPostRedisplay();
      }
      break;
   default:
      break;
   }
}

int main(int argc, char **argv)
{
   std::cout << "=== Test complex operation" << std::endl;
   
   Complex<double> c0(1, -1);
   Complex<double> c1(-2, 4);
   
   std::cout << c0 << " + " << c1 << " = " << (c0 + c1) << std::endl;
   std::cout << c0 << " - " << c1 << " = " << (c0 - c1) << std::endl;
   std::cout << c0 << " * " << c1 << " = " << (c0 * c1) << std::endl;
   std::cout << c0 << " / " << c1 << " = " << (c0 / c1) << std::endl;
   
   Complex<double> c2 = c1.conjugate();
   std::cout << "(" << c0 << " * " << c2 << ") / |" << c1 << "|^2 = " << (c0 * c2) / c1.squaredNorm() << std::endl;
   
   std::cout << "=== Test 2D FFT" << std::endl;
   
   Init();
   
   atexit(Exit);
   glutInit(&argc, argv);
   glutInitWindowPosition(50, 50);
   glutInitWindowSize(512, 512);
   glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);
   glutCreateWindow("FFT");
   InitGL();
   glutDisplayFunc(Display);
   glutReshapeFunc(Reshape);
   glutKeyboardFunc(Keyboard);
   glutMainLoop();
   
   return 0;
}

