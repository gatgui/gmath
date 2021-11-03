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

