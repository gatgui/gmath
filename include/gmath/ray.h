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

#ifndef __gmath_ray_h_
#define __gmath_ray_h_

#include <gmath/vector.h>
#include <gmath/plane.h>
#include <gmath/sphere.h>
#include <gmath/aabox.h>
#include <gmath/obox.h>

namespace gmath {
  
  class GMATH_API Ray {
    public:
  
      inline Ray() :mOrg(Vector3::ZERO), mDir(Vector3::UNIT_X) {
      }
      inline Ray(const Vector3 &org, const Vector3 &dir)
        :mOrg(org), mDir(dir) {
        mDir.normalize();
      }
      inline Ray(const Ray &rhs) :mOrg(rhs.mOrg), mDir(rhs.mDir) {
      }
      inline ~Ray() {
      }
      
      inline Ray& operator=(const Ray &rhs) {
        if (this != &rhs) {
          mOrg = rhs.mOrg;
          mDir = rhs.mDir;
        }
        return *this;
      }
      
      inline const Vector3& getDirection() const {
        return mDir;
      }
      inline const Vector3& getOrigin() const {
        return mOrg;
      }
      inline void setOrigin(const Vector3 &org) {
        mOrg = org;
      }
      inline void setDirection(const Vector3 &dir) {
        mDir = dir;
        mDir.normalize();
      }
      
      bool intersect(const Plane &p, float *dist=NULL) const;
      int intersect(const Sphere &s, float *dists=NULL) const;
      bool intersect(const AABox &aab, float *dist=NULL) const;
      bool intersect(const OBox &ob, float *dist=NULL) const;
      
      inline Vector3 getPoint(float t) const {
        return (mOrg + (t * mDir));
      }
  
    protected:
      
      bool intersect(const Vector3 &c, const Vector3 a[3], const Vector3 &e, float *dist) const;
      
      Vector3 mOrg;
      Vector3 mDir;
  };
}

inline std::ostream& operator<<(std::ostream &os, const gmath::Ray &r) {
  os << "Ray{" << r.getOrigin() << ", " << r.getDirection() << "}";
  return os;
}

#endif
