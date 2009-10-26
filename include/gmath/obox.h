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
