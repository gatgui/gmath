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


#ifndef __gmath_aabox_h_
#define __gmath_aabox_h_

#include <gmath/box.h>

namespace gmath {
  
  class GMATH_API OBox;
  
  class GMATH_API AABox : public Box {
    
    public:
      
      AABox();
      AABox(const Vector3 &minPt, const Vector3 &maxPt);
      AABox(const Box &box);
      AABox(const AABox &rhs);
      virtual ~AABox();
    
      AABox& operator=(const AABox &rhs);
      
      virtual Box& transform(const Matrix4 &m);
      
      virtual bool isPointInside(const Vector3 &pt, bool inclusive=true) const;
      
      inline bool isNull() const {
        return mMin == mMax;
      }
      
      inline const Vector3& getMax() const {
        return mMax;
      }
      
      inline const Vector3& getMin() const {
        return mMin;
      }
      
      inline void reset() {
        mMin = mMax = Vector3::ZERO;
        dirty();
      }
      
      // you should initialize with one vertices before
      inline AABox& merge(const Vector3 &p) {
        mMin.floor(p);
        mMax.ceil(p);
        dirty();
        return *this;
      }
      
      inline AABox& merge(const Box &box) {
        for (unsigned char i=0; i<8; ++i) {
          merge(box.getCorner(i));
        }
        return *this;
      }
      
      bool intersect(const AABox &aab) const;
      bool intersect(const OBox &ob) const;
      
      inline void setMin(const Vector3 &min) {
        mMin = min;
        dirty();
      }
      
      inline void setMax(const Vector3 &max) {
        mMax = max;
        dirty();
      }
      
    protected:
      
      virtual void updateCorners() const;
      
      Vector3 mMin;
      Vector3 mMax;
  };
  
}

inline gmath::AABox operator*(const gmath::Matrix4 &m, const gmath::AABox &box) {
  gmath::AABox tmp(box);
  tmp.transform(m);
  return tmp;
}

#endif
