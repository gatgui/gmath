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

#ifndef __gmath_frustum_h_
#define __gmath_frustum_h_

#include <gmath/box.h>

namespace gmath {
  
  enum ProjectionMode {
    PM_ORTHOGRAPHIC = 0,
    PM_PERSPECTIVE,
    PM_MAX
  };
  
  class GMATH_API Frustum : public Box {
    public:
  
      enum {
        PLANE_NEAR = PLANE_FRONT,
        PLANE_FAR = PLANE_BACK
      };
      
      enum {
        CORNER_NEAR = CORNER_FRONT,
        CORNER_FAR = CORNER_BACK
      };
      
      Frustum();
      Frustum(ProjectionMode mode, float fovy, float asp, float np, float fp);
      Frustum(const Frustum &rhs);
      virtual ~Frustum();
      
      Frustum& operator=(const Frustum &rhs);
      
      virtual Box& transform(const Matrix4 &m);
      
      void setProjectionMatrix(const Matrix4 &m);
      
      inline void setMode(ProjectionMode pm) {
        mMode = pm;
        mCustomMatrix = false;
        dirty();
      }

      inline void setFocalLength(float fl) {
        mFocal = fl;
        mCustomMatrix = false;
        dirty();
      }

      inline void setOffset(float x, float y) {
        mOffsetX = x;
        mOffsetY = y;
        mCustomMatrix = false;
        dirty();
      }

      inline void setNearClip(float nplane) {
        mNear = nplane;
        mCustomMatrix = false;
        dirty();
      }

      inline void setFarClip(float fplane) {
        mFar = fplane;
        mCustomMatrix = false;
        dirty();
      }

      inline void setFovy(float fovy) {
        mFovy = fovy;
        mCustomMatrix = false;
        dirty();
      }

      inline void setAspect(float asp) {
        mAspect = asp;
        mCustomMatrix = false;
        dirty();
      }
      
      inline float getFovy() const {
        return mFovy;
      }
      
      inline float getAspect() const {
        return mAspect;
      }
      
      inline float getNearClip() const {
        return mNear;
      }
      
      inline float getFarClip() const {
        return mFar;
      }
      
      inline void getOffset(float &x, float &y) const {
        x = mOffsetX;
        y = mOffsetY;
      }
      
      inline float getFocalLength() const {
        return mFocal;
      }
      
      inline ProjectionMode getMode() const {
        return mMode;
      }
      
      inline const Matrix4& getProjectionMatrix() const {
        if (!mCustomMatrix && mDirty) {
          update();
        }
        return mProjMatrix;
      }
      
    protected:
      
      void updateNearRect() const;
      void updateMatrix() const;
      virtual void updateCorners() const;
      
      float mFovy;
      float mAspect;
      float mNear;
      float mFar;
      ProjectionMode mMode;
      float mFocal;
      float mOffsetX;
      float mOffsetY;
      
      bool mCustomMatrix;
      
      mutable float mLeft;
      mutable float mRight;
      mutable float mTop;
      mutable float mBottom;
      mutable Matrix4 mProjMatrix;
  };
  
  
}

inline gmath::Frustum operator*(const gmath::Matrix4 &m, const gmath::Frustum &f) {
  gmath::Frustum tmp(f);
  tmp.transform(m);
  return tmp;
}


#endif
