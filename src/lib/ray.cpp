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

#include <gmath/ray.h>

namespace gmath {
  
  bool Ray::intersect(const Plane &p, float *dist) const {
    // use dirEquals()
    float d = mDir.dot(p.getNormal());
    if (Abs(d) < EPS6) {
      // parallel
      return false;
    } else {
      float n = p.getNormal().dot(mOrg) + p.getD();
      float t = - n / d;
      if (dist) {
        *dist = t;
      }
      return (t >= 0);
    }
  }
  
  int Ray::intersect(const Sphere &s, float *dists) const {
    Vector3 v = mOrg - s.getCenter();
    float b = mDir.dot(v);
    float c = v.getSquaredLength() - (s.getRadius() * s.getRadius());
    float d = b*b - c;
    if (d < 0.0f) {
      return 0;
    } else if (4.0f*d < EPS6) {
      if (dists) {
        //t = -b;
        dists[0] = -b;
        dists[1] = -b;
      }
      return 1;
    } else {
      if (dists) {
        //float s = (c <= 0 ? 1.0f : -1.0f);
        //t = -b + s*(float)sqrt((double)d);
        float sd = Sqrt(d);
        dists[0] = -b - sd;
        dists[1] = -b + sd;
      }
      return 2;
    }
  }
  
  bool Ray::intersect(const AABox &aab, float *dist) const {
    Vector3 c = 0.5f * (aab.getMin() + aab.getMax());
    const Vector3 axis[3] = {Vector3::UNIT_X, Vector3::UNIT_Y, Vector3::UNIT_Z};
    Vector3 exts = 0.5f * (aab.getMax() - aab.getMin());
    return intersect(c, axis, exts, dist);
  }
  
  bool Ray::intersect(const OBox &ob, float *dist) const {
    const Vector3 axis[3] = {ob.getX(), ob.getY(), ob.getZ()};
    return intersect(ob.getCenter(), axis, ob.getExtents(), dist);
  }
  
  bool Ray::intersect(
    const Vector3 &c, const Vector3 axis[3], const Vector3 &exts, float *dist) const
  {
    float tmin = std::numeric_limits<float>::min();
    float tmax = std::numeric_limits<float>::max();
    Vector3 oc = c - mOrg;
    for (int i=0; i<3; ++i) {
      float e = oc.dot(axis[i]);
      float f = mDir.dot(axis[i]);
      if (Abs(f) > EPS6) {
        float inv_f = 1.0f / f;
        float t1 = (e + exts[i]) * inv_f;
        float t2 = (e - exts[i]) * inv_f;
        if (t1 > t2) {
          float tmp = t1;
          t1 = t2;
          t2 = tmp;
        }
        if (t1 > tmin) {
          tmin = t1;
        }
        if (t2 < tmax) {
          tmax = t2;
        } 
        if (tmin > tmax) {
          return false;
        }
        if (tmax < 0.0f) {
          return false;
        }
      }
    }
    if (dist) {
      if (tmin > 0.0f) {
        *dist = tmin;
      } else {
        *dist = tmax;
      }
    }
    return true;
  }
  
}
