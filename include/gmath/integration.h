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
