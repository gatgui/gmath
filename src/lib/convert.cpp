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

#include <gmath/convert.h>

namespace gmath {

  namespace Convert {
    
    // ---
    
    typedef void (*EulerToMatrix4)(const Euler&, Matrix4&);
    typedef void (*Matrix4ToEuler)(const Matrix4&, Euler&);
    
    static void EulerToMatrix4_XYZ(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
      float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cy*cz;
      m[ 1] = sx*sy*cz + cx*sz;
      m[ 2] = -cx*sy*cz + sx*sz;
      m[ 4] = -cy*sz;
      m[ 5] = -sx*sy*sz + cx*cz;
      m[ 6] = cx*sy*sz + sx*cz;
      m[ 8] = sy;
      m[ 9] = -sx*cy;
      m[10] = cx*cy;
    }

    static void EulerToMatrix4_XZY(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
      float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cz*cy;
      m[ 1] = cx*sz*cy + sx*sy;
      m[ 2] = sx*sz*cy - cx*sy;
      m[ 4] = -sz;
      m[ 5] = cx*cz;
      m[ 6] = sx*cz;
      m[ 8] = cz*sy;
      m[ 9] = cx*sz*sy - sx*cy;
      m[10] = sx*sz*sy + cx*cy;
    }

    static void EulerToMatrix4_YXZ(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
    	float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cy*cz + sy*sx*sz;
      m[ 1] = cx*sz;
      m[ 2] = -sy*cz + cy*sx*sz;
      m[ 4] = -cy*sz + sy*sx*cz;
      m[ 5] = cx*cz;
      m[ 6] = sy*sz + cy*sx*cz;
      m[ 8] = sy*cx;
      m[ 9] = -sx;
      m[10] = cy*cx;
    }

    static void EulerToMatrix4_YZX(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
      float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cy*cz;
      m[ 1] = sz;
      m[ 2] = -sy*cz;
      m[ 4] = -cy*sz*cx + sy*sx;
      m[ 5] = cz*cx;
      m[ 6] = sy*sz*cx + cy*sx;
      m[ 8] = cy*sz*sx + sy*cx;
      m[ 9] = -cz*sx;
      m[10] = -sy*sz*sx + cy*cx;
    }

    static void EulerToMatrix4_ZXY(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
      float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cz*cy - sz*sx*sy;
      m[ 1] = sz*cy + cz*sx*sy;
      m[ 2] = -cx*sy;
      m[ 4] = -sz*cx;
      m[ 5] = cz*cx;
      m[ 6] = sx;
      m[ 8] = cz*sy + sz*sx*cy;
      m[ 9] = sz*sy - cz*sx*cy;
      m[10] = cx*cy; 
    }

    static void EulerToMatrix4_ZYX(const Euler &e, Matrix4 &m) {
      float rx = ToRadian(e.rx);
      float ry = ToRadian(e.ry);
      float rz = ToRadian(e.rz);
      float cz = Cos(rz);
      float cy = Cos(ry);
      float cx = Cos(rx);
      float sz = Sin(rz);
      float sy = Sin(ry);
      float sx = Sin(rx);
      m[ 0] = cz*cy;
      m[ 1] = sz*cy;
      m[ 2] = -sy;
      m[ 4] = -sz*cx + cz*sy*sx;
      m[ 5] = cz*cx + sz*sy*sx;
      m[ 6] = cy*sx;
      m[ 8] = sz*sx + cz*sy*cx;
      m[ 9] = -cz*sx + sz*sy*cx;
      m[10] = cy*cx;
    }
    
    static void Matrix4ToEuler_XYZ(const Matrix4 &m, Euler &e) {
    	if (m[8] < 1.0f) {
    		if (m[8] > -1.0f) {
    			e.rx = Atan2d(-m[9], m[10]);
    			e.ry = Asind(m[8]);
    			e.rz = Atan2d(-m[4], m[0]);
    		} else {
    			e.rz = 0.0f;
    			e.ry = -ToDegree(0.5f * PI);
    			e.rx = -Atan2d(m[1], m[5]);
    		}
    	} else {
    		e.rz = 0.0f;
    		e.ry = ToDegree(0.5f * PI);
    		e.rx = Atan2d(m[1], m[5]);
    	}
    }

    static void Matrix4ToEuler_XZY(const Matrix4 &m, Euler &e) {
    	if (m[4] < 1.0f) {
    	  if (m[4] > -1.0f) {
          e.rx = Atan2d(m[6], m[5]);
          e.rz = Asind(-m[4]);
          e.ry = Atan2d(m[8], m[0]);
        } else {
          e.rx = Atan2d(m[2], m[10]);
          e.rz = ToDegree(PI * 0.5f);
          e.ry = 0.0f;
        }
      } else {
        e.rx = Atan2d(-m[2], m[10]);
        e.rz = -ToDegree(PI * 0.5f);
        e.ry = 0.0f;
      }
    }

    static void Matrix4ToEuler_YXZ(const Matrix4 &m, Euler &e) {
      if (m[9] < 1.0f) {
        if (m[9] > -1.0f) {
          e.ry = Atan2d(m[8], m[10]);
          e.rx = Asind(-m[9]);
          e.rz = Atan2d(m[1], m[5]);
        } else {
          e.ry = Atan2d(m[4], m[0]);
          e.rx = ToDegree(PI * 0.5f);
          e.rz = 0.0f;
        }
      } else {
        e.ry = Atan2d(-m[4], m[0]);
        e.rx = -ToDegree(PI * 0.5f);
        e.rz = 0.0f;
      }
    }

    static void Matrix4ToEuler_YZX(const Matrix4 &m, Euler &e) {
    	if (m[1] < 1.0f) {
    	  if (m[1] > -1.0f) {
          e.ry = Atan2d(-m[2], m[0]);
          e.rz = Asind(m[1]);
          e.rx = Atan2d(-m[9], m[5]);
        } else {
          e.ry = -Atan2d(m[6], m[10]);
          e.rz = -ToDegree(PI * 0.5f);
          e.rx = 0.0f;
        }
      } else {
        e.ry = Atan2d(m[6], m[10]);
        e.rz = ToDegree(PI * 0.5f);
        e.rx = 0.0f;
      }
    }

    static void Matrix4ToEuler_ZXY(const Matrix4 &m, Euler &e) {
    	if (m[6] < 1.0f) {
        if (m[6] > -1.0f) {
          e.rz = Atan2d(-m[4], m[5]);
          e.rx = Asind(m[6]);
          e.ry = Atan2d(-m[2], m[10]);
        } else {
          e.rz = -Atan2d(m[8], m[0]);
          e.rx = -ToDegree(PI * 0.5f);
          e.ry = 0.0f;
        }
      } else {
        e.rz = Atan2d(m[8], m[0]);
        e.rx = ToDegree(PI * 0.5f);
        e.ry = 0.0f;
      }
    }

    static void Matrix4ToEuler_ZYX(const Matrix4 &m, Euler &e) {
    	if (m[2] < 1.0f) {
        if (m[2] > -1.0f) {
          e.rz = Atan2d(m[1], m[0]);
          e.ry = Asind(-m[2]);
          e.rx = Atan2d(m[6], m[10]);
        } else {
          e.rz = -Atan2d(m[4], m[8]);
          e.ry = ToDegree(PI * 0.5f);
          e.rx = 0.0f;
        }
      } else {
        e.rz = Atan2d(-m[4], -m[8]);
        e.ry = ToDegree(-PI * 0.5f);
        e.rx = 0.0f;
      }
    }
    
    // ---
    
    void ToQuat(const Euler &e, Quat &q) {
      Matrix4 tmp;
      ToMatrix4(e, tmp);
      ToQuat(tmp, q);
    }
    
    void ToQuat(const Vector3 &axis, float angle, Quat &q) {
      float ha = ToRadian(0.5f * angle);
      float sinha = Sin(ha);
      q.x = sinha * axis.x;
      q.y = sinha * axis.y;
      q.z = sinha * axis.z;
      q.w = Cos(ha);
    }
    
    void ToQuat(const Matrix4 &m, Quat &q) {
      float tr, s;
      tr = m[0] + m[5] + m[10] + 1;
      if (tr > 0.0f) {
        s = Sqrt(tr);
        q.w = 0.5f * s;
        s = 0.5f / s;
        q.x = (m[6] - m[9]) * s;
        q.y = (m[8] - m[2]) * s;
        q.z = (m[1] - m[4]) * s;
      } else {
        int i = 0;
        if (m[5] > m[0]) i = 1;
        if (m[10] > m[i+(i<<2)]) i = 2;
        if (i == 0) {
          s = Sqrt(m[0] - (m[5] + m[10]) + 1.0f);
          q.x = 0.5f * s;
          s = 0.5f / s;
          q.y = (m[4] + m[1]) * s;
          q.z = (m[2] + m[8]) * s;
          q.w = (m[6] - m[9]) * s;
        } else if (i == 1) {
          s = Sqrt(m[5] - (m[0] + m[10]) + 1.0f);
          q.y = 0.5f * s;
          s = 0.5f / s;
          q.z = (m[9] + m[6]) * s;
          q.w = (m[8] - m[2]) * s;
          q.x = (m[4] + m[1]) * s;
        } else {
          s = Sqrt(m[10] - (m[0] + m[5]) + 1.0f);
          q.z = 0.5f * s;
          s = 0.5f / s;
          q.w = (m[1] - m[4]) * s;
          q.x = (m[2] + m[8]) * s;
          q.y = (m[9] + m[6]) * s;
        }
      }
      q.normalize();
    }
    
    void ToAxisAngle(const Euler &e, Vector3 &axis, float &angle) {
      Matrix4 tmp;
      ToMatrix4(e, tmp);
      ToAxisAngle(tmp, axis, angle);
    }
    
    void ToAxisAngle(const Quat &q, Vector3 &axis, float &angle) {
      float isinht = q.x*q.x + q.y*q.y + q.z*q.z;
      if (isinht > 0) {
    		isinht = 1.0f / Sqrt(isinht);
        axis.x = q.x * isinht;
        axis.y = q.y * isinht;
        axis.z = q.z * isinht;
        angle = 2.0f * ToDegree(Acos(q.w));
      } else {
    		angle = 0.0f;
    		axis.x = 1.0f;
    		axis.y = 0.0f;
    		axis.z = 0.0f;
    	}
    }
    
    void ToAxisAngle(const Matrix4 &m, Vector3 &axis, float &angle) {
      float tr   = m[0] + m[5] + m[10];
    	float cost = 0.5f * (tr - 1.0f);
    	if (cost > (1-EPS6)) {
    		angle = 0;
    		axis.x = 1;
    		axis.y = 0;
    		axis.z = 0;
    	} else {
    		angle = Acos(cost);
    		float isint = 1.0f / Sin(angle);
    		axis.x = 0.5f * isint * (m[6] - m[9]);
    		axis.y = 0.5f * isint * (m[8] - m[2]);
    		axis.z = 0.5f * isint * (m[1] - m[4]);
    		axis.normalize();
    	  angle = ToDegree(angle);
    	}
    }
    
    void ToMatrix4(const Vector3 &axis, float angle, Matrix4 &m) {
      m = Matrix4::MakeRotate(angle, axis);
    }
    
    void ToMatrix4(const Quat &q, Matrix4 &m) {
      float xx, yy, zz, xy, xz, yz, wx, wy, wz;
      xx = 2.0f * q.x;
      yy = 2.0f * q.y;
      zz = 2.0f * q.z;
      xy = xx * q.y;
      xz = xx * q.z;
      yz = yy * q.z;
      wx = xx * q.w;
      wy = yy * q.w;
      wz = zz * q.w;
      xx = xx * q.x;
      yy = yy * q.y;
      zz = zz * q.z;
      m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
      m[15] = 1.0f;
      m[0] = 1.0f - yy - zz;
    	m[4] = xy - wz;
    	m[8] = xz + wy;
      m[1] = xy + wz;
    	m[5] = 1.0f - xx - zz;
    	m[9] = yz - wx;
      m[2] = xz - wy;
    	m[6] = yz + wx;
    	m[10] = 1.0f - xx - yy;
    }
    
    void ToMatrix4(const Euler &e, Matrix4 &m) {
      static EulerToMatrix4 tom4[6] = {
        &EulerToMatrix4_XYZ,
        &EulerToMatrix4_XZY,
        &EulerToMatrix4_YXZ,
        &EulerToMatrix4_YZX,
        &EulerToMatrix4_ZXY,
        &EulerToMatrix4_ZYX
      };
      m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
      m[15] = 1.0f;
      (*(tom4[e.order]))(e, m);
    }
    
    void ToEuler(const Matrix4 &m, Euler &e) {
      static Matrix4ToEuler toe[6] = {
        &Matrix4ToEuler_XYZ,
        &Matrix4ToEuler_XZY,
        &Matrix4ToEuler_YXZ,
        &Matrix4ToEuler_YZX,
        &Matrix4ToEuler_ZXY,
        &Matrix4ToEuler_ZYX
      };
      (*(toe[e.order]))(m, e);
    }
    
    void ToEuler(const Quat &q, Euler &e) {
      Matrix4 tmp;
      ToMatrix4(q, tmp);
      ToEuler(tmp, e);
    }
    
    void ToEuler(const Vector3 &axis, float angle, Euler &e) {
      Matrix4 tmp;
      ToMatrix4(axis, angle, tmp);
      ToEuler(tmp, e);
    }
    
  }
  
}

