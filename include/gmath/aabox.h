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
