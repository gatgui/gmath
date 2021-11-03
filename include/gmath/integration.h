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

#ifndef __gmath_integration_h_
#define __gmath_integration_h_

#include <gmath/config.h>

namespace gmath {

	template <typename Real, unsigned int order>
	Real Integrate(Real from, Real to, Real (*f)(Real,void*), void *userData) {
	  //i0: current pass for trapezoidal rule
  	//p0: number of sample in this pass
  	Real coeff[2][order];

  	int i0, i1, i2, p0, p1;
  	Real h, sum;

  	h = to - from;

  	coeff[0][0] = 0.5f * h * (f(from, userData) + f(to, userData));

  	for (i0 = 1, p0 = 1; i0 < order; i0++, h *= 0.5f, p0 *= 2) {

  		//Trapezoidal rule
  		sum = 0.0f;
  		for (i1 = 1; i1 <= p0; i1++) {
  			sum += f(from + h*(i1-0.5f), userData);
  		}
  		coeff[1][0] = 0.5f * (coeff[0][0] + h*sum);

  		//Error correction
  		for (i2 = 1, p1 = 4; i2 <= i0; i2++, p1 *= 4) {
  			coeff[1][i2] = (p1 * coeff[1][i2-1] - coeff[0][i2-1]) / (p1 - 1);
  		}

  		//Keep value for next pass
  		for (i1 = 0; i1 <= i0; i1++) {
  			coeff[0][i1] = coeff[1][i1];
  		}

  	}

  	return coeff[0][order-1];
	}

}

#endif
