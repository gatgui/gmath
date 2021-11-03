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

#ifndef __gmath_plane_h_
#define __gmath_plane_h_

#include <gmath/vector.h>
#include <gmath/matrix.h>

namespace gmath {
  
  class GMATH_API Plane {
    public:

      enum Side {
        POSITIVE = 0,
        ON,
        NEGATIVE
      };

      inline Plane()
        : mNormal(Vector3::ZERO), mDist(0) {
      }
      inline Plane(const Plane &rhs)
        : mNormal(rhs.mNormal), mDist(rhs.mDist) {
      }
      inline Plane(const Vector3 &n, float d)
        : mNormal(n), mDist(d) {
      }
      inline Plane(const Vector3 &n, const Vector3 &p)
        : mNormal(n) {
        mDist = - mNormal.normalize().dot(p);
      }
      inline Plane(const Vector4 &eq)
        : mNormal(Vector3(eq)), mDist(eq.w) {
        float l = 1.0f / mNormal.getLength();
        mDist *= l;
        mNormal *= l;
      }
      inline Plane(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2) {
        setup(p0, p1, p2);
      }
      inline ~Plane() {
      }
      
      inline Plane& operator=(const Plane &rhs) {
        if (this != &rhs) {
          mNormal = rhs.mNormal;
          mDist = rhs.mDist;
        }
        return *this;
      }

      inline const Vector3& getNormal() const {
        return mNormal;
      }

      inline float getD() const {
        return mDist;
      }

      inline void setNormal(const Vector3 &n) {
        mNormal = n;
        mNormal.normalize();
      }

      inline void setD(float d) {
        mDist = d;
      }
      
      inline float getDistanceTo(const Vector3 &p) const {
        return p.dot(mNormal) + mDist;
      }

      inline Side getSide(const Vector3 &p) const {
        float d = p.dot(mNormal) + mDist;
        return ((d < -EPS6) ? NEGATIVE : ((d > EPS6) ? POSITIVE : ON));
      }
      
      Plane& setup(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2);

      Plane& transform(const Matrix4 &matrix);

    protected:

      Vector3 mNormal;
      float mDist;
  };
  
}

inline gmath::Plane operator*(const gmath::Matrix4 &m, const gmath::Plane &p) {
  gmath::Plane tmp(p);
  return tmp.transform(m);
}


#endif
