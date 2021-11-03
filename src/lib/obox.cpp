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

#include <gmath/obox.h>
#include <gmath/aabox.h>
#include <gmath/convert.h>

namespace gmath {
  
  OBox::OBox() {
    mAxis[0] = Vector3::UNIT_X;
    mAxis[1] = Vector3::UNIT_Y;
    mAxis[2] = Vector3::UNIT_Z;
  }
  
  OBox::OBox(const Vector3 &minPt, const Vector3 &maxPt)
    :Box() {
    mCenter = 0.5f * (minPt + maxPt);
    mExtents = 0.5f * (maxPt - minPt);
    mAxis[0] = Vector3::UNIT_X;
    mAxis[1] = Vector3::UNIT_Y;
    mAxis[2] = Vector3::UNIT_Z;
  }
  
  OBox::OBox(const Vector3 &c, const Quat &q, const Vector3 &e)
    :Box(), mCenter(c), mExtents(e) {
    Matrix4 tmp;
    Convert::ToMatrix4(q, tmp);
    mAxis[0] = Vector3(tmp.getColumn(0));
    mAxis[1] = Vector3(tmp.getColumn(1));
    mAxis[2] = Vector3(tmp.getColumn(2));
  }
  
  OBox::OBox(const OBox &rhs)
    :Box(rhs), mCenter(rhs.mCenter), mExtents(rhs.mExtents) {
    mAxis[0] = rhs.mAxis[0];
    mAxis[1] = rhs.mAxis[1];
    mAxis[2] = rhs.mAxis[2];
  }
  
  OBox::~OBox() {
  }
  
  float OBox::getRadius(const Vector3 &dir) const {
    float hw = 0.0f;
    for (int i=0; i<3; ++i) {
      Vector3 tmp = mExtents[i] * mAxis[i];
      hw += Abs(tmp.dot(dir));
    }
    return hw;
  }
  
  bool OBox::intersect(const OBox &ob) const {
    Vector3 caxis, c2c = getCenter() - ob.getCenter();
    float r0, r1, r;
    
    caxis = getX();
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getY();
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getZ();                        
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    
    caxis = ob.getX();
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = ob.getY();
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = ob.getZ();
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    
    caxis = getX().cross(ob.getX());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getX().cross(ob.getY());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getX().cross(ob.getZ());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;

    caxis = getY().cross(ob.getX());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getY().cross(ob.getY());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getY().cross(ob.getZ());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;

    caxis = getZ().cross(ob.getX());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getZ().cross(ob.getY());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    caxis = getZ().cross(ob.getZ());
    r0 = getRadius(caxis); r1 = ob.getRadius(caxis); r = Abs(c2c.dot(caxis));
    if (((r0 + r1) - r) < 0.0f) return false;
    
    return true;
  }                 
  
  bool OBox::intersect(const AABox &aab) const {
    OBox tmp;
    tmp.mCenter = 0.5f * (aab.getMax() + aab.getMin());
    tmp.mExtents = 0.5f * (aab.getMax() - aab.getMin());
    tmp.mAxis[0] = Vector3::UNIT_X;
    tmp.mAxis[1] = Vector3::UNIT_Y;
    tmp.mAxis[2] = Vector3::UNIT_Z;
    return intersect(tmp);
  }
  
  void OBox::merge(const Vector3 &pt) {
    Vector3 v = pt - getCenter();
    for (unsigned int i=0; i<3; ++i) {
      float e = Abs(pt.dot(mAxis[i]));
      if (e > mExtents[i]) {
        mExtents[i] = e;
        dirty();
      }
    }
  }
  
  void OBox::merge(const AABox &aab) {
    OBox tmp;
    tmp.mCenter = 0.5f * (aab.getMax() + aab.getMin());
    tmp.mExtents = 0.5f * (aab.getMax() - aab.getMin());
    tmp.mAxis[0] = Vector3::UNIT_X;
    tmp.mAxis[1] = Vector3::UNIT_Y;
    tmp.mAxis[2] = Vector3::UNIT_Z;
    tmp.dirty(); // because we use getCorner() in merge
    return merge(tmp);
  }
  
  void OBox::merge(const OBox &ob) {
    
    Quat q0 = getOrientation();
    Quat q1 = ob.getOrientation();
    Quat o = q0.slerp(q1, 0.5f);
    
    Matrix4 tmp;
    Convert::ToMatrix4(o, tmp);
    
    Vector3 c = 0.5f * (getCenter() + ob.getCenter());
    Vector3 e = Vector3::ZERO;
    Vector3 a[3];
    a[0] = Vector3(tmp.getColumn(0));
    a[1] = Vector3(tmp.getColumn(1));
    a[2] = Vector3(tmp.getColumn(2));
    
    for (unsigned char i=0; i<8; ++i) {
      const Vector3 &d0 = getCorner(i) - c;
      const Vector3 &d1 = ob.getCorner(i) - c;
      for (unsigned int j=0; j<3; ++j) {
        float e0 = Abs(d0.dot(a[j]));
        float e1 = Abs(d1.dot(a[j]));
        float eMax = Max(e0, e1);
        if (eMax > e[j]) {
          e[j] = eMax;
        }
      }
    }
    
    setCenter(c);
    setOrientation(o);
    setExtents(e);
  }
  
  void OBox::updateCorners() const {
    
    mCorners[CORNER_LEFT|CORNER_TOP|CORNER_FRONT] =
      mCenter + Vector3(-mExtents.x,  mExtents.y,  mExtents.z);
    
    mCorners[CORNER_LEFT|CORNER_TOP|CORNER_BACK] =
      mCenter + Vector3(-mExtents.x,  mExtents.y, -mExtents.z);
    
    mCorners[CORNER_RIGHT|CORNER_TOP|CORNER_FRONT] =
      mCenter + Vector3( mExtents.x,  mExtents.y,  mExtents.z);
    
    mCorners[CORNER_RIGHT|CORNER_TOP|CORNER_BACK] =
      mCenter + Vector3( mExtents.x,  mExtents.y, -mExtents.z);
      
    mCorners[CORNER_LEFT|CORNER_BOTTOM|CORNER_FRONT] =
      mCenter + Vector3(-mExtents.x, -mExtents.y,  mExtents.z);
    
    mCorners[CORNER_LEFT|CORNER_BOTTOM|CORNER_BACK] =
      mCenter + Vector3(-mExtents.x, -mExtents.y, -mExtents.z);
    
    mCorners[CORNER_RIGHT|CORNER_BOTTOM|CORNER_FRONT] =
      mCenter + Vector3( mExtents.x, -mExtents.y,  mExtents.z);
    
    mCorners[CORNER_RIGHT|CORNER_BOTTOM|CORNER_BACK] =
      mCenter + Vector3( mExtents.x, -mExtents.y, -mExtents.z);
  }
  
  OBox& OBox::operator=(const OBox &rhs) {
    Box::operator=(rhs);
    if (this != &rhs) {
      mCenter = rhs.mCenter;
      mExtents = rhs.mExtents;
      mAxis[0] = rhs.mAxis[0];
      mAxis[1] = rhs.mAxis[1];
      mAxis[2] = rhs.mAxis[2];
    }
    return *this;
  }
  
  Box& OBox::transform(const Matrix4 &m) {
    // to do
    for (int i=0; i<3; ++i) { // axis are vector, so m * mAxis[0] doesn't work (would use w = 1)
      mAxis[i] = Vector3(m * Vector4(mAxis[i], 0)); // persp divide ?
    }
    mCenter = m * mCenter;
    dirty();
    return *this;
  }
  
  Quat OBox::getOrientation() const {
    Matrix4 tmp;
    tmp.setColumn(0, Vector4(mAxis[0], 0.0f));
    tmp.setColumn(1, Vector4(mAxis[1], 0.0f));
    tmp.setColumn(2, Vector4(mAxis[2], 0.0f));
    Quat q;
    Convert::ToQuat(tmp, q);
    return q;
  }
  
  void OBox::setOrientation(const Quat &q) {
    Matrix4 tmp;
    Convert::ToMatrix4(q, tmp);
    mAxis[0] = Vector3(tmp.getColumn(0));
    mAxis[1] = Vector3(tmp.getColumn(1));
    mAxis[2] = Vector3(tmp.getColumn(2));
    dirty();
  }
  
}

