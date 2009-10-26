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

