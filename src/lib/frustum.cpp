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

#include <gmath/frustum.h>

namespace gmath {
  
  Frustum::Frustum()
    :mFovy(56.0f), mAspect(4.0f/3.0f), mNear(100.f), mFar(100000.0f),
     mMode(PM_PERSPECTIVE), mFocal(1), mOffsetX(0), mOffsetY(0), mCustomMatrix(false) {
  }
  
  Frustum::Frustum(ProjectionMode mode, float fovy, float asp, float np, float fp)
    :Box(), mFovy(fovy), mAspect(asp), mNear(np), mFar(fp), mMode(mode),
     mFocal(1), mOffsetX(0), mOffsetY(0), mCustomMatrix(false) {
  }
  
  Frustum::Frustum(const Frustum &rhs)
    :Box(rhs), mFovy(rhs.mFovy), mAspect(rhs.mAspect), mNear(rhs.mNear),
     mFar(rhs.mFar), mMode(rhs.mMode), mFocal(rhs.mFocal), mOffsetX(rhs.mOffsetX),
     mOffsetY(rhs.mOffsetY), mCustomMatrix(rhs.mCustomMatrix), mLeft(rhs.mLeft),
     mRight(rhs.mRight), mTop(rhs.mTop), mBottom(rhs.mBottom),
     mProjMatrix(rhs.mProjMatrix) {
  }
  
  Frustum::~Frustum() {
  }
  
  Frustum& Frustum::operator=(const Frustum &rhs) {
    Box::operator=(rhs);
    if (this != &rhs) {
      mMode = rhs.mMode;
      mFovy = rhs.mFovy;
      mNear = rhs.mNear;
      mFar = rhs.mFar;
      mAspect = rhs.mAspect;
      mFocal = rhs.mFocal;
      mOffsetX = rhs.mOffsetX;
      mOffsetY = rhs.mOffsetY;
      mLeft = rhs.mLeft;
      mRight = rhs.mRight;
      mTop = rhs.mTop;
      mBottom = rhs.mBottom;
      mProjMatrix = rhs.mProjMatrix;
      mCustomMatrix = rhs.mCustomMatrix;
    }
    return *this;
  }
  
  void Frustum::setProjectionMatrix(const Matrix4 &m) {
    mCustomMatrix = true;
    mProjMatrix = m;
    Matrix4 invProj = m.getInverse();
    Vector3 topLeft = invProj * Vector3(-0.5f, 0.5f, 0.0f);
    Vector3 bottomRight = invProj * Vector3(0.5f, -0.5f, 0.0f);
    mLeft = topLeft.x;
    mTop = topLeft.y;
    mRight = bottomRight.x;
    mBottom = bottomRight.y;
    // near and far ?
    dirty();
  }
  
  void Frustum::updateNearRect() const {
    float hf = ToRadian(0.5f * mFovy);
    float tanhfy = Tan(hf);
    float tanhfx = mAspect * tanhfy;
    float nearFocal = (mMode == PM_PERSPECTIVE) ? mNear/mFocal : 0;
    float nearOffX = nearFocal * mOffsetX;
    float nearOffY = nearFocal * mOffsetY;
    float halfw = tanhfx * mNear;
    float halfh = tanhfy * mNear;
    mLeft = nearOffX - halfw;
    mRight = nearOffX + halfw;
    mTop = nearOffY + halfh;
    mBottom = nearOffY - halfh;
  }
  
  void Frustum::updateMatrix() const {
    updateNearRect();
    mProjMatrix = Matrix4::ZERO;
    float invw = 1 / (mRight - mLeft);
    float invh = 1 / (mTop - mBottom);
    float invd = 1 / (mFar - mNear);
    if (mMode == PM_PERSPECTIVE) {
      float A = 2 * mNear * invw;
      float B = 2 * mNear * invh;
      float C = (mRight + mLeft) * invw;
      float D = (mTop + mBottom) * invh;
      float q, qn;
      if (mFar <= 0) {
        // infinite far plane
        // should add epsilon ?
        q = -1;
        qn = -2 * mNear;
      } else {
        q = - (mFar + mNear) * invd;
        qn = -2 * (mFar * mNear) * invd;
      }
      mProjMatrix(0,0) = A;
      mProjMatrix(1,1) = B;
      mProjMatrix(0,2) = C;
      mProjMatrix(1,2) = D;
      mProjMatrix(2,2) = q;
      mProjMatrix(3,2) = -1;
      mProjMatrix(2,3) = qn;
    } else {
      float A = 2 * invw;
      float B = 2 * invh;
      float C = - (mRight + mLeft) * invw;
      float D = - (mTop + mBottom) * invh;
      float q, qn;
      if (mFar <= 0) {
        // should use epsilon ?
        q = 0;
        qn = -1;
      } else {
        q = -2 * invd;
        qn = - (mNear + mFar) * invd;
      }
      mProjMatrix(0,0) = A;
      mProjMatrix(1,1) = B;
      mProjMatrix(2,2) = q;
      mProjMatrix(0,3) = C;
      mProjMatrix(1,3) = D;
      mProjMatrix(2,3) = qn;
      mProjMatrix(3,3) = 1;
    }
  }
  
  void Frustum::updateCorners() const {
    if (!mCustomMatrix) {
      updateMatrix();
    }
    float fplane = (mFar <= 0) ? 100000 : mFar;
    float ratio = (mMode == PM_PERSPECTIVE) ? (fplane / mNear) : 1;
    float fleft = mLeft * ratio;
    float fright = mRight * ratio;
    float ftop = mTop * ratio;
    float fbottom = mBottom * ratio;
    mCorners[CORNER_NEAR|CORNER_TOP|CORNER_LEFT] = Vector3(mLeft, mTop, -mNear);
    mCorners[CORNER_NEAR|CORNER_TOP|CORNER_RIGHT] = Vector3(mRight, mTop, -mNear);
    mCorners[CORNER_NEAR|CORNER_BOTTOM|CORNER_LEFT] = Vector3(mLeft, mBottom, -mNear);
    mCorners[CORNER_NEAR|CORNER_BOTTOM|CORNER_RIGHT] = Vector3(mRight, mBottom, -mNear);
    mCorners[CORNER_FAR|CORNER_TOP|CORNER_LEFT] = Vector3(fleft, ftop, -fplane);
    mCorners[CORNER_FAR|CORNER_TOP|CORNER_RIGHT] = Vector3(fright, ftop, -fplane);
    mCorners[CORNER_FAR|CORNER_BOTTOM|CORNER_LEFT] = Vector3(fleft, fbottom, -fplane);
    mCorners[CORNER_FAR|CORNER_BOTTOM|CORNER_RIGHT] = Vector3(fright, fbottom, -fplane);
  }
  
  Box& Frustum::transform(const Matrix4 &m) {
    unsigned char i;
    for (i=0; i<8; ++i) {
      mCorners[i] = m * getCorner(i);
    }
    for (i=0; i<6; ++i) {
      mPlanes[i] = m * getPlane(i);
    }
    return *this;
  }
  
}

