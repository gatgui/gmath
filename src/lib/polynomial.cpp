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

#include <gmath/polynomial.h>

namespace gmath {

  int Polynomial::ACCURACY = 6;
  float Polynomial::ZERO_TOLERANCE = 0.000001f;

  Polynomial::Polynomial(int deg)
    : degree(-1), coeff(0), owns(true) {
    if (deg >= 0) {
      degree = deg;
      coeff = new float[deg+1];
    }
  }
  
  Polynomial::Polynomial(int deg, float *fcoeffs)
    : degree(deg), coeff(fcoeffs), owns(false) {
  }

  Polynomial::Polynomial(const Polynomial &rhs)
    : degree(rhs.degree), coeff(0), owns(true) {
    if (rhs.owns) {
      if (degree >= 0) {
        coeff = new float[degree+1];
        for (int i = 0; i <= degree; i++) {
          coeff[i] = rhs.coeff[i];
        }
      } else {
        coeff = 0;
      }
    } else {
      owns = false;
      coeff = rhs.coeff;
    }
  }

  Polynomial::~Polynomial() {
    if (owns && coeff) {
      delete[] coeff;
    }
  }

  int Polynomial::getDegree(void) const {
    return degree;
  }

  bool Polynomial::setDegree(int deg) {
    if (deg != degree) {
      if (!owns) {
        return false;
      }
      if (coeff) {
        delete[] coeff;
      }
      coeff = 0;
      if (deg > -1) {
        coeff = new float[deg+1];
        degree = deg;
      } else {
        degree = -1;
      }
    }
    return true;
  }
  
  void Polynomial::setCoeffs(int deg, float *fcoeffs) {
    if (owns) {
      if (coeff) {
        delete[] coeff;
      }
    }
    coeff = fcoeffs;
    degree = deg;
    owns = false;
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
  
  bool Polynomial::getDerivative(Polynomial &deriv) const {
    if (degree > 0) {
      if (!deriv.setDegree(degree-1)) {
        return false;
      }
      
      for (int i0 = 0, i1 = 1; i0 < degree; i0++, i1++) {
        deriv[i0] = i1 * coeff[i1];
      }
      return true;
      
    } else {
      return false;
    }
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
  
  bool Polynomial::getInversion(Polynomial &inv) const {
    if (!inv.setDegree(degree)) {
      return false;
    }

    for (int i = 0; i <= degree; i++) {
      inv[i] = coeff[degree-i];
    }
    return true;
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
  
  Polynomial& Polynomial::operator*=(float scalar) {
    for (int i = 0; i <= degree; i++) {
      coeff[i] *= scalar;
    }
    return *this;
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
      if (owns && coeff) {
        delete[] coeff;
      }
      
      degree = rhs.degree;
      
      if (rhs.owns) {
        if (degree >= 0) {
          coeff = new float[degree+1];
          for (int i = 0; i <= degree; i++) {
            coeff[i] = rhs.coeff[i];
          }
        } else {
          coeff = 0;
        }
        owns = true;
        
      } else {
        coeff = rhs.coeff;
        owns = false;
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

    Polynomial deriv;
    if (!getDerivative(deriv)) {
      nroots = 0;
      return;
    }

    deriv.getRootsOn(min, max, nroots, roots);

    tmpRoots = new float[nroots+1];

    if (nroots > 0) {
      //Polynome is monotone on each interval defined by
      //the derivative roots [plus begin and end interval]

      //On those interval, function is not necessarily linear
      //some problem arise with infinite numbers and float limitation

      if (newton(min, roots[0], root)) {
        tmpRoots[nTmpRoots++] = root;
      }
      for (i = 0; i < nroots-1; i++) {
        if (newton(roots[i], roots[i+1], root)) {
          tmpRoots[nTmpRoots++] = root;
        }
      }
      if (newton(roots[nroots-1], max, root)) {
        tmpRoots[nTmpRoots++] = root;
      }
    } else {
      //Polynomial is monotone, at most one root
      if (newton(min, max, root)) {
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
    getRootsOn(-bound, bound, nroots, roots);
  }

  bool Polynomial::getDegree1Roots(int &nroots, float roots[1]) const {
    if (degree < 1) {
      nroots = 0;
      return false;
    }

    if (Abs(coeff[1]) < ZERO_TOLERANCE) {
      roots[0] = 0.0f;
    
    } else {
      roots[0] = -coeff[0] / coeff[1];
    }

    nroots = 1;
    return true;
  }

  bool Polynomial::getDegree2Roots(int &nroots, Complex<float> roots[2]) const {
    if (degree < 2) {
      nroots = 0;
      return false;
    }

    if (Abs(coeff[2]) < ZERO_TOLERANCE) {
      float roots1[1];
      if (!getDegree1Roots(nroots, roots1)) {
        return false;
      }
      if (nroots == 1) {
        roots[0].re = roots1[0];
        roots[0].im = 0.0f;
      }
      return true;
    }

    float discr = coeff[1]*coeff[1] - 4.0f*coeff[2]*coeff[0];

    if (discr < -ZERO_TOLERANCE) {
      // complex roots
      discr = Sqrt(-discr);
      float scalar = 0.5f * coeff[2]; 
      roots[0].re = -coeff[1] * scalar;
      roots[0].im = discr * scalar;
      roots[1].re = roots[0].re;
      roots[1].im = -roots[0].im;
      nroots = 2;

    } else {
      if (discr <= ZERO_TOLERANCE) {
        discr = 0.0f;
        nroots = 1;
      } else {
        nroots = 2;
      }

      discr = Sqrt(discr);
      float scalar = 0.5f / coeff[2];
      roots[0].re = scalar * (-coeff[1] + discr);
      roots[0].im = 0.0f;
      roots[1].re = scalar * (-coeff[1] - discr);
      roots[1].im = 0.0f;
    }

    return true;
  }

  bool Polynomial::getDegree2Roots(int &nroots, float roots[2]) const {
    if (degree < 2) {
      nroots = 0;
      return false;
    }

    if (Abs(coeff[2]) < ZERO_TOLERANCE) {
      return getDegree1Roots(nroots, roots);
    }

    float discr = coeff[1]*coeff[1] - 4.0f*coeff[2]*coeff[0];

    if (discr < -ZERO_TOLERANCE) {
      // complex roots
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

  bool Polynomial::getDegree3Roots(int &nroots, float roots[3]) const {
    static float a3rd = 1.0f / 3.0f;
    static float a27th = 1.0f / 27.0f;
    static float sqrt3 = Sqrt(3.0f);

    if (degree < 3) {
      nroots = 0;
      return false;
    }

    float p[4] = {coeff[0], coeff[1], coeff[2], coeff[3]};

    if (Abs(p[3]) < ZERO_TOLERANCE) {
      return getDegree2Roots(nroots, roots);
    }

    // p[3]*x^3 + p[2]*x^2 + p[1]*x + p[0] -> x^3 + x^2*(p[2]/p[3]) + x*(p[1]/p[3]) + p[0]/p[3]
    float inv3 = 1.0f / p[3];
    p[2] *= inv3;
    p[1] *= inv3;
    p[0] *= inv3;

    // Convert to the form y^3 + a*y + b using x = y - p[2]/3
    float off = a3rd * p[2];
    float A = p[1] - (p[2] * off);
    float B = p[0] + (a27th * p[2] * (2.0f * p[2] * p[2] - 9.0f * p[1]));
    float hB = 0.5f * B;
    float D = hB * hB + a27th * A * A * A;

    if (Abs(D) < ZERO_TOLERANCE) {
      D = 0.0f;
    }

    if (D > 0.0f) {
      D = Sqrt(D);
      float tmp = -hB + D;
      roots[0] = (tmp > 0.0f ? Pow(tmp, a3rd) : -Pow(-tmp, a3rd));
      tmp = -hB - D;
      roots[0] += (tmp > 0.0f ? Pow(tmp, a3rd) : -Pow(-tmp, a3rd));
      roots[0] -= off;
      nroots = 1;

    } else if (D < 0.0f) {
      float dist = Sqrt(-a3rd * A);
      float angle = a3rd * Atan2(Sqrt(-D), -hB);
      float cosa = Cos(angle);
      float sina = Sin(angle);
      roots[0] = 2.0f * dist * cosa - off;
      roots[1] = -dist * (cosa + sqrt3 * sina) - off;
      roots[2] = -dist * (cosa - sqrt3 * sina) - off;
      // Sort roots
      float tmp;
      if (roots[1] < roots[0]) {
        tmp = roots[0]; roots[0] = roots[1]; roots[1] = tmp;
      }
      if (roots[2] < roots[0]) {
        tmp = roots[0]; roots[0] = roots[2]; roots[2] = tmp;
      }
      if (roots[2] < roots[1]) {
        tmp = roots[1]; roots[1] = roots[2]; roots[2] = tmp;
      }
      nroots = 3;

    } else {
      float tmp = (hB >= 0.0f ? -Pow(hB, a3rd) : Pow(-hB, a3rd));
      roots[0] = 2.0f * tmp - off;
      roots[1] = -tmp - off;
      roots[2] = roots[1];
      if (roots[1] < roots[0]) {
        roots[2] = roots[0];
        roots[0] = roots[1];
      }
      nroots = 2;
    }

    return true;
  }
  
}

std::ostream& operator<<(std::ostream &os, const gmath::Polynomial &p) {
  if (p.getDegree() >= 0) {
    os << "p(x) = ";
    for (int i=p.getDegree(); i>0; --i) {
      os << p[i] << "*x^" << i << " + ";
    }
    os << p[0];
  } else {
    os << "p(x) undefined" << std::endl;
  }
  return os;
}

gmath::Polynomial operator*(float scalar, const gmath::Polynomial &poly) {
  gmath::Polynomial prod(poly.getDegree());
  for (int i = 0; i < poly.getDegree(); i++) {
    prod[i] = scalar * poly[i];
  }
  return prod;
}

