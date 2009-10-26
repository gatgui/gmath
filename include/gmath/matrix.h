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

#ifndef __gmath_matrix_h_
#define __gmath_matrix_h_

#include <gmath/vector.h>

namespace gmath {

  class GMATH_API Matrix3 {
    public:
      
      static const Matrix3 ZERO;
      static const Matrix3 IDENTITY;
  
      Matrix3();
      Matrix3(const Matrix3 &rhs);
      Matrix3(
        float m00, float m01, float m02,
        float m10, float m11, float m12,
        float m20, float m21, float m22);
      Matrix3(const Vector3 &c0, const Vector3 &c1, const Vector3 &c2);
      ~Matrix3();
      
      Matrix3& operator=(const Matrix3 &rhs);
      Matrix3& operator*=(float s);
      Matrix3& operator/=(float s);
      Matrix3& operator*=(const Matrix3 &rhs);
      Matrix3& operator+=(const Matrix3 &rhs);
      Matrix3& operator-=(const Matrix3 &rhs);
      float& operator()(int i, int j);
      float operator()(int i, int j) const;
      
      Vector3 getColumn(int i) const;
      Vector3 getRow(int i) const;
      void setColumn(int i, const Vector3 &col);
      void setRow(int i, const Vector3 &row);
      
      Matrix3& transpose();
      Matrix3 getTranspose() const;
      
      Matrix3& inverse();
      Matrix3 getInverse() const;
      float determinant() const;
      Matrix3 getAdjoint() const;
      
      static Matrix3 MakeScale(const Vector3 &s);
      static Matrix3 MakeRotate(float angle, const Vector3 &axis);
      
    protected:
      
      float mM[3][3];
  };
  
  
  class GMATH_API Matrix4 {
    public:
      
      static const Matrix4 IDENTITY;
      static const Matrix4 ZERO;
      
      Matrix4();
      Matrix4(const Matrix4 &rhs);
      Matrix4(
        float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);
      
      Matrix4& operator=(const Matrix4 &rhs);
      
      Vector4 getColumn(int i) const;
      Vector4 getRow(int i) const;
      void setColumn(int i, const Vector4 &c);
      void setRow(int i, const Vector4 &r);
      
      Matrix4& transpose();
      Matrix4 getTranspose() const;
      
      Matrix4& fastInverse();
      Matrix4 getFastInverse() const;
      
      Matrix4& inverse();
      Matrix4 getAdjoint() const;
      float determinant() const;
      Matrix4 getInverse() const;
      
      Matrix4& operator*=(float s);
      Matrix4& operator/=(float s);
      Matrix4& operator*=(const Matrix4 &rhs);
      Matrix4& operator+=(const Matrix4 &rhs);
      Matrix4& operator-=(const Matrix4 &rhs);
      
      float& operator()(int i, int j);
      float operator()(int i, int j) const;
      
      inline operator const float* () const {
        return mM;
      }
      inline operator float* () {
        return mM;
      }
      
      static Matrix4 MakeScale(const Vector3 &s);
      static Matrix4 MakeTranslate(const Vector3 &t);
      static Matrix4 MakeRotate(float angle, const Vector3 &axis);
      static Matrix4 MakeLookAt(const Vector3 &pos, const Vector3 &aim, const Vector3 &up);
      static Matrix4 MakeLookIn(const Vector3 &pos, const Vector3 &dir, const Vector3 &up);
      static Matrix4 MakeFrustum(float l, float r, float b, float t, float n, float f);
      static Matrix4 MakeOrtho(float l, float r, float b, float t, float n, float f);
      static Matrix4 MakePerspective(float fovy, float aspect, float n, float f);
  
    protected:
      
      float mM[16];
  };

}

GMATH_API gmath::Matrix3 operator*(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1);
GMATH_API gmath::Matrix3 operator+(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1);
GMATH_API gmath::Matrix3 operator-(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1);
GMATH_API gmath::Matrix3 operator*(const gmath::Matrix3 &m0, float s);
GMATH_API gmath::Vector3 operator*(const gmath::Matrix3 &m, const gmath::Vector3 &v);
GMATH_API gmath::Vector3 operator*(const gmath::Vector3 &v, const gmath::Matrix3 &m);
GMATH_API gmath::Matrix3 operator*(float s, const gmath::Matrix3 &m0);
GMATH_API gmath::Matrix3 operator/(const gmath::Matrix3 &m0, float s);
GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::Matrix3 &m);

GMATH_API gmath::Matrix4 operator*(const gmath::Matrix4 &m0, const gmath::Matrix4 &m1);
GMATH_API gmath::Matrix4 operator+(const gmath::Matrix4 &m0, const gmath::Matrix4 &m1);
GMATH_API gmath::Matrix4 operator-(const gmath::Matrix4 &m0, const gmath::Matrix4 &m1);
GMATH_API gmath::Matrix4 operator*(const gmath::Matrix4 &m0, float s);
GMATH_API gmath::Vector4 operator*(const gmath::Matrix4 &m, const gmath::Vector4 &v);
GMATH_API gmath::Vector4 operator*(const gmath::Vector4 &v, const gmath::Matrix4 &m);
GMATH_API gmath::Vector3 operator*(const gmath::Matrix4 &m, const gmath::Vector3 &v);
GMATH_API gmath::Vector3 operator*(const gmath::Vector3 &v, const gmath::Matrix4 &m);
GMATH_API gmath::Matrix4 operator*(float s, const gmath::Matrix4 &m0);
GMATH_API gmath::Matrix4 operator/(const gmath::Matrix4 &m0, float s);
GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::Matrix4 &m);

#endif

