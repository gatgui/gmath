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
