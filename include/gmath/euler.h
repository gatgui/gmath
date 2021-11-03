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

#ifndef __gmath_euler_h_
#define __gmath_euler_h_

#include <gmath/vector.h>

namespace gmath {
  
  class GMATH_API Euler {
    public:
      
      enum Order {
				XYZ = 0,
				XZY,
				YXZ,
				YZX,
				ZXY,
				ZYX
			};
      
      float rx;
      float ry;
      float rz;
      Order order;
      
      inline Euler(Order o = ZYX)
        :rx(0), ry(0), rz(0), order(o) {
      }
      
      inline Euler(float x, float y, float z, Order o = ZYX)
        :rx(x), ry(y), rz(z), order(o) {
      }
      
      inline Euler(const float *v, Order o = ZYX)
        :rx(v[0]), ry(v[1]), rz(v[2]), order(o) {
      }
      
      inline Euler(const Vector3 &v, Order o = ZYX)
        :rx(v.x), ry(v.y), rz(v.z), order(o) {
      }
      
      inline Euler(const Euler &rhs)
        :rx(rhs.rx), ry(rhs.ry), rz(rhs.rz), order(rhs.order) {
      }
      
      inline ~Euler() {
      }
      
      inline Euler& operator=(const Euler &rhs) {
        if (this != &rhs) {
          rx = rhs.rx;
          ry = rhs.ry;
          rz = rhs.rz;
          order = rhs.order;
        }
        return *this;
      }
      
      inline bool operator==(const Euler &rhs) const {
        return (
          order==rhs.order &&
          Abs(rx-rhs.rx)<EPS6 &&
          Abs(ry-rhs.ry)<EPS6 &&
          Abs(rz-rhs.rz)<EPS6);
      }
      
      inline bool operator!=(const Euler &rhs) const {
        return !operator==(rhs);
      }
      
      inline Euler& operator+=(const Euler &rhs) {
        if (order == rhs.order) {
          rx += rhs.rx;
          ry += rhs.ry;
          rz += rhs.rz;
        }
        return *this;
      }
      
      inline Euler& operator-=(const Euler &rhs) {
        if (order == rhs.order) {
          rx -= rhs.rx;
          ry -= rhs.ry;
          rz -= rhs.rz;
        }
        return *this;
      }
      
      inline Euler& operator*=(float s) {
        rx *= s;
        ry *= s;
        rz *= s;
        return *this;
      }
      
      inline Euler& operator/=(float s) {
        rx /= s;
        ry /= s;
        rz /= s;
        return *this;
      }
  
  };
  
}

inline gmath::Euler operator+(const gmath::Euler &e0, const gmath::Euler &e1) {
  gmath::Euler tmp(e0);
  return (tmp += e1);
}

inline gmath::Euler operator-(const gmath::Euler &e0, const gmath::Euler &e1) {
  gmath::Euler tmp(e0);
  return (tmp -= e1);
}

inline gmath::Euler operator*(const gmath::Euler &e, float s) {
  gmath::Euler tmp(e);
  return (tmp *= s);
}

inline gmath::Euler operator*(float s, const gmath::Euler &e) {
  gmath::Euler tmp(e);
  return (tmp *= s);
}

inline gmath::Euler operator/(const gmath::Euler &e, float s) {
  gmath::Euler tmp(e);
  return (tmp /= s);
}

inline std::ostream& operator<<(std::ostream &os, const gmath::Euler &e) {
  os << "Euler{(" << e.rx << ", " << e.ry << ", " << e.rz << "), ";
  switch (e.order) {
    case gmath::Euler::XYZ:
      os << "XYZ"; break;
    case gmath::Euler::XZY:
      os << "XZY"; break;
    case gmath::Euler::YXZ:
      os << "YXZ"; break;
    case gmath::Euler::YZX:
      os << "YZX"; break;
    case gmath::Euler::ZXY:
      os << "ZXY"; break;
    case gmath::Euler::ZYX:
    default:
      os << "ZYX";
  }
  return os;
}


#endif
