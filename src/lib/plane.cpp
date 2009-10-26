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

#include <gmath/plane.h>

namespace gmath {

  Plane& Plane::setup(const Vector3 &p0, const Vector3 &p1, const Vector3 &p2) {
    Vector3 e0 = (p1 - p0).normalize();
    Vector3 e1 = (p2 - p0).normalize();
    mNormal = e0.cross(e1).normalize();
    mDist = - mNormal.dot(p0);
    return *this;
  }

  Plane& Plane::transform(const Matrix4 &matrix) {
    Vector3 pt = matrix * Vector3(-mDist*mNormal);
    (mNormal = Vector3(matrix * Vector4(mNormal,0))).normalize();
    mDist = - mNormal.dot(pt);
    /*
    Matrix4 invTrans = matrix.getInverse().getTranspose();
    Vector3 normal;
    normal.x = invTrans(0,0) * mNormal.x + invTrans(0,1) * mNormal.y + invTrans(0,2) * mNormal.z;
    normal.y = invTrans(1,0) * mNormal.x + invTrans(1,1) * mNormal.y + invTrans(1,2) * mNormal.z;
    normal.z = invTrans(2,0) * mNormal.x + invTrans(2,1) * mNormal.y + invTrans(2,2) * mNormal.z;
    Vector3 pt = -mDist * mNormal;
    pt = matrix * pt;
    // normal.normalize(); //?
    mDist = -pt.dot(normal);
    mNormal = normal;
    */      
    return *this;
  } 
}

