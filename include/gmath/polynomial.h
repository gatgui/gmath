/*

Copyright (C) 2009  Gaetan Guidet

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

