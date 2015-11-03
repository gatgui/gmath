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

#include <gmath/matrix.h>

namespace gmath {

  const Matrix3 Matrix3::ZERO = Matrix3(0,0,0, 0,0,0, 0,0,0);
  const Matrix3 Matrix3::IDENTITY = Matrix3(1,0,0, 0,1,0, 0,0,1);

  Matrix3 Matrix3::MakeScale(const Vector3 &s) {
    return Matrix3(s.x,0,0, 0,s.y,0, 0,0,s.z);
  }

  Matrix3 Matrix3::MakeRotate(float angle, const Vector3 &a) {
    Matrix3 m;
    angle = ToRadian(angle);
    float ct = Cos(angle);
    float st = Sin(angle);
    float x2 = a.x * a.x;
    float y2 = a.y * a.y;
    float z2 = a.z * a.z;
    float sx = st * a.x;
    float sy = st * a.y;
    float sz = st * a.z;
    float xy = a.x * a.y;
    float xz = a.x * a.z;
    float yz = a.y * a.z;
    float omct = 1.0f - ct;
    m(0,0) = x2 + (1 - x2) * ct;
    m(1,0) = xy * omct    + sz;
    m(2,0) = xz * omct    - sy;
    m(0,1) = xy * omct    - sz;
    m(1,1) = y2 + (1 - y2) * ct;
    m(2,1) = yz * omct    + sx;
    m(0,2) = xz * omct    + sy;
    m(1,2) = yz * omct    - sx;
    m(2,2) = z2 + (1 - z2) * ct;
    return m;
  }

  Matrix3::Matrix3() {
    mM[0][0] = 1.0f;
    mM[0][1] = 0.0f;
    mM[0][2] = 0.0f;
    mM[1][0] = 0.0f;
    mM[1][1] = 1.0f;
    mM[1][2] = 0.0f;
    mM[2][0] = 0.0f;
    mM[2][1] = 0.0f;
    mM[2][2] = 1.0f;
  }

  Matrix3::Matrix3(const Matrix3 &rhs) {
    mM[0][0] = rhs(0,0);
    mM[0][1] = rhs(0,1);
    mM[0][2] = rhs(0,2);
    mM[1][0] = rhs(1,0);
    mM[1][1] = rhs(1,1);
    mM[1][2] = rhs(1,2);
    mM[2][0] = rhs(2,0);
    mM[2][1] = rhs(2,1);
    mM[2][2] = rhs(2,2);
  }

  Matrix3::Matrix3(
    float m00, float m01, float m02,
    float m10, float m11, float m12,
    float m20, float m21, float m22)
  {
    mM[0][0] = m00;
    mM[0][1] = m01;
    mM[0][2] = m02;
    mM[1][0] = m10;
    mM[1][1] = m11;
    mM[1][2] = m12;
    mM[2][0] = m20;
    mM[2][1] = m21;
    mM[2][2] = m22;
  }

  Matrix3::Matrix3(const Vector3 &c0, const Vector3 &c1, const Vector3 &c2) {
    mM[0][0] = c0.x;
    mM[0][1] = c1.x;
    mM[0][2] = c2.x;
    mM[1][0] = c0.y;
    mM[1][1] = c1.y;
    mM[1][2] = c2.y;
    mM[2][0] = c0.z;
    mM[2][1] = c1.z;
    mM[2][2] = c2.z;
  }

  Matrix3::~Matrix3() {
  }

  Matrix3& Matrix3::operator=(const Matrix3 &rhs) {
    if (this != &rhs) {
      mM[0][0] = rhs(0,0);
      mM[0][1] = rhs(0,1);
      mM[0][2] = rhs(0,2);
      mM[1][0] = rhs(1,0);
      mM[1][1] = rhs(1,1);
      mM[1][2] = rhs(1,2);
      mM[2][0] = rhs(2,0);
      mM[2][1] = rhs(2,1);
      mM[2][2] = rhs(2,2);
    }
    return *this;
  }

  Matrix3& Matrix3::operator*=(float s) {
    for (int i=0; i<3; ++i) {
      for (int j=0; j<3; ++j) {
        mM[i][j] *= s;
      }
    }
    return *this;
  }

  Matrix3& Matrix3::operator/=(float s) {
    return operator*=(1.0f / s);
  }

  Matrix3& Matrix3::operator*=(const Matrix3 &rhs) {
    return (*this = (*this * rhs));
  }

  Matrix3& Matrix3::operator+=(const Matrix3 &rhs) {
    for (int i=0; i<3; ++i) {
      for (int j=0; j<3; ++j) {
        mM[i][j] += rhs(i,j);
      }
    }
    return *this;
  }

  Matrix3& Matrix3::operator-=(const Matrix3 &rhs) {
    for (int i=0; i<3; ++i) {
      for (int j=0; j<3; ++j) {
        mM[i][j] -= rhs(i,j);
      }
    }
    return *this;
  }

  float& Matrix3::operator()(int i, int j) {
    return mM[i][j];
  }

  float Matrix3::operator()(int i, int j) const {
    return mM[i][j];
  }

  Vector3 Matrix3::getColumn(int i) const {
    return Vector3(mM[0][i], mM[1][i], mM[2][i]);
  }

  Vector3 Matrix3::getRow(int i) const {
    return Vector3(mM[i][0], mM[i][1], mM[i][2]);
  }

  void Matrix3::setColumn(int i, const Vector3 &col) {
    mM[0][i] = col.x;
    mM[1][i] = col.y;
    mM[2][i] = col.z;
  }

  void Matrix3::setRow(int i, const Vector3 &row) {
    mM[i][0] = row.x;
    mM[i][1] = row.y;
    mM[i][2] = row.z;
  }

  Matrix3& Matrix3::transpose() {
    return (*this = getTranspose());
  }

  Matrix3 Matrix3::getTranspose() const {
    return Matrix3(
      mM[0][0], mM[1][0], mM[2][0],
      mM[0][1], mM[1][1], mM[2][1],
      mM[0][2], mM[1][2], mM[2][2]);
  }

  Matrix3& Matrix3::inverse() {
    return (*this = getInverse());
  }

  Matrix3 Matrix3::getInverse() const {
    return ((1.0f / determinant()) * getAdjoint());
  }

  float Matrix3::determinant() const {
    return (
      mM[0][0] * (mM[1][1]*mM[2][2] - mM[2][1]*mM[1][2]) -
      mM[1][0] * (mM[0][1]*mM[2][2] - mM[2][1]*mM[0][2]) +
      mM[2][0] * (mM[0][1]*mM[1][2] - mM[1][1]*mM[0][2]));
  }

  Matrix3 Matrix3::getAdjoint() const {
    return Matrix3(
       (mM[1][1]*mM[2][2] - mM[2][1]*mM[1][2]),
      -(mM[0][1]*mM[2][2] - mM[2][1]*mM[0][2]),
       (mM[0][1]*mM[1][2] - mM[1][1]*mM[0][2]),
      -(mM[1][0]*mM[2][2] - mM[2][0]*mM[1][2]),
       (mM[0][0]*mM[2][2] - mM[2][0]*mM[0][2]),
      -(mM[0][0]*mM[1][2] - mM[1][0]*mM[0][2]),
       (mM[1][0]*mM[2][1] - mM[2][0]*mM[1][1]),
      -(mM[0][0]*mM[2][1] - mM[2][0]*mM[0][1]),
       (mM[0][0]*mM[1][1] - mM[1][0]*mM[0][1]));
  }

  // ---

  const Matrix4 Matrix4::IDENTITY = Matrix4(1,0,0,0, 0,1,0,0, 0,0,1,0, 0,0,0,1);
  const Matrix4 Matrix4::ZERO = Matrix4(0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0);

  Matrix4 Matrix4::MakeLookAt(const Vector3 &p, const Vector3 &a, const Vector3 &u) {
    Vector3 z = (p - a).normalize();
    Vector3 x = u.cross(z).normalize();
    Vector3 y = z.cross(x).normalize();
    Matrix4 r;
    r.setRow(0, Vector4(x, 0));
    r.setRow(1, Vector4(y, 0));
    r.setRow(2, Vector4(z, 0));
    Matrix4 t = MakeTranslate(-p);
    return (r * t);
  }

  Matrix4 Matrix4::MakeLookIn(const Vector3 &pos, const Vector3 &dir, const Vector3 &up) {
    Vector3 x = dir.cross(up).normalize();
    Vector3 y = x.cross(dir).normalize();
    Matrix4 r;
    r.setRow(0, Vector4(x, -x.dot(pos)));
    r.setRow(1, Vector4(y, -y.dot(pos)));
    r.setRow(2, Vector4(-dir, dir.dot(pos)));
    return r;
  }

  Matrix4 Matrix4::MakeScale(const Vector3 &s) {
    Matrix4 m;
    m(0,0) = s.x;
    m(1,1) = s.y;
    m(2,2) = s.z;
    return m;
  }

  Matrix4 Matrix4::MakeTranslate(const Vector3 &t) {
    Matrix4 m;
    m(0,3) = t.x;
    m(1,3) = t.y;
    m(2,3) = t.z;
    return m;
  }

  Matrix4 Matrix4::MakeRotate(float angle, const Vector3 &a) {
    Matrix4 m;
    angle = ToRadian(angle);
    float ct = Cos(angle);
    float st = Sin(angle);
    float x2 = a.x * a.x;
    float y2 = a.y * a.y;
    float z2 = a.z * a.z;
    float sx = st * a.x;
    float sy = st * a.y;
    float sz = st * a.z;
    float xy = a.x * a.y;
    float xz = a.x * a.z;
    float yz = a.y * a.z;
    float omct = 1.0f - ct;
    m(0,0) = x2 + (1 - x2) * ct;
    m(1,0) = xy * omct    + sz;
    m(2,0) = xz * omct    - sy;
    m(0,1) = xy * omct    - sz;
    m(1,1) = y2 + (1 - y2) * ct;
    m(2,1) = yz * omct    + sx;
    m(0,2) = xz * omct    + sy;
    m(1,2) = yz * omct    - sx;
    m(2,2) = z2 + (1 - z2) * ct;
    return m;
  }

  Matrix4 Matrix4::MakeFrustum(float l, float r, float b, float t, float n, float f) {
    Matrix4 m = Matrix4::ZERO;
    float iw = 1.0f / (r - l);
    float ih = 1.0f / (t - b);
    float id = 1.0f / (f - n);
    m(0,0) = 2.0f * n * iw;
    m(0,2) = (r + l) * iw;
    m(1,1) = 2.0f * n * ih;
    m(1,2) = (t + b) * ih;
    //m(2,2) = (n + f) * id;
    m(2,2) = -(n + f) * id;
    m(2,3) = -2.0f * n * f * id;
    m(3,2) = -1;
    return m;
  }

  Matrix4 Matrix4::MakeOrtho(float l, float r, float b, float t, float n, float f) {
    Matrix4 m;
    float iw = 1.0f / (r - l);
    float ih = 1.0f / (t - b);
    float id = 1.0f / (f - n);
    m(0,0) = 2.0f * iw;
    m(1,1) = 2.0f * ih;
    //m(2,2) = 2.0f * id;
    m(2,2) = -2.0f * id;
    m(0,3) = - (r + l) * iw;
    m(1,3) = - (t + b) * ih;
    m(2,3) = - (f + n) * id;
    return m;
  }

  Matrix4 Matrix4::MakePerspective(float fovy, float aspect, float n, float f) {
    Matrix4 m = Matrix4::ZERO;
    float chf = Cotand(0.5f * fovy);
    float id = 1.0f / (n - f);
    m(0,0) = chf / aspect;
    m(1,1) = chf;
    m(2,2) = (n + f) * id;
    m(2,3) = 2.0f * n * f * id;
    m(3,2) = -1;
    return m;
  }

  Matrix4::Matrix4() {
    memset(mM, 0, 16*sizeof(float));
    mM[0] = mM[5] = mM[10] = mM[15] = 1.0f;
  }

  Matrix4::Matrix4(const Matrix4 &rhs) {
    memcpy(mM, rhs.mM, 16*sizeof(float));
  }

  Matrix4::Matrix4(
    float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
  {
    mM[0] = m00; mM[4] = m01; mM[8]  = m02; mM[12] = m03;
    mM[1] = m10; mM[5] = m11; mM[9]  = m12; mM[13] = m13;
    mM[2] = m20; mM[6] = m21; mM[10] = m22; mM[14] = m23;
    mM[3] = m30; mM[7] = m31; mM[11] = m32; mM[15] = m33;
  }

  Matrix4& Matrix4::operator=(const Matrix4 &rhs) {
    if (this != &rhs) {
      memcpy(mM, rhs.mM, 16*sizeof(float));
    }
    return *this;
  }

  Vector4 Matrix4::getColumn(int i) const {
    i = i << 2;
    return Vector4(mM[i], mM[i+1], mM[i+2], mM[i+3]);
  }

  Vector4 Matrix4::getRow(int i) const {
    return Vector4(mM[i], mM[i+4], mM[i+8], mM[i+12]);
  }

  void Matrix4::setColumn(int i, const Vector4 &c) {
    i = i << 2;
    mM[i] = c.x;
    mM[i+1] = c.y;
    mM[i+2] = c.z;
    mM[i+3] = c.w;
  }

  void Matrix4::setRow(int i, const Vector4 &r) {
    mM[i] = r.x;
    mM[i+4] = r.y;
    mM[i+8] = r.z;
    mM[i+12] = r.w;
  }

  Matrix4& Matrix4::operator*=(float s) {
    for (int i=0; i<16; ++i) {
      mM[i] *= s;
    }
    return *this;
  }

  Matrix4& Matrix4::operator*=(const Matrix4 &rhs) {
    return (*this = (*this * rhs));
  }

  Matrix4& Matrix4::operator/=(float s) {
    for (int i=0; i<16; ++i) {
      mM[i] /= s;
    }
    return *this;
  }

  Matrix4& Matrix4::operator+=(const Matrix4 &rhs) {
    for (int i=0; i<16; ++i) {
      mM[i] += rhs.mM[i];
    }
    return *this;
  }

  Matrix4& Matrix4::operator-=(const Matrix4 &rhs) {
    for (int i=0; i<16; ++i) {
      mM[i] -= rhs.mM[i];
    }
    return *this;
  }

  Matrix4& Matrix4::transpose() {
    return (*this = getTranspose());
  }

  Matrix4 Matrix4::getTranspose() const {
    Matrix4 r;
    r[0] = mM[0];
    r[1] = mM[4];
    r[2] = mM[8];
    r[3] = mM[12];
    r[4] = mM[1];
    r[5] = mM[5];
    r[6] = mM[9];
    r[7] = mM[13];
    r[8] = mM[2];
    r[9] = mM[6];
    r[10] = mM[10];
    r[11] = mM[14];
    r[12] = mM[3];
    r[13] = mM[7];
    r[14] = mM[11];
    r[15] = mM[15];
    return r;
  }

  inline static float Minor(
    const Matrix4& m,
    int i00, int i01, int i02,
    int i10, int i11, int i12,
    int i20, int i21, int i22)
  {
    return m[i00] * ( m[i11] * m[i22] - m[i21] * m[i12] ) -
           m[i01] * ( m[i10] * m[i22] - m[i20] * m[i12] ) +
           m[i02] * ( m[i10] * m[i21] - m[i20] * m[i11] );
  }

  Matrix4 Matrix4::getAdjoint() const {
    return Matrix4(

       Minor(*this, 5,9,13, 6,10,14, 7,11,15),
      -Minor(*this, 4,8,12, 6,10,14, 7,11,15),
       Minor(*this, 4,8,12, 5,9,13,  7,11,15),
      -Minor(*this, 4,8,12, 5,9,13,  6,10,14),

      -Minor(*this, 1,9,13, 2,10,14, 3,11,15),
       Minor(*this, 0,8,12, 2,10,14, 3,11,15),
      -Minor(*this, 0,8,12, 1,9,13,  3,11,15),
       Minor(*this, 0,8,12, 1,9,13,  2,10,14),

       Minor(*this, 1,5,13, 2,6,14, 3,7,15),
      -Minor(*this, 0,4,12, 2,6,14, 3,7,15),
       Minor(*this, 0,4,12, 1,5,13, 3,7,15),
      -Minor(*this, 0,4,12, 1,5,13, 2,6,14),

      -Minor(*this, 1,5,9, 2,6,10, 3,7,11),
       Minor(*this, 0,4,8, 2,6,10, 3,7,11),
      -Minor(*this, 0,4,8, 1,5,9,  3,7,11),
       Minor(*this, 0,4,8, 1,5,9,  2,6,10));
  }

  float Matrix4::determinant() const {
    return mM[0]  * Minor(*this, 5,9,13, 6,10,14, 7,11,15) -
           mM[4]  * Minor(*this, 1,9,13, 2,10,14, 3,11,15) +
           mM[8]  * Minor(*this, 1,5,13, 2,6,13,  3,7,15) -
           mM[12] * Minor(*this, 1,5,9,  2,6,10,  3,7,11);
  }

  Matrix4& Matrix4::inverse() {
    return (*this = getInverse());
  }

  Matrix4 Matrix4::getInverse() const {

    //return ((1.0f / determinant()) * getAdjoint());

    float m00 =  Minor(*this, 5,9,13, 6,10,14, 7,11,15);
    float m01 = -Minor(*this, 4,8,12, 6,10,14, 7,11,15);
    float m02 =  Minor(*this, 4,8,12, 5,9,13,  7,11,15);
    float m03 = -Minor(*this, 4,8,12, 5,9,13,  6,10,14);

    float m10 = -Minor(*this, 1,9,13, 2,10,14, 3,11,15);
    float m11 =  Minor(*this, 0,8,12, 2,10,14, 3,11,15);
    float m12 = -Minor(*this, 0,8,12, 1,9,13,  3,11,15);
    float m13 =  Minor(*this, 0,8,12, 1,9,13,  2,10,14);

    float m20 =  Minor(*this, 1,5,13, 2,6,14, 3,7,15);
    float m21 = -Minor(*this, 0,4,12, 2,6,14, 3,7,15);
    float m22 =  Minor(*this, 0,4,12, 1,5,13, 3,7,15);
    float m23 = -Minor(*this, 0,4,12, 1,5,13, 2,6,14);

    float m30 = -Minor(*this, 1,5,9, 2,6,10, 3,7,11);
    float m31 =  Minor(*this, 0,4,8, 2,6,10, 3,7,11);
    float m32 = -Minor(*this, 0,4,8, 1,5,9,  3,7,11);
    float m33 =  Minor(*this, 0,4,8, 1,5,9,  2,6,10);

    float idet = 1.0f / (mM[0]*m00 - mM[4]*m10 + mM[8]*m20 - mM[12]*m30);

    return Matrix4(
      idet*m00, idet*m01, idet*m02, idet*m03,
      idet*m10, idet*m11, idet*m12, idet*m13,
      idet*m20, idet*m21, idet*m22, idet*m23,
      idet*m30, idet*m31, idet*m32, idet*m33);
  }

  Matrix4& Matrix4::fastInverse() {
    return (*this = getFastInverse());
  }

  Matrix4 Matrix4::getFastInverse() const {
    Matrix4 r;
    r[0] = mM[0];
    r[1] = mM[4];
    r[2] = mM[8];
    r[3] = 0.0f;
    r[4] = mM[1];
    r[5] = mM[5];
    r[6] = mM[9];
    r[7] = 0.0f;
    r[8] = mM[2];
    r[9] = mM[6];
    r[10] = mM[10];
    r[11] = 0.0f;
    r[12] = - (mM[0]*mM[12] + mM[1]*mM[13] + mM[2]*mM[14]);
    r[13] = - (mM[4]*mM[12] + mM[5]*mM[13] + mM[6]*mM[14]);
    r[14] = - (mM[8]*mM[12] + mM[9]*mM[13] + mM[10]*mM[14]);
    r[15] = 1.0f;
    return r;
  }

  float& Matrix4::operator()(int i, int j) {
    return mM[i+(j<<2)];
  }

  float Matrix4::operator()(int i, int j) const {
    return mM[i+(j<<2)];
  }

}

// ---

gmath::Matrix3 operator*(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1) {
  gmath::Matrix3 tmp;
  tmp(0,0) = m0(0,0)*m1(0,0) + m0(0,1)*m1(1,0) + m0(0,2)*m1(2,0);
  tmp(0,1) = m0(0,0)*m1(0,1) + m0(0,1)*m1(1,1) + m0(0,2)*m1(2,1);
  tmp(0,2) = m0(0,0)*m1(0,2) + m0(0,1)*m1(1,2) + m0(0,2)*m1(2,2);
  tmp(1,0) = m0(1,0)*m1(0,0) + m0(1,1)*m1(1,0) + m0(1,2)*m1(2,0);
  tmp(1,1) = m0(1,0)*m1(0,1) + m0(1,1)*m1(1,1) + m0(1,2)*m1(2,1);
  tmp(1,2) = m0(1,0)*m1(0,2) + m0(1,1)*m1(1,2) + m0(1,2)*m1(2,2);
  tmp(2,0) = m0(2,0)*m1(0,0) + m0(2,1)*m1(1,0) + m0(2,2)*m1(2,0);
  tmp(2,1) = m0(2,0)*m1(0,1) + m0(2,1)*m1(1,1) + m0(2,2)*m1(2,1);
  tmp(2,2) = m0(2,0)*m1(0,2) + m0(2,1)*m1(1,2) + m0(2,2)*m1(2,2);
  return tmp;
}

gmath::Matrix3 operator+(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1) {
  gmath::Matrix3 tmp(m0);
  return (tmp += m1);
}

gmath::Matrix3 operator-(const gmath::Matrix3 &m0, const gmath::Matrix3 &m1) {
  gmath::Matrix3 tmp(m0);
  return (tmp -= m1);
}

gmath::Matrix3 operator*(const gmath::Matrix3 &m0, float s) {
  gmath::Matrix3 tmp(m0);
  return (tmp *= s);
}

gmath::Vector3 operator*(const gmath::Matrix3 &m, const gmath::Vector3 &v) {
  return gmath::Vector3(
    (v.x*m(0,0) + v.y*m(0,1) + v.z*m(0,2)),
    (v.x*m(1,0) + v.y*m(1,1) + v.z*m(1,2)),
    (v.x*m(2,0) + v.y*m(2,1) + v.z*m(2,2)));
}

gmath::Vector3 operator*(const gmath::Vector3 &v, const gmath::Matrix3 &m) {
  return gmath::Vector3(
    (v.x*m(0,0) + v.y*m(1,0) + v.z*m(2,0)),
    (v.x*m(0,1) + v.y*m(1,1) + v.z*m(2,1)),
    (v.x*m(0,2) + v.y*m(1,2) + v.z*m(2,2)));
}

gmath::Matrix3 operator*(float s, const gmath::Matrix3 &m0) {
  gmath::Matrix3 tmp(m0);
  return (tmp *= s);
}

gmath::Matrix3 operator/(const gmath::Matrix3 &m0, float s) {
  gmath::Matrix3 tmp(m0);
  return (tmp /= s);
}

std::ostream& operator<<(std::ostream &os, const gmath::Matrix3 &m) {
  os << "Matrix3{";
  os << "{" << m(0,0) << ", " << m(0,1) << ", " << m(0,2) << "}, ";
  os << "{" << m(1,0) << ", " << m(1,1) << ", " << m(1,2) << "}, ";
  os << "{" << m(2,0) << ", " << m(2,1) << ", " << m(2,2) << "}}";
  return os;
}

// ---

gmath::Matrix4 operator+(const gmath::Matrix4 &m0, const gmath::Matrix4 &m1) {
  gmath::Matrix4 tmp(m0);
  return (tmp += m1);
}

gmath::Matrix4 operator-(const gmath::Matrix4 &m0, const gmath::Matrix4 &m1) {
  gmath::Matrix4 tmp(m0);
  return (tmp -= m1);
}

gmath::Matrix4 operator*(const gmath::Matrix4 &m, const gmath::Matrix4 &rhs) {
  gmath::Matrix4 tmp;
  tmp[0]  = m[0]*rhs[0]  + m[4]*rhs[1]  + m[8]*rhs[2]   + m[12]*rhs[3];
  tmp[1]  = m[1]*rhs[0]  + m[5]*rhs[1]  + m[9]*rhs[2]   + m[13]*rhs[3];
  tmp[2]  = m[2]*rhs[0]  + m[6]*rhs[1]  + m[10]*rhs[2]  + m[14]*rhs[3];
  tmp[3]  = m[3]*rhs[0]  + m[7]*rhs[1]  + m[11]*rhs[2]  + m[15]*rhs[3];
  tmp[4]  = m[0]*rhs[4]  + m[4]*rhs[5]  + m[8]*rhs[6]   + m[12]*rhs[7];
  tmp[5]  = m[1]*rhs[4]  + m[5]*rhs[5]  + m[9]*rhs[6]   + m[13]*rhs[7];
  tmp[6]  = m[2]*rhs[4]  + m[6]*rhs[5]  + m[10]*rhs[6]  + m[14]*rhs[7];
  tmp[7]  = m[3]*rhs[4]  + m[7]*rhs[5]  + m[11]*rhs[6]  + m[15]*rhs[7];
  tmp[8]  = m[0]*rhs[8]  + m[4]*rhs[9]  + m[8]*rhs[10]  + m[12]*rhs[11];
  tmp[9]  = m[1]*rhs[8]  + m[5]*rhs[9]  + m[9]*rhs[10]  + m[13]*rhs[11];
  tmp[10] = m[2]*rhs[8]  + m[6]*rhs[9]  + m[10]*rhs[10] + m[14]*rhs[11];
  tmp[11] = m[3]*rhs[8]  + m[7]*rhs[9]  + m[11]*rhs[10] + m[15]*rhs[11];
  tmp[12] = m[0]*rhs[12] + m[4]*rhs[13] + m[8]*rhs[14]  + m[12]*rhs[15];
  tmp[13] = m[1]*rhs[12] + m[5]*rhs[13] + m[9]*rhs[14]  + m[13]*rhs[15];
  tmp[14] = m[2]*rhs[12] + m[6]*rhs[13] + m[10]*rhs[14] + m[14]*rhs[15];
  tmp[15] = m[3]*rhs[12] + m[7]*rhs[13] + m[11]*rhs[14] + m[15]*rhs[15];
  return tmp;
}

gmath::Matrix4 operator*(const gmath::Matrix4 &m0, float s) {
  gmath::Matrix4 tmp(m0);
  return (tmp *= s);
}

gmath::Matrix4 operator*(float s, const gmath::Matrix4 &m0) {
  gmath::Matrix4 tmp(m0);
  return (tmp *= s);
}

gmath::Matrix4 operator/(const gmath::Matrix4 &m0, float s) {
  gmath::Matrix4 tmp(m0);
  return (tmp /= s);
}

gmath::Vector3 operator*(const gmath::Matrix4 &m, const gmath::Vector3 &v) {
  float invw = 1.0f / (m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]);
  return gmath::Vector3(
    invw * (m[0]*v.x + m[4]*v.y + m[8]*v.z + m[12]),
    invw * (m[1]*v.x + m[5]*v.y + m[9]*v.z + m[13]),
    invw * (m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]));
}

gmath::Vector3 operator*(const gmath::Vector3 &v, const gmath::Matrix4 &m) {
  float invw = 1.0f / (m[12]*v.x + m[13]*v.y + m[14]*v.z + m[15]);
  return gmath::Vector3(
    invw * (m[0]*v.x + m[1]*v.y + m[2]*v.z + m[3]),
    invw * (m[4]*v.x + m[5]*v.y + m[6]*v.z + m[7]),
    invw * (m[8]*v.x + m[9]*v.y + m[10]*v.z + m[11]));
}

gmath::Vector4 operator*(const gmath::Matrix4 &m, const gmath::Vector4 &v) {
  gmath::Vector4 tmp;
  tmp.x = m[0]*v.x + m[4]*v.y + m[8]*v.z  + m[12]*v.w;
  tmp.y = m[1]*v.x + m[5]*v.y + m[9]*v.z  + m[13]*v.w;
  tmp.z = m[2]*v.x + m[6]*v.y + m[10]*v.z + m[14]*v.w;
  tmp.w = m[3]*v.x + m[7]*v.y + m[11]*v.z + m[15]*v.w;
  return tmp;
}

gmath::Vector4 operator*(const gmath::Vector4 &v, const gmath::Matrix4 &m) {
  gmath::Vector4 tmp;
  tmp.x = m[0]*v.x  + m[1]*v.y  + m[2]*v.z  + m[3]*v.w;
  tmp.y = m[4]*v.x  + m[5]*v.y  + m[6]*v.z  + m[7]*v.w;
  tmp.z = m[8]*v.x  + m[9]*v.y  + m[10]*v.z + m[11]*v.w;
  tmp.w = m[12]*v.x + m[13]*v.y + m[14]*v.z + m[15]*v.w;
  return tmp;
}

std::ostream& operator<<(std::ostream &os, const gmath::Matrix4 &m) {
  os << "Matrix4{";
  os << "{" << m[0] << ", " << m[4] << ", " << m[8] << ", " << m[12] << "}, ";
  os << "{" << m[1] << ", " << m[5] << ", " << m[9] << ", " << m[13] << "}, ";
  os << "{" << m[2] << ", " << m[6] << ", " << m[10] << ", " << m[14] << "}, ";
  os << "{" << m[3] << ", " << m[7] << ", " << m[11] << ", " << m[15] << "}}";
  return os;
}
