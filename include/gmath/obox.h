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

#ifndef __gmath_obox_h_
#define __gmath_obox_h_

#include <gmath/box.h>
#include <gmath/quat.h>

namespace gmath {
  
  class GMATH_API AABox;
  
  class GMATH_API OBox : public Box {
    public:
  
      OBox();
      OBox(const Vector3 &minPt, const Vector3 &maxPt);
      OBox(const Vector3 &c, const Quat &q, const Vector3 &e);
      OBox(const OBox &rhs);
      virtual ~OBox();
      
      OBox& operator=(const OBox &rhs);
      
      virtual Box& transform(const Matrix4 &m);
      
      inline bool isNull() const {
        return mExtents == Vector3::ZERO;
      }
      
      inline void reset() {
        mExtents = Vector3::ZERO;
        dirty();
      }
      
      inline const Vector3& getCenter() const {
        return mCenter;
      }
      
      inline const Vector3& getX() const {
        return mAxis[0];
      }
      
      inline const Vector3& getY() const {
        return mAxis[1];
      }
      
      inline const Vector3& getZ() const {
        return mAxis[2];
      }
      
      inline const Vector3& getExtents() const {
        return mExtents;
      }
      
      inline const Vector3& getAxis(int i) const {
        return mAxis[i];
      }
      
      inline float getExtent(int i) const {
        return mExtents[i];
      }
      
      inline void setCenter(const Vector3 &c) {
        mCenter = c;
        dirty();
      }
      
      inline void setExtents(const Vector3 &e) {
        mExtents = e;
        dirty();
      }
      
      void setOrientation(const Quat &q);
      
      Quat getOrientation() const;
      
      void merge(const AABox &aab);
      void merge(const OBox &ob);
      void merge(const Vector3 &pt);
      
      bool intersect(const AABox &aab) const;
      bool intersect(const OBox &ob) const;
      
    protected:
      
      float getRadius(const Vector3 &dir) const;
      
      virtual void updateCorners() const;
      
      Vector3 mAxis[3];
      Vector3 mCenter;
      Vector3 mExtents;
  };
  
  
}

inline gmath::OBox operator*(const gmath::Matrix4 &m, const gmath::OBox &box) {
  gmath::OBox tmp(box);
  tmp.transform(m);
  return tmp;
}


#endif
