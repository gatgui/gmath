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

#include <gmath/aabox.h>
#include <gmath/obox.h>

namespace gmath {
  
  AABox::AABox()
    :mMin(Vector3::ZERO), mMax(Vector3::ZERO) {
  }
  
  AABox::AABox(const Vector3 &minPt, const Vector3 &maxPt)
    :Box(), mMin(minPt), mMax(maxPt) {
  }
  
  AABox::AABox(const Box &box) {
    mMin = mMax = box.getCorner(0);
    for (unsigned char i=1; i<8; ++i) {
      merge(box.getCorner(i));
    }
  }
  
  AABox::AABox(const AABox &rhs) 
    :Box(rhs), mMin(rhs.mMin), mMax(rhs.mMax) {
  }
  
  AABox::~AABox() {
  }
  
  AABox& AABox::operator=(const AABox &rhs) {
    Box::operator=(rhs);
    if (this != &rhs) {
      mMin = rhs.mMin;
      mMax = rhs.mMax;
    }
    return *this;
  }
  
  void AABox::updateCorners() const {
    mCorners[CORNER_LEFT|CORNER_TOP|CORNER_FRONT] = Vector3(mMin.x, mMax.y, mMax.z);
    mCorners[CORNER_LEFT|CORNER_TOP|CORNER_BACK] = Vector3(mMin.x, mMax.y, mMin.z);
    mCorners[CORNER_RIGHT|CORNER_TOP|CORNER_FRONT] = Vector3(mMax.x, mMax.y, mMax.z);
    mCorners[CORNER_RIGHT|CORNER_TOP|CORNER_BACK] = Vector3(mMax.x, mMax.y, mMin.z);
    mCorners[CORNER_LEFT|CORNER_BOTTOM|CORNER_FRONT] = Vector3(mMin.x, mMin.y, mMax.z);
    mCorners[CORNER_LEFT|CORNER_BOTTOM|CORNER_BACK] = Vector3(mMin.x, mMin.y, mMin.z);
    mCorners[CORNER_RIGHT|CORNER_BOTTOM|CORNER_FRONT] = Vector3(mMax.x, mMin.y, mMax.z);
    mCorners[CORNER_RIGHT|CORNER_BOTTOM|CORNER_BACK] = Vector3(mMax.x, mMin.y, mMin.z); 
  }
  
  bool AABox::isPointInside(const Vector3 &pt, bool inclusive) const {
    return (inclusive ? (pt >= mMin && pt <= mMax) : (pt > mMin && pt < mMax));
  }
  
  Box& AABox::transform(const Matrix4 &m) {
    Vector3 tc[8];
    unsigned char i;
    for (i=0; i<8; ++i) {
      tc[i] = m * getCorner(i);
    }
    mMin = mMax = tc[0];
    for (i=1; i<8; ++i) {
      merge(tc[i]);
    }
    dirty();
    return *this;
  }
  
  bool AABox::intersect(const AABox &aab) const {
    if (mMin.x > aab.mMax.x) return false;
    if (mMin.y > aab.mMax.y) return false;
    if (mMin.z > aab.mMax.z) return false;
    if (mMax.x < aab.mMin.x) return false;
    if (mMax.y < aab.mMin.y) return false;
    if (mMax.z < aab.mMin.z) return false;
    return true;
  }
  
  bool AABox::intersect(const OBox &ob) const {
    return ob.intersect(*this);
  }
  
}

