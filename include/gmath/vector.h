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

#ifndef __gmath_vector_h_
#define __gmath_vector_h_

#include <gmath/config.h>

namespace gmath {
  
  class GMATH_API Vector2 {
    public:
      
      float x;
      float y;
      
      inline Vector2() {
      }
      inline explicit Vector2(float v) :x(v), y(v) {
      }
      inline explicit Vector2(float a, float b) :x(a), y(b) {
      }
      inline explicit Vector2(const float *v) :x(v[0]), y(v[1]) {
      }
      inline Vector2(const Vector2 &rhs) :x(rhs.x), y(rhs.y) {
      }
      inline ~Vector2() {
      }
      
      inline Vector2& operator=(const Vector2 &rhs) {
        if (this != &rhs) {
          x = rhs.x;
          y = rhs.y;
        }
        return *this;
      }
      
      inline bool equals(const Vector2 &rhs) const {
        return (Abs(x-rhs.x) < EPS6 && Abs(y-rhs.y)<EPS6);
      }
      inline Vector2 getOrtho() const {
        return Vector2(-y, x);
      }
      inline float dot(const Vector2 &rhs) const {
        return ((x * rhs.x) + (y * rhs.y));
      }
      inline float getSquaredLength() const {
        return dot(*this);
      } 
      inline float getLength() const {
        return Sqrt(getSquaredLength());
      }
      Vector2& normalize() {
        float l = getLength();
        if (l > EPS6) {
          l = 1.0f / l;
          x *= l;
          y *= l;
        }
        return *this;
      }
      Vector2& floor(const Vector2 &rhs) {
        x = (x > rhs.x) ? rhs.x : x;
        y = (y > rhs.y) ? rhs.y : y;
        return *this;
      }
      Vector2& ceil(const Vector2 &rhs) {
        x = (x < rhs.x) ? rhs.x : x;
        y = (y < rhs.y) ? rhs.y : y;
        return *this;
      }
      
      inline Vector2& operator+=(const Vector2 &rhs) {
        x += rhs.x;
        y += rhs.y;
        return *this;
      }
      inline Vector2& operator-=(const Vector2 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
      }
      inline Vector2& operator*=(const Vector2 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
      }
      inline Vector2& operator/=(const Vector2 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
      }
      inline Vector2& operator*=(float s) {
        x *= s;
        y *= s;
        return *this;
      }
      inline Vector2& operator/=(float s) {
        x /= s;
        y /= s;
        return *this;
      }
      inline Vector2 operator-() const {
        return Vector2(-x, -y);
      }
      inline bool operator==(const Vector2 &rhs) const {
        return equals(rhs);
      }
      inline bool operator!=(const Vector2 &rhs) const {
        return !operator==(rhs);
      }
      inline bool operator<(const Vector2 &rhs) const {
        return (x<rhs.x && y<rhs.y);
      }
      inline bool operator<=(const Vector2 &rhs) const {
        return (x<=rhs.x && y<=rhs.y);
      }
      inline bool operator>(const Vector2 &rhs) const {
        return (x>rhs.x && y>rhs.y);
      }
      inline bool operator>=(const Vector2 &rhs) const {
        return (x>=rhs.x && y>=rhs.y);
      }
      
      inline operator const float* () const {
        return (&(this->x));
      }
      inline operator float* () {
        return (&(this->x));
      }
      
      static const Vector2 ZERO;
      static const Vector2 UNIT_X;
      static const Vector2 UNIT_Y;
  };
  
  class GMATH_API Vector3 {
    public:
  
      float x;
      float y;
      float z;
      
      inline Vector3()
        :x(0), y(0), z(0) {  
      }
      inline explicit Vector3(float v)
        :x(v), y(v), z(v) {
      }
      inline explicit Vector3(float a, float b, float c)
        :x(a), y(b), z(c) {
      }
      inline explicit Vector3(const float *v)
        :x(v[0]), y(v[1]), z(v[2]) {
      }
      inline Vector3(const Vector3 &rhs)
        :x(rhs.x), y(rhs.y), z(rhs.z) {
      }
      inline ~Vector3() {
      }
      
      inline Vector3& operator=(const Vector3 &rhs) {
        if (this != &rhs) {
          x = rhs.x;
          y = rhs.y;
          z = rhs.z;
        }
        return *this;
      }
      
      inline bool equals(const Vector3 &rhs) const {
        return (
          (Abs(x-rhs.x) < EPS6) &&
          (Abs(y-rhs.y) < EPS6) &&
          (Abs(z-rhs.z) < EPS6));
      }
      inline bool dirEquals(const Vector3 &rhs, float angularTolerance) const {
        float d = dot(rhs);
        float a = ToDegree(Acos(d));
        return (Abs(a) <= angularTolerance);
      }
      inline Vector3 cross(const Vector3 &rhs) const {
        Vector3 r;
        r.x = (y * rhs.z) - (z * rhs.y);
        r.y = (z * rhs.x) - (x * rhs.z);
        r.z = (x * rhs.y) - (y * rhs.x);
        return r;
      }
      inline float dot(const Vector3 &rhs) const {
        return ((x*rhs.x) + (y*rhs.y) + (z*rhs.z));
      }
      inline float getSquaredLength() const {
        return dot(*this);
      }
      inline float getLength() const {
        return Sqrt(getSquaredLength());
      }
      inline Vector3& normalize() {
        float l = getLength();
        if (l > EPS6) {
          l = 1.0f / l;
          x *= l;
          y *= l;
          z *= l;
        }
        return *this;
      }
      // -> read as minimum of two
      inline Vector3& floor(const Vector3 &rhs) {
        x = (x > rhs.x) ? rhs.x : x;
        y = (y > rhs.y) ? rhs.y : y;
        z = (z > rhs.z) ? rhs.z : z;
        return *this;
      }
      // -> read as maximum of two
      inline Vector3& ceil(const Vector3 &rhs) {
        x = (x < rhs.x) ? rhs.x : x;
        y = (y < rhs.y) ? rhs.y : y;
        z = (z < rhs.z) ? rhs.z : z;
        return *this;
      }
      
      inline Vector3& operator+=(const Vector3 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
      }
      inline Vector3& operator-=(const Vector3 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
      }
      inline Vector3& operator*=(const Vector3 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
      }
      inline Vector3& operator/=(const Vector3 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
      }
      inline Vector3& operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        return *this;
      }
      inline Vector3& operator/=(float s) {
        x /= s;
        y /= s;
        z /= s;
        return *this;
      }
      inline Vector3 operator-() const {
        return Vector3(-x, -y, -z);
      }
      inline bool operator==(const Vector3 &rhs) const {
        return equals(rhs);
      }
      inline bool operator!=(const Vector3 &rhs) const {
        return !operator==(rhs);
      }
      inline bool operator<(const Vector3 &rhs) const {
        return (x<rhs.x && y<rhs.y && z<rhs.z);
      }
      inline bool operator<=(const Vector3 &rhs) const {
        return (x<=rhs.x && y<=rhs.y && z<=rhs.z);
      }
      inline bool operator>(const Vector3 &rhs) const {
        return (x>rhs.x && y>rhs.y && z>rhs.z);
      }
      inline bool operator>=(const Vector3 &rhs) const {
        return (x>=rhs.x && y>=rhs.y && z>=rhs.z);
      }
      
      inline operator const float* () const {
        return (&(this->x));
      }
      inline operator float* () {
        return (&(this->x));
      }
      
      static const Vector3 ZERO;
      static const Vector3 UNIT_X;
      static const Vector3 UNIT_Y;
      static const Vector3 UNIT_Z;
      static const Vector3 NEG_UNIT_X;
      static const Vector3 NEG_UNIT_Y;
      static const Vector3 NEG_UNIT_Z;
      static const Vector3 UNIT_SCALE;
  };
  
  class GMATH_API Vector4 {
    public:
      
      float x;
      float y;
      float z;
      float w;
      
      inline Vector4()
        :x(0), y(0), z(0), w(0) {
      }
      inline explicit Vector4(float v)
        :x(v), y(v), z(v), w(v) {
      }
      inline explicit Vector4(const float *v)
        :x(v[0]), y(v[1]), z(v[2]), w(v[3]) {
      }
      inline explicit Vector4(const Vector3 &v3, float v=1.0f)
        :x(v3.x), y(v3.y), z(v3.z), w(v) {
      }
      inline explicit Vector4(float a, float b, float c, float d=1.0f)
        :x(a), y(b), z(c), w(d) {
      }
      inline Vector4(const Vector4 &rhs)
        :x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {
      }
      inline ~Vector4() {
      }
      
      inline Vector4& operator=(const Vector4 &rhs) {
        if (this != &rhs) {
          x = rhs.x;
          y = rhs.y;
          z = rhs.z;
          w = rhs.w;
        }
        return *this;
      }
      inline Vector4& operator=(const Vector3 &rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = 1.0f;
        return *this;
      }
      
      inline float dot(const Vector4 &rhs) const {
        return (x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w);
      }
      
      inline Vector4& operator+=(const Vector4 &rhs) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
      }
      inline Vector4& operator-=(const Vector4 &rhs) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
      }
      inline Vector4& operator*=(const Vector4 &rhs) {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
      }
      inline Vector4& operator/=(const Vector4 &rhs) {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
      }
      inline Vector4& operator*=(float s) {
        x *= s;
        y *= s;
        z *= s;
        w *= s;
        return *this;
      }
      inline Vector4& operator/=(float s) {
        x /= s;
        y /= s;
        z /= s;
        w /= s;
        return *this;
      }
      inline Vector4 operator-() const {
        return Vector4(-x, -y, -z, -w);
      }
      inline bool operator==(const Vector4 &rhs) const {
        return (
          (Abs(x - rhs.x) < EPS6) && (Abs(y - rhs.y) < EPS6) &&
          (Abs(z - rhs.z) < EPS6) && (Abs(w - rhs.w) < EPS6));
      }
      inline bool operator!=(const Vector4 &rhs) const {
        return !operator==(rhs);
      }
      
      inline operator const float* () const {
        return (&(this->x));
      }
      inline operator float* () {
        return (&(this->x));
      }
      
      static const Vector4 ZERO;
  };
  
  
  template <unsigned int dim>
  class Vector {
    public:
      
      inline Vector() {
        zero();
      }
      
      inline Vector(float v) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] = v;
        }
      }
      
      inline Vector(const float *v) {
        memcpy(values, v, dim*sizeof(float));
      }
      
      inline Vector(const char *fmt, ...) {
        zero();
        if (fmt) {
          unsigned int cur = 0;
          const char *cc = fmt;
          va_list al;
          va_start(al, fmt);
          while (*cc != '\0' && cur<dim) {
            switch (*cc) {
              case 'g':
              case 'f': {
                double v = va_arg(al, double);
                values[cur] = float(v);
                break;
              }
              case 'u':
              case 'd':
              case 'l':
              case 'i': {
                int i = va_arg(al, int);
                values[cur] = float(i);
                break;
              }
              default:
                cur = dim; // will break the outer loop
            }
            ++cc;
            ++cur;
          }
          va_end(al);
        }
      }
      
      inline Vector(const Vector<dim> &rhs) {
        memcpy(values, rhs.values, dim*sizeof(float));
      }
      
      inline ~Vector() {
      }
      
      inline unsigned int size() const {
        return dim;
      }
      
      inline void zero() {
        memset(values, 0, dim*sizeof(float));
      }
      
      inline void set(const float *v) {
        memcpy(values, v, dim*sizeof(float));
      }
      
      inline float dot(const Vector<dim> &rhs) const {
        float r = 0.0f;
        for (unsigned int i=0; i<dim; ++i) {
          r += values[i] * rhs[i];
        }
        return r;
      }
      
      inline float getSquaredLength() const {
        return dot(*this);
      }
      
      inline float getLength() const {
        return Sqrt(getSquaredLength());
      }
      
      inline Vector<dim>& normalize() {
        float l = getSquaredLength();
        if (l > EPS6) {
          l = 1.0f / Sqrt(l);
          for (unsigned int i=0; i<dim; ++i) {
            values[i] *= l;
          }
        }
        return *this;
      }
      
      inline Vector<dim>& floor(const Vector<dim> &rhs) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] = (values[i] > rhs.values[i]) ? rhs.values[i] : values[i];
        }
        return *this;
      }
      
      inline Vector<dim>& ceil(const Vector<dim> &rhs) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] = (values[i] < rhs.values[i]) ? rhs.values[i] : values[i];
        }
        return *this;
      }
      
      inline void swap(unsigned int i, unsigned int j) {
        float tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
      }
      
      template <unsigned int D>
      inline Vector<dim>& operator=(const Vector<D> &rhs) {
        if (&(values[0]) != &(rhs.values[0])) {
          memcpy(values, rhs.values, (D < dim ? D : dim)*sizeof(float));
        }
        return *this;
      }
      
      inline Vector<dim>& operator*=(float f) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] *= f;
        }
        return *this;
      }
      
      inline Vector<dim>& operator*=(const Vector<dim> &rhs) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] *= rhs[i];
        }
        return *this;
      }
      
      inline Vector<dim>& operator/=(float f) {
        return operator*=(1.0f / f);
      }
      
      inline Vector<dim>& operator+=(const Vector<dim> &rhs) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] += rhs.values[i];
        }
        return *this;
      }
      
      inline Vector<dim>& operator-=(const Vector<dim> &rhs) {
        for (unsigned int i=0; i<dim; ++i) {
          values[i] -= rhs.values[i];
        }
        return *this;
      }
      
      inline float& operator[](unsigned int i) {
        return values[i];
      }
      
      inline float operator[](unsigned int i) const {
        return values[i];
      }
      
    public:
      
      float values[dim];
  };
  
}

inline gmath::Vector2 operator*(const gmath::Vector2 &v0, const gmath::Vector2 &v1) {
  gmath::Vector2 tmp(v0);
  tmp *= v1;
  return tmp;
}
inline gmath::Vector2 operator/(const gmath::Vector2 &v0, const gmath::Vector2 &v1) {
  gmath::Vector2 tmp(v0);
  tmp /= v1;
  return tmp;
}
inline gmath::Vector2 operator+(const gmath::Vector2 &v0, const gmath::Vector2 &v1) {
  gmath::Vector2 tmp(v0);
  tmp += v1;
  return tmp;
}
inline gmath::Vector2 operator-(const gmath::Vector2 &v0, const gmath::Vector2 &v1) {
  gmath::Vector2 tmp(v0);
  tmp -= v1;
  return tmp;
}
inline gmath::Vector2 operator*(const gmath::Vector2 &v, float f) {
  gmath::Vector2 tmp(v);
  tmp *= f;
  return tmp;
}
inline gmath::Vector2 operator/(const gmath::Vector2 &v, float f) {
  gmath::Vector2 tmp(v);
  tmp /= f;
  return tmp;
}
inline gmath::Vector2 operator*(float f, const gmath::Vector2 &v) {
  gmath::Vector2 tmp(v);
  tmp *= f;
  return tmp;
}
inline std::ostream& operator<<(std::ostream &os, const gmath::Vector2 &rhs) {
  os << "(" << rhs.x << ", " << rhs.y << ")";
  return os;
}

inline gmath::Vector3 operator*(const gmath::Vector3 &v0, const gmath::Vector3 &v1) {
  gmath::Vector3 tmp(v0);
  tmp *= v1;
  return tmp;
}
inline gmath::Vector3 operator/(const gmath::Vector3 &v0, const gmath::Vector3 &v1) {
  gmath::Vector3 tmp(v0);
  tmp /= v1;
  return tmp;
}
inline gmath::Vector3 operator+(const gmath::Vector3 &v0, const gmath::Vector3 &v1) {
  gmath::Vector3 tmp(v0);
  tmp += v1;
  return tmp;
}
inline gmath::Vector3 operator-(const gmath::Vector3 &v0, const gmath::Vector3 &v1) {
  gmath::Vector3 tmp(v0);
  tmp -= v1;
  return tmp;
}
inline gmath::Vector3 operator*(const gmath::Vector3 &v, float f) {
  gmath::Vector3 tmp(v);
  tmp *= f;
  return tmp;
}
inline gmath::Vector3 operator/(const gmath::Vector3 &v, float f) {
  gmath::Vector3 tmp(v);
  tmp /= f;
  return tmp;
}
inline gmath::Vector3 operator*(float f, const gmath::Vector3 &v) {
  gmath::Vector3 tmp(v);
  tmp *= f;
  return tmp;
}
inline std::ostream& operator<<(std::ostream &os, const gmath::Vector3 &rhs) {
  os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ")";
  return os;
}


inline gmath::Vector4 operator*(const gmath::Vector4 &v0, const gmath::Vector4 &v1) {
  gmath::Vector4 tmp(v0);
  tmp *= v1;
  return tmp;
}
inline gmath::Vector4 operator/(const gmath::Vector4 &v0, const gmath::Vector4 &v1) {
  gmath::Vector4 tmp(v0);
  tmp /= v1;
  return tmp;
}
inline gmath::Vector4 operator+(const gmath::Vector4 &v0, const gmath::Vector4 &v1) {
  gmath::Vector4 tmp(v0);
  tmp += v1;
  return tmp;
}
inline gmath::Vector4 operator-(const gmath::Vector4 &v0, const gmath::Vector4 &v1) {
  gmath::Vector4 tmp(v0);
  tmp -= v1;
  return tmp;
}
inline gmath::Vector4 operator*(const gmath::Vector4 &v, float f) {
  gmath::Vector4 tmp(v);
  tmp *= f;
  return tmp;
}
inline gmath::Vector4 operator/(const gmath::Vector4 &v, float f) {
  gmath::Vector4 tmp(v);
  tmp /= f;
  return tmp;
}
inline gmath::Vector4 operator*(float f, const gmath::Vector4 &v) {
  gmath::Vector4 tmp(v);
  tmp *= f;
  return tmp;
}
inline std::ostream& operator<<(std::ostream &os, const gmath::Vector4 &rhs) {
  os << "(" << rhs.x << ", " << rhs.y << ", " << rhs.z << ", " << rhs.w << ")";
  return os;
}


template <unsigned int d>
inline gmath::Vector<d> operator+(const gmath::Vector<d> &v0, const gmath::Vector<d> &v1) {
	gmath::Vector<d> result(v0);
	return result += v1;
}

template <unsigned int d>
inline gmath::Vector<d> operator-(const gmath::Vector<d> &v0, const gmath::Vector<d> &v1) {
	gmath::Vector<d> result(v0);
	return result -= v1;
}

template <unsigned int d>
inline gmath::Vector<d> operator*(const gmath::Vector<d> &v0, const gmath::Vector<d> &v1) {
	gmath::Vector<d> result(v0);
	return result *= v1;
}

template <unsigned int d>
inline gmath::Vector<d> operator*(const gmath::Vector<d> &v, float s) {
	gmath::Vector<d> result(v);
	return result *= s;
}

template <unsigned int d>
inline gmath::Vector<d> operator/(const gmath::Vector<d> &v, float s) {
	gmath::Vector<d> result(v);
	return result /= s;
}

template <unsigned int d>
inline gmath::Vector<d> operator*(float s, const gmath::Vector<d> &v) {
	gmath::Vector<d> result(v);
	return result *= s;
}

template <unsigned int d>
inline std::ostream& operator<<(std::ostream &os, const gmath::Vector<d> &v) {
  os << "(";
	for (unsigned int i=0; i<(d-1); ++i) {
		os << v[i] << ", ";
	}
	os << v[d-1] << ")";
	return os;
}

#endif


