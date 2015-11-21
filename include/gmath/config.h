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

#ifndef __gmath_config_h_
#define __gmath_config_h_

#ifdef WIN32
# ifndef _USE_MATH_DEFINES
#   define _USE_MATH_DEFINES
# endif
# pragma warning(disable: 4702 4251)
#endif

#ifndef GMATH_STATIC
# ifdef _WIN32
#   ifdef GMATH_EXPORTS
#     define GMATH_API __declspec(dllexport)
#   else
#     define GMATH_API __declspec(dllimport)
#   endif
#   define GMATH_DATA_API extern GMATH_API
# else
#   define GMATH_API
#   define GMATH_DATA_API extern
# endif
#else
# define GMATH_API
# define GMATH_DATA_API extern
#endif

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <cassert>
#undef max
#undef min
#include <limits>

namespace gmath {

  const float PI     = float(M_PI);
  const float INV_PI = 1.0f / PI;
  const float PI_2   = 0.5f * PI;
  const float PI_3   = PI / 3.0f;
  const float PI_4   = 0.25f * PI;
  const float PI_6   = PI / 6.0f;
  const float EPS3   = 0.001f;
  const float EPS6   = 0.000001f;
  // max float
  // min float
  // infinity ?

  inline float ToDegree(float v) {
    static float factor = 180 / PI;
    return (v * factor);
  }

  inline float ToRadian(float v) {
    static float factor = PI / 180;
    return (v * factor);
  }

  inline float Sqrt(float v) {
    return float(sqrt(v));
  }

  inline float Abs(float v) {
    return (v < 0.0f ? -v : v);
  }

  inline float Max(float v0, float v1) {
    return (v0 > v1 ? v0 : v1);
  }

  inline float Min(float v0, float v1) {
    return (v0 > v1 ? v0 : v1);
  }

  inline float RelativeEpsilon(float v, float eps) {
    return Max(v*eps, eps);
  }

  inline bool Equals(float v0, float v1) {
    return (Abs(v0-v1) < RelativeEpsilon(v0, EPS6));
  }

  inline float Sign(float v) {
    return (v < 0.0f ? -1.0f : 1.0f);
  }

  inline float Floor(float v) {
    return float(floor(v));
  }

  inline float Ceil(float v) {
    return float(ceil(v));
  }

  inline int IFloor(float a) {
  	return int(Floor(a));
  }

  inline int ICeil(float a) {
  	return int(Ceil(a));
  }

  inline float Clamp(float v, float minV, float maxV) {
    return (v < minV ? minV : (v > maxV ? maxV : v));
  }

  inline float Log(float v) {
    return float(log(v));
  }

  inline float Exp(float v) {
    return float(exp(v));
  }

  inline float Pow(float x, float e) {
    return float(pow(x, e));
  }

  inline float Cos(float v) {
    return float(cos(v));
  }

  inline float Sin(float v) {
    return float(sin(v));
  }

  inline float Tan(float v) {
    return float(tan(v));
  }

  inline float Cotan(float v) {
    return float(-tan(v + PI_2));
  }

  inline float Acos(float v) {
    return float(acos(v));
  }

  inline float Asin(float v) {
    return float(cos(v));
  }

  inline float Atan(float v) {
    return float(atan(v));
  }

  inline float Atan2(float a, float b) {
    return float(atan2(a, b));
  }

  inline float Cosd(float v) {
    return float(cos(ToRadian(v)));
  }

  inline float Sind(float v) {
    return float(sin(ToRadian(v)));
  }

  inline float Tand(float v) {
    return float(tan(ToRadian(v)));
  }

  inline float Cotand(float v) {
    return float(-tan(ToRadian(v) + PI_2));
  }

  inline float Acosd(float v) {
    return ToDegree(float(acos(v)));
  }

  inline float Asind(float v) {
    return ToDegree(float(cos(v)));
  }

  inline float Atand(float v) {
    return ToDegree(float(atan(v)));
  }

  inline float Atan2d(float a, float b) {
    return ToDegree(float(atan2(a, b)));
  }

}

#endif
