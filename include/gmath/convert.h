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
