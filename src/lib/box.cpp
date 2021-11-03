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

#include <gmath/box.h>

namespace gmath {
  
  Box::Box() : mDirty(true) {
  }
  
  Box::Box(const Box &rhs) : mDirty(rhs.mDirty) {
    unsigned char i;
    for (i=0; i<8; ++i) {
      mCorners[i] = rhs.getCorner(i);
    }
    for (i=0; i<6; ++i) {
      mPlanes[i] = rhs.getPlane(i);
    }
  }
  
  Box::~Box() {
  }
  
  Box& Box::operator=(const Box &rhs) {
    if (this != &rhs) {
      unsigned char i;
      for (i=0; i<8; ++i) {
        mCorners[i] = rhs.getCorner(i);
      }
      for (i=0; i<6; ++i) {
        mPlanes[i] = rhs.getPlane(i);
      }
      mDirty = rhs.mDirty;
    }
    return *this;
  }
  
  bool Box::isPointInside(const Vector3 &pt, bool inclusive) const {
    for (unsigned char i=0; i<6; ++i) {
      Plane::Side sd = getPlane(i).getSide(pt);
      if (sd == Plane::POSITIVE || (!inclusive && sd == Plane::ON)) {
        return false;
      }
    }
    return true;
  }
  
  void Box::dirty() {
    mDirty = true;
  }
  
  void Box::updatePlanes() const {
    
    mPlanes[PLANE_TOP].setup(
      mCorners[CORNER_FRONT|CORNER_TOP|CORNER_LEFT],
      mCorners[CORNER_FRONT|CORNER_TOP|CORNER_RIGHT],
      mCorners[CORNER_BACK|CORNER_TOP|CORNER_RIGHT]);
      
    mPlanes[PLANE_BOTTOM].setup(
      mCorners[CORNER_FRONT|CORNER_BOTTOM|CORNER_LEFT],
      mCorners[CORNER_BACK|CORNER_BOTTOM|CORNER_LEFT],
      mCorners[CORNER_BACK|CORNER_BOTTOM|CORNER_RIGHT]);
    
    mPlanes[PLANE_LEFT].setup(
      mCorners[CORNER_BACK|CORNER_TOP|CORNER_LEFT],
      mCorners[CORNER_BACK|CORNER_BOTTOM|CORNER_LEFT],
      mCorners[CORNER_FRONT|CORNER_BOTTOM|CORNER_LEFT]);
    
    mPlanes[PLANE_RIGHT].setup(
      mCorners[CORNER_FRONT|CORNER_BOTTOM|CORNER_RIGHT],
      mCorners[CORNER_BACK|CORNER_BOTTOM|CORNER_RIGHT],
      mCorners[CORNER_BACK|CORNER_TOP|CORNER_RIGHT]);
    
    mPlanes[PLANE_FRONT].setup(
      mCorners[CORNER_FRONT|CORNER_BOTTOM|CORNER_LEFT],
      mCorners[CORNER_FRONT|CORNER_BOTTOM|CORNER_RIGHT],
      mCorners[CORNER_FRONT|CORNER_TOP|CORNER_RIGHT]);
    
    mPlanes[PLANE_BACK].setup(
      mCorners[CORNER_BACK|CORNER_BOTTOM|CORNER_LEFT],
      mCorners[CORNER_BACK|CORNER_TOP|CORNER_LEFT],
      mCorners[CORNER_BACK|CORNER_TOP|CORNER_RIGHT]);
  }
}

