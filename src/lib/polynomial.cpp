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

#include <gmath/polynomial.h>

namespace gmath {

  int Polynomial::ACCURACY = 6;
  float Polynomial::ZERO_TOLERANCE = 0.000001f;

  Polynomial::Polynomial(int deg)
  	: degree(-1), coeff(0) {
    if (deg >= 0) {
      degree = deg;
      coeff = new float[deg+1];
    }
  }

  Polynomial::Polynomial(const Polynomial &rhs)
    : degree(rhs.degree), coeff(0) {
    if (degree >= 0) {
      coeff = new float[degree+1];
      for (int i = 0; i <= degree; i++) {
        coeff[i] = rhs.coeff[i];
      }
    } else {
      coeff = 0;
    }
  }

  Polynomial::~Polynomial() {
    delete[] coeff;
  }

  int Polynomial::getDegree(void) const {
    return degree;
  }

  void Polynomial::setDegree(int deg) {
  	delete[] coeff;
  	coeff = 0;
  	if (deg > -1) {
  		coeff = new float[deg+1];
  		degree = deg;
  	} else {
  		degree = -1;
  	}
  }

  float& Polynomial::operator[](int index) {
    assert(index >= 0 && index <= degree);
    return coeff[index];
  }
  
  float Polynomial::operator[](int index) const {
    assert(index >= 0 && index <= degree);
    return coeff[index];
  }

  float Polynomial::eval(float x) const {
    assert(degree >= 0);

    float res = coeff[degree];

    for (int i = degree-1; i >= 0; i--) {
      res *= x;
      res += coeff[i];
    }
    return res;
  }

  Polynomial Polynomial::getDerivative(void) const {
    if (degree > 0) {
      Polynomial deriv(degree-1);

      for (int i0 = 0, i1 = 1; i0 < degree; i0++, i1++) {
        deriv[i0] = i1 * coeff[i1];
      }
      return deriv;
    } else {
      return Polynomial(-1);
    }
  }

  Polynomial Polynomial::getInversion(void) const {
    Polynomial inv(degree);

    for (int i = 0; i <= degree; i++) {
      inv[i] = coeff[degree-i];
    }
    return inv;
  }

  Polynomial Polynomial::operator+(const Polynomial &rhs) const {
    assert(degree >= 0 && rhs.degree >= 0);

    Polynomial sum(-1);
    int i;

    if (degree > rhs.degree) {
      sum.setDegree(degree);
      for (i = 0; i <= rhs.degree; i++) {
        sum[i] = coeff[i] + rhs.coeff[i];
      }
      for (i = rhs.degree+1; i <= degree; i++) {
        sum[i] = coeff[i];
      }
    } else {
      sum.setDegree(rhs.degree);
      for (i = 0; i <= degree; i++) {
        sum[i] = coeff[i] + rhs.coeff[i];
      }
      for (i = degree+1; i <= rhs.degree; i++) {
        sum[i] = rhs.coeff[i];
      }
    }
    return sum;
  }

  Polynomial Polynomial::operator-(const Polynomial &rhs) const {
    assert(degree >= 0 && rhs.degree >= 0);

    Polynomial sum(-1);
    int i;

    if (degree > rhs.degree) {
      sum.setDegree(degree);
      for (i = 0; i <= rhs.degree; i++) {
        sum[i] = coeff[i] - rhs.coeff[i];
      }
      for (i = rhs.degree+1; i <= degree; i++) {
        sum[i] = coeff[i];
      }
    } else {
      sum.setDegree(rhs.degree);
      for (i = 0; i <= degree; i++) {
        sum[i] = coeff[i] - rhs.coeff[i];
      }
      for (i = degree+1; i <= rhs.degree; i++) {
        sum[i] = -rhs.coeff[i];
      }
    }
    return sum;
  }

  Polynomial Polynomial::operator*(const Polynomial &rhs) const {
    assert(degree >= 0 && rhs.degree >= 0);

    Polynomial prod(degree + rhs.degree);

    memset(prod.coeff,0,(prod.degree+1)*sizeof(float));

    for (int i0 = 0; i0 <= degree; i0++) {
      for (int i1 = 0; i1 <= rhs.degree; i1++) {
        int i2 = i0 + i1;
        prod.coeff[i2] += coeff[i0] * rhs.coeff[i1];
      }
    }
    return prod;
  }

  Polynomial Polynomial::operator*(float scalar) const {
    assert(degree >= 0);

    Polynomial prod(degree);

    for (int i = 0; i <= degree; i++) {
      prod[i] = scalar * coeff[i];
    }
    return prod;
  }

  Polynomial Polynomial::operator-() const {
    assert(degree >= 0);

    Polynomial neg(degree);

    for (int i = 0; i <= degree; i++) {
      neg[i] = -coeff[i];
    }
    return neg;
  }

  Polynomial& Polynomial::operator=(const Polynomial &rhs) {
    if (this != &rhs) {
      if (degree >= 0) {
        delete[] coeff;
      }

      degree = rhs.degree;
        
  		if (degree >= 0) {
        coeff = new float[degree+1];
        for (int i = 0; i <= degree; i++) {
          coeff[i] = rhs.coeff[i];
        }
      } else {
        coeff = 0;
      }
    }
    return *this;
  }

  bool Polynomial::newton(float xmin, float xmax, float &root) const {
    static float ilog2 = 1.0f / Log(2.0f);

    float pxmin = eval(xmin);
    float pxmax = eval(xmax);

    if (Abs(pxmin) <= ZERO_TOLERANCE) {
      root = xmin;
      return true;
    }
    if (Abs(pxmax) <= ZERO_TOLERANCE) {
      root = xmax;
      return true;
    }

    /* - MAX ITERATION CALCULUS
      Each iteration divide search area by 2 so, after n iteration,
      the search area width will be:
      (1/2)^n * base_width, with base_width = xmax - xmin
      now if we want a precision of 3 digits, we don't have to go under
      an area width of 10^-3 (this would be useless, we don't ask so
	  much precision)
      Then we can calculte the maximun number of iteration n:
      (1/2)^n * (xmax - xmin) = 10^-ACCURACY
      thus: n = ( log(xmax - xmin) + ACCURACY ) / log(2)
      we need an integer, so we ceil the result, to be sure to have enough
	  precision
    
      NOTE: i tried with n fixed as explain above, but there were a problem of
	        inaccuracy
            and i prefer no result than inaccurate result
            so i factored by 2 the max number of iteration
            and return false if you go out of the loop
    */

    int maxIter = 2 * ICeil((Log(xmax-xmin) + ACCURACY) * ilog2);

    //Problem with float limitation and infinite numbers
  	// (like in operator(float fX))

    for (int i = 0; i <= maxIter; ++i) {

      root = 0.5f * (xmin+xmax);
      float proot = eval(root);

      if (Abs(proot) <= ZERO_TOLERANCE) {
        return true;
      }
      if (proot * pxmin < 0.0f) {
        pxmax = proot;
        xmax = root;
      } else if (proot * pxmax < 0.0f) {
        pxmin = proot;
        xmin = root;
      } else {
        return false;
      }
    }
    return true;
  }

  //REM: roots is supposed to be allocated, with
  //     enough space as needed
  //     so don't give an array of three float to get
  //     the roots of a degree 6 polynom ^^
  void Polynomial::getRootsOn(float min, float max, int &nroots, float *roots) const {
    float root;
    int i, nTmpRoots = 0;
    float *tmpRoots;

    if (degree == 1) {
      if (newton(min,max,root)) {
        nroots = 1;
        roots[0] = root;
      } else {
        nroots = 0;
      }
      return;
    }

    Polynomial deriv = getDerivative();

    deriv.getRootsOn(min,max,nroots,roots);

    tmpRoots = new float[nroots+1];

    if (nroots > 0) {
      //Polynome is monotone on each interval defined by
      //the derivative roots [plus begin and end interval]

      //On those interval, function is not necessarily linear
      //some problem arise with infinite numbers and float limitation

      if (newton(min,roots[0],root)) {
        tmpRoots[nTmpRoots++] = root;
      }
      for (i = 0; i < nroots-1; i++) {
        if (newton(roots[i],roots[i+1],root)) {
          tmpRoots[nTmpRoots++] = root;
        }
      }
      if (newton(roots[nroots-1],max,root)) {
        tmpRoots[nTmpRoots++] = root;
      }
    } else {
      //Polynomial is monotone, at most one root
      if (newton(min,max,root)) {
        tmpRoots[nTmpRoots++] = root;
      }
    }

    if (nTmpRoots > 0) {
      //We ask for a certain precision, so if two roots are close enough
      // (if the polynom has fast variation for example)
      // we can consider them as the same root for our precision
      nroots = 1;
      roots[0] = tmpRoots[0];
      for (i = 1; i < nTmpRoots; i++) {
        if (Abs(tmpRoots[i]-tmpRoots[i-1]) > ZERO_TOLERANCE) {
          roots[nroots++] = tmpRoots[i];
        }
      }
    } else {
      nroots = 0;
    }

  	delete[] tmpRoots;
  }

  float Polynomial::getRootsBound(void) const {
    float bound, tmp;
    int i;

    float abs0 = Abs(coeff[0]);
    float absD = Abs(coeff[degree]);

    if ( absD >= abs0 ) {
      bound = abs0;
      for (i = 0; i < degree; i++) {
        tmp = Abs(coeff[i]) + absD;
        if (bound < tmp) {
          bound = tmp;
        }
      }
      bound /= absD;
    } else {
      bound = absD;
      for (i = 0; i < degree; i++) {
        tmp = Abs(coeff[i]) + abs0;
        if (bound < tmp) {
          bound = tmp;
        }
      }
      bound /= abs0;
    }
    return bound;
  }

  void Polynomial::getAllRoots(int &nroots, float *roots) const {
    float bound = getRootsBound();
    getRootsOn(-bound,bound,nroots,roots);
  }

  bool Polynomial::getDegree2Roots(int &nroots, float roots[2]) const {
    if (degree != 2) {
  		nroots = 0;
      return false;
    }

    float discr = coeff[1]*coeff[1] - 4.0f*coeff[2]*coeff[0];

    if (discr < 0.0f) {
      nroots = 0;
    } else {
      if (discr <= ZERO_TOLERANCE) {
        discr = 0.0f;
        nroots = 1;
      } else {
        nroots = 2;
      }

      discr = Sqrt(discr);
      float scalar = 0.5f / coeff[2];
      roots[0] = scalar * (-coeff[1] + discr);
      roots[1] = scalar * (-coeff[1] - discr);
    }
    return true;
  }
  
}


gmath::Polynomial operator*(float scalar, const gmath::Polynomial &poly) {
  gmath::Polynomial prod(poly.getDegree());
  for (int i = 0; i < poly.getDegree(); i++) {
    prod[i] = scalar * poly[i];
  }
  return prod;
}

