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
