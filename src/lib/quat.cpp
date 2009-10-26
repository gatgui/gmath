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

#include <gmath/quat.h>
#include <gmath/convert.h>

namespace gmath {
  
  const Quat Quat::IDENTITY(0,0,0,1);
  const Quat Quat::ZERO(0,0,0,0);
  
  Quat::Quat(const Vector3 &axis, float a) {
    //fromAxisAngle(axis, a);
    Convert::ToQuat(axis, a, *this);
  }
  
  Quat& Quat::inverse() {
    float n = getSquaredLength();
    if (n > EPS6) {
      n = 1.0f / Sqrt(n); // (float)sqrt(n);
      x = -x * n;
      y = -y * n;
      z = -z * n;
      w = w * n;
    }
    return *this;
  }
  
  Quat& Quat::operator*=(const Quat &rhs) {
    float cx = (y * rhs.z) - (z * rhs.y);
    float cy = (z * rhs.x) - (x * rhs.z);
    float cz = (x * rhs.y) - (y * rhs.x);
    float dp = (x*rhs.x + y*rhs.y + z*rhs.z);
    x = (w * rhs.x) + (x * rhs.w) + cx;
    y = (w * rhs.y) + (y * rhs.w) + cy;
    z = (w * rhs.z) + (z * rhs.w) + cz;
    w = (w * rhs.w) - dp;
    return *this;
  }
  
  Quat& Quat::normalize() {
    float n = getSquaredLength();
    if (n > EPS6) {
      float factor = 1.0f / Sqrt(n);
      return (*this *= factor);
    } else {
      return *this;
    }
  }
  
  Quat Quat::getLog() const {
  	Quat qlog;
  	qlog.w = 0.0f;
    if (Abs(w) < 1) {
      float theta = Acos(w);
      float sint = Sin(theta);
      if (Abs(sint) >= EPS6) {
        float coeff = theta / sint;
        qlog.x = x * coeff;
        qlog.y = y * coeff;
        qlog.z = z * coeff;
  			return qlog;
      }
    }
  	qlog.x = x;
  	qlog.y = y;
  	qlog.z = z;
    return qlog;
  }

  Quat Quat::getExp() const
  {
  	Quat qexp;
  	float theta = Sqrt(x*x + y*y + z*z);
    float sint = Sin(theta);
    qexp.w = Cos(theta);
    if (Abs(sint) >= EPS6) {
      float coeff = sint / theta;
      qexp.x = x * coeff;
      qexp.y = y * coeff;
      qexp.z = z * coeff;
    } else {
  		qexp.x = x;
  		qexp.y = y;
  		qexp.z = z;
  	}
  	return qexp;
  }
  
  Quat Quat::getPow(float p) const {
  	//  q^a = exp(a * log(q))
  	Quat qpow;
  	float l = Sqrt(x*x + y*y + z*z);
  	float cost = w;
  	float sint = 1 / l;
  	float angle = Atan2(sint, cost);
  	sint *= sint;
  	qpow.w = p * angle;
  	qpow.x = x * sint;
  	qpow.y = y * sint;
  	qpow.z = z * sint;
  	return qpow;
  }
  
  Quat Quat::slerp(const Quat &to, float t) const {
    
    Clamp(t, 0, 1);
    
    Quat tmp;
    
    float cost = this->dot(to);
    if (cost < 0.0f) {
      cost = -cost;
      tmp = -to;
    } else {
      tmp = to;
    }
    
    float scale0, scale1;
    
    if ((1.0f - cost) > EPS6) {
      float theta = Acos(cost);
      float isint = 1.0f / Sin(theta);
      scale0 = Sin((1.0f - t)*theta) * isint;
      scale1 = Sin(t*theta) * isint;
    } else {
      scale0 = 1.0f - t;
      scale1 = t;
    }
    return ((scale0 * (*this)) + (scale1 * tmp));
  }
  
  Quat Quat::Align(
    const Vector3 &axis0, const Vector3 &axis1, const Vector3 &fallback)
  {
    Quat q;
    Vector3 v0 = axis0;
    Vector3 v1 = axis1;
    v0.normalize();
    v1.normalize();
    float d = v0.dot(v1); // cos(a)
    if (d >= 1.0f) {
      return Quat::IDENTITY;
    }
    // cos(a) = 2 cos(a/2)^2 - 1
    float c = Sqrt(0.5f * (d + 1.0f)); // cos(a/2)
    if (c < EPS6) {
      float a = ToDegree(PI);
      if (fallback != Vector3::ZERO) {
        //q.fromAxisAngle(fallback, a);
        Convert::ToQuat(fallback, a, q);
      } else {
        Vector3 axis = Vector3::UNIT_X.cross(v0);
        if (axis == Vector3::ZERO) {
          axis = Vector3::UNIT_Y.cross(v0);
        }
        axis.normalize();
        //q.fromAxisAngle(axis, a);
        Convert::ToQuat(axis, a, q);
      }
    } else {
      // sin(a) = 2 sin(a/2) cos(a/2)
      // sin(a/2) / sin(a) = 1 / 2 cos(a/2) --> s
      Vector3 axis = v0.cross(v1); // axis.length() = sin(a)
      float s = 0.5f / c;
      q.x = axis.x * s;
      q.x = axis.y * s;
      q.x = axis.z * s;
      q.w = c;
    }
    return q;
  }
  
  void Quat::decompTwistSwing(const Vector3 &twistAxis, Quat &twist, Quat &swing) {
  	Vector3 ra = *this * twistAxis;
  	swing = Align(twistAxis, ra);
    // *this = twist * swing
    // twist = *this * swing^-1
  	twist = (*this) * swing.getConjugate();
  }

  void Quat::decompSwingTwist(const Vector3 &twistAxis, Quat &swing, Quat &twist) {
  	Vector3 ra = *this * twistAxis;
  	swing = Align(twistAxis, ra);
    // *this = swing * twist
    // twist = swing^-1 * *this
  	twist = swing.getConjugate() * (*this);
  }
  
}

gmath::Quat operator*(const gmath::Quat &q0, const gmath::Quat &q1) {
  gmath::Quat tmp(q0);
  return (tmp *= q1);
}

gmath::Quat operator+(const gmath::Quat &q0, const gmath::Quat &q1) {
  gmath::Quat tmp(q0);
  return (tmp += q1);
}

gmath::Quat operator-(const gmath::Quat &q0, const gmath::Quat &q1) {
  gmath::Quat tmp(q0);
  return (tmp -= q1);
}

gmath::Quat operator*(float s, const gmath::Quat &q) {
  gmath::Quat tmp(q);
  return (tmp *= s);
}

gmath::Quat operator*(const gmath::Quat &q, float s) {
  gmath::Quat tmp(q);
  return (tmp *= s);
}

gmath::Quat operator/(const gmath::Quat &q, float s) {
  gmath::Quat tmp(q);
  return (tmp /= s);
}

gmath::Vector3 operator*(const gmath::Quat &q, const gmath::Vector3 &v) {
  // q * (v,0) * q-1
  gmath::Quat tmp = q * gmath::Quat(v.x, v.y, v.z, 0) * q.getConjugate();
  return gmath::Vector3(tmp.x, tmp.y, tmp.z);
  /*
  //nVidia SDK implementation
  gmath::Vector3 uv, uuv;
  gmath::Vector3 qvec(q.x, q.y, q.z);
  uv = qvec.cross(v);
  uuv = qvec.cross(uv);
  uv *= (2.0f * q.w);
  uuv *= 2.0f;
  return v + uv + uuv;
  */
}

std::ostream& operator<<(std::ostream &os, const gmath::Quat &q) {
  os << "Quat(" << q.x << ", " << q.y << ", " << q.z << ", " << q.w << ")";
  return os;
}

