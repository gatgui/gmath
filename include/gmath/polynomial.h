/*
MIT License

Copyright (c) 2009 Gaetan Guidet

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

#ifndef __gmath_polynomial_h_
#define __gmath_polynomial_h_

#include <gmath/config.h>
#include <gmath/complex.h>

namespace gmath {

  class GMATH_API Polynomial {
    public:

      Polynomial(int deg = -1);
      Polynomial(int deg, float *fcoeffs);
      Polynomial(const Polynomial &rhs);
      ~Polynomial();

      int getDegree(void) const;
      bool setDegree(int deg);
      
      void setCoeffs(int deg, float *fcoeffs);

      float& operator[](int index);
      float operator[](int index) const;
      float operator()(float x) const {return eval(x);}

      float eval(float x) const;

      Polynomial getDerivative(void) const;
      bool getDerivative(Polynomial &p) const;
      
      Polynomial getInversion(void) const;
      bool getInversion(Polynomial &p) const;
      
      Polynomial operator+(const Polynomial &rhs) const;
      Polynomial operator-(const Polynomial &rhs) const;
      Polynomial operator*(const Polynomial &rhs) const;
      Polynomial operator*(float fScalar) const;
      Polynomial& operator*=(float fScalar); // the only one that may not change the polynomial degree
      Polynomial operator-() const;
      Polynomial& operator=(const Polynomial &rhs);

      // Root finding
      static int ACCURACY;
      static float ZERO_TOLERANCE;

      float getRootsBound(void) const;
      void getRootsOn(float min, float max, int &nroots, float *roots) const;
      void getAllRoots(int &nroots, float *roots) const;
      bool getDegree1Roots(int &nroots, float roots[1]) const;
      bool getDegree2Roots(int &nroots, float roots[2]) const;
      bool getDegree3Roots(int &nroots, float roots[3]) const;

      bool getDegree2Roots(int &nroots, Complex<float> roots[2]) const;

    protected:

      bool newton(float xmin, float xmax, float &root) const;

      int degree;
      float *coeff;
      bool owns;
  };

}

GMATH_API gmath::Polynomial operator*(float scalar, const gmath::Polynomial &poly);
GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::Polynomial &poly);

#endif

