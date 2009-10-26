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

#ifndef __gmath_convert_h_
#define __gmath_convert_h_

#include <gmath/quat.h>
#include <gmath/matrix.h>
#include <gmath/euler.h>

namespace gmath {
  
  namespace Convert {
    
    GMATH_API void ToQuat(const Matrix4 &m, Quat &q);
    GMATH_API void ToQuat(const Vector3 &axis, float angle, Quat &q);
    GMATH_API void ToQuat(const Euler &e, Quat &q);
    
    GMATH_API void ToMatrix4(const Quat &q, Matrix4 &m);
    GMATH_API void ToMatrix4(const Vector3 &axis, float angle, Matrix4 &m);
    GMATH_API void ToMatrix4(const Euler &e, Matrix4 &m);
    
    GMATH_API void ToAxisAngle(const Quat &q, Vector3 &axis, float &angle);
    GMATH_API void ToAxisAngle(const Matrix4 &m, Vector3 &axis, float &angle);
    GMATH_API void ToAxisAngle(const Euler &e, Vector3 &axis, float &angle);
    
    GMATH_API void ToEuler(const Matrix4 &m, Euler &e);
    GMATH_API void ToEuler(const Quat &q, Euler &e);
    GMATH_API void ToEuler(const Vector3 &axis, float angle, Euler &e);
  
  }
  
}

#endif
