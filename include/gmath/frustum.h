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
