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

#ifndef __gmath_quat_h_
#define __gmath_quat_h_

#include <gmath/vector.h>
#include <gmath/matrix.h>

namespace gmath {
  
  class GMATH_API Quat {
    public:
      
      static const Quat IDENTITY;
      static const Quat ZERO;
      
      float x;
      float y;
      float z;
      float w;
      
      inline Quat()
        : x(0), y(0), z(0), w(1) {
      }
      
      inline Quat(const float *v)
        : x(v[0]), y(v[1]), z(v[2]), w(v[2]) {
      }
      
      Quat(const Vector3 &axis, float a);
      
      inline Quat(float a, float b, float c, float d)
        : x(a), y(b), z(c), w(d) {
      }
      
      inline Quat(const Quat &rhs)
        : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {
      }
      
      inline ~Quat() {
      }
      
      inline Quat& operator=(const Quat &rhs) {
        if (this != &rhs) {
          x = rhs.x;
          y = rhs.y;
          z = rhs.z;
          w = rhs.w;
        }
        return *this;
      }
      
      inline bool equals(const Quat &rhs, float angularTolerance) {
        float angle = ToDegree(Acos(dot(rhs)));
        return (Abs(angle) <= angularTolerance ||
                Abs(angle-PI) <= angularTolerance);
      }
      
      inline Quat& operator+=(const Quat &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
      }
      
      inline Quat& operator-=(const Quat &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
      }
      
      inline Quat& operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
      }
      
      inline Quat& operator/=(float s) {
        s = 1.0f / s;
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
      }
      
      Quat& operator*=(const Quat &rhs);
      
      inline Quat operator-() const { // antipodal
        return Quat(-x, -y, -z, -w);
      }
      
      inline float dot(const Quat &rhs) const {
        return (x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
      }
      
      inline float getSquaredLength() const {
        return dot(*this);
      }
      
      inline float getLength() const {
        return Sqrt(getSquaredLength());
      }
      
      Quat& normalize();
      
      Quat& inverse();
      
      inline Quat& conjugate() {
        x = -x;
        y = -y;
        z = -z;
        return *this;
      }
      
      inline Quat getInverse() const {
        return Quat(*this).inverse();
      }
      
      inline Quat getConjugate() const {
        return Quat(*this).conjugate();
      }
      
      Quat getLog() const;
      Quat getExp() const;
      Quat getPow(float p) const;
      Quat slerp(const Quat &to, float t) const;
      
      // In both following function, taxis is the Twist axis when no rotation applied
      // decompose this quaternion in twist + swing 
      void decompTwistSwing(const Vector3 &twistAxis, Quat &twist, Quat &swing);
      // decompose this quaternion in swing + twist 
      void decompSwingTwist(const Vector3 &twistAxis, Quat &swing, Quat &twist);
      
      // ---
      
      static Quat Align(
        const Vector3 &axis0, const Vector3 &axis1,
        const Vector3 &fallback = Vector3::ZERO);
  };
  
}

GMATH_API gmath::Quat operator*(const gmath::Quat &q0, const gmath::Quat &q1);
GMATH_API gmath::Quat operator+(const gmath::Quat &q0, const gmath::Quat &q1);
GMATH_API gmath::Quat operator-(const gmath::Quat &q0, const gmath::Quat &q1);
GMATH_API gmath::Quat operator*(float s, const gmath::Quat &q);
GMATH_API gmath::Quat operator*(const gmath::Quat &q, float s);
GMATH_API gmath::Quat operator/(const gmath::Quat &q, float s);
GMATH_API gmath::Vector3 operator*(const gmath::Quat &q, const gmath::Vector3 &v);
GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::Quat &q);

#endif
