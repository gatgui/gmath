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

#ifndef __gmath_box_h_
#define __gmath_box_h_

#include <gmath/matrix.h>
#include <gmath/plane.h>

namespace gmath {
  
  class GMATH_API Box {
    public:
      
      enum {
        PLANE_FRONT = 0,
        PLANE_BACK,
        PLANE_LEFT,
        PLANE_RIGHT,
        PLANE_TOP,
        PLANE_BOTTOM,
        PLANE_MASK = 0x07
      };
      
      enum {
        CORNER_LEFT = 0x01,
        CORNER_RIGHT = 0,
        CORNER_TOP = 0x02,
        CORNER_BOTTOM = 0,
        CORNER_FRONT = 0x04,
        CORNER_BACK = 0,
        CORNER_MASK = 0x07
      };
  
      Box();
      Box(const Box &rhs);
      virtual ~Box();
      
      Box& operator=(const Box &rhs);
      
      virtual Box& transform(const Matrix4 &m) = 0;
      
      virtual bool isPointInside(const Vector3 &pt, bool inclusive=true) const;
      
      inline void update() const {
        updateCorners();
        updatePlanes();
        mDirty = false;
      }
      
      inline const Vector3& getCorner(unsigned char i) const {
        if (mDirty) {
          update();
        }
        return mCorners[i & CORNER_MASK];
      }
      
      inline const Plane& getPlane(unsigned char i) const {
        if (mDirty) {
          update();
        }
        return mPlanes[i & PLANE_MASK];
      }
      
      
      
    protected:
      
      virtual void updateCorners() const = 0;
      void updatePlanes() const;
      void dirty();
      
      mutable Vector3 mCorners[8];
      mutable Plane mPlanes[6];
      mutable bool mDirty;
  };
  
}


#endif
