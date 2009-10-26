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
