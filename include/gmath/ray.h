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
