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

#ifndef __gmath_sphere_h_
#define __gmath_sphere_h_

#include <gmath/vector.h>

namespace gmath {
  
  class GMATH_API Sphere {

    public:

      inline Sphere()
        :mRadius(1) { //, mRadius2(1), mRadius3(1) {
      }
      
      inline Sphere(const Vector3 &c, float r)
        :mCenter(c), mRadius(r) { //, mRadius2(r*r), mRadius3(r*r*r) {
      }
      
      inline Sphere(const Sphere &rhs)
        :mCenter(rhs.mCenter), mRadius(rhs.mRadius) { //,
         //mRadius2(rhs.mRadius2), mRadius3(rhs.mRadius3) {
      }
      
      inline ~Sphere() {
      }

      inline Sphere& operator=(const Sphere &rhs) {
        if (this != &rhs) {
          mCenter = rhs.mCenter;
          mRadius = rhs.mRadius;
          //mRadius2 = rhs.mRadius2;
          //mRadius3 = rhs.mRadius3;
        }
        return *this;
      }
      
      inline bool operator==(const Sphere &rhs) const {
        return ((mCenter == rhs.mCenter) && (Abs(mRadius-rhs.mRadius) < EPS6));
      }
      
      inline bool operator!=(const Sphere &rhs) const {
        return !operator==(rhs);
      }
      
      inline bool isPointInside(const Vector3 &p, bool inclusive=true) const {
        float l = (p - mCenter).getSquaredLength();
        //return (inclusive ? (l <= mRadius2) : (l < mRadius2));
        return (inclusive ? (l <= (mRadius*mRadius)) : (l < (mRadius*mRadius)));
      }
      // add also to box
      
      inline const Vector3& getCenter() const {
        return mCenter;
      }
      
      inline float getRadius() const {
        return mRadius;
      }
      
      //inline float getRadius2() const {
      //  return mRadius2;
      //}
      
      //inline float getRadius3() const {
      //  return mRadius3;
      //}
      
      inline void setCenter(const Vector3 &c) {
        mCenter = c;
      }
      
      inline void setRadius(float r) {
        mRadius = r;
        //mRadius2 = r * r;
        //mRadius3 = mRadius2 * r;
      }
      
      inline float volume() const {
        return (4.0f * PI_3 * mRadius * mRadius * mRadius); //mRadius3);
      }
      
      static Sphere NaiveMinSphere(const std::vector<Vector3> &points);
      static Sphere FastMinSphere(const std::vector<Vector3> &points);
      static Sphere MinSphere(const std::vector<Vector3> &points, float eps=EPS3);

      
    private:
      
      Vector3 mCenter;
      float mRadius;
      //float mRadius2;
      //float mRadius3;
  };

}

inline std::ostream& operator<<(std::ostream &os, const gmath::Sphere &s) {
  os << "Sphere(" << s.getCenter() << " - " << s.getRadius() << ")";
  return os;
}



#endif
