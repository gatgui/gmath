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

#include <gmath/sphere.h>

namespace gmath {

  Sphere Sphere::NaiveMinSphere(const std::vector<Vector3> &points) {
    size_t i;
    Vector3 center;
    for (i=0; i<points.size(); ++i) {
      center += points[i];
    }
    center /= float(points.size());
    float r0 = 0;
    for (i=0; i<points.size(); ++i) {
      float r1 = (points[i] - center).getSquaredLength();
      if (r1 > r0) {
        r0 = r1;
      }
    }
    return Sphere(center, Sqrt(r0));
  }

  Sphere Sphere::FastMinSphere(const std::vector<Vector3> &points) {
    
    size_t i, j, p0 = 0, p1 = 0;

    float len, len2, r2, dr, maxlen2 = 0;

    // find the two most sperated points
    for (i=0; i<points.size(); ++i) {
      for (j=i+1; j<points.size(); ++j) {
        len2 = (points[j] - points[i]).getSquaredLength();
        if (len2 > maxlen2) {
          p0 = i;
          p1 = j;
          maxlen2 = len2;
        }
      }
    }

    Vector3 center = 0.5f * (points[p0] + points[p1]);
    float radius = 0.5f * Sqrt(maxlen2);

    r2 = 0.25f * maxlen2;

    for (i=0; i<points.size(); ++i) {
      Vector3 d = points[i] - center;
      len2 = d.getSquaredLength();
      if (len2 > r2) {
        len = Sqrt(len2);
        dr  = 0.5f * (len - radius);
        d  /= len;
        radius += dr;
        center += dr * d;
        r2 = radius * radius;
      }
    }
    
    return Sphere(center, radius);
  }
  
  // ---
  
  struct Support {
    bool isPointInside(size_t idx, std::vector<Vector3*> &ppoints, float eps) {
      for (size_t i=0; i<count; ++i) {
        Vector3 diff = *(ppoints[idx]) - *(ppoints[indices[i]]);
        if (diff.getSquaredLength() < eps) {
          return true;
        }
      }
      return false;
    }
    size_t count;
    size_t indices[4];
  };
  
  static bool IsPointInside(const Vector3 &p, const Sphere &s, float &diff) {
    Vector3 dv  = p - s.getCenter();
    float test = dv.getSquaredLength();
    diff = test - s.getRadius(); // isn't it Radius2 ?
    return (diff <= 0.0f);
  }
  
  static Sphere ExactSphere1(const Vector3 &p) {
    return Sphere(p, 0.0f);
  }

  static Sphere ExactSphere2(const Vector3 &p0, const Vector3 &p1) {
    Sphere s;
    s.setCenter(0.5f * (p0 + p1));
    Vector3 dv = p1 - p0;
    // store radius * radius
    s.setRadius(0.25f * dv.getSquaredLength()); // so that r = 0.5f * dv.length();
    return s;
  }

  static Sphere ExactSphere3(
    const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, float epsilon2)
  {
    Vector3 a = p0 - p2;
    Vector3 b = p1 - p2;

    float aa = a.dot(a);
    float ab = a.dot(b);
    float bb = b.dot(b);
    float det = aa*bb - ab*ab;

    Sphere s;

    if (Abs(det) > epsilon2) {
      float hid = 0.5f / det;
      float u0 = hid * bb * (aa - ab);
      float u1 = hid * aa * (bb - ab);
      float u2 = 1.0f - u0 - u1;
      s.setCenter(u0*p0 + u1*p1 + u2*p2);
      Vector3 tmp = u0*a + u1*b;
      s.setRadius(tmp.getSquaredLength());
    } else {
      s.setCenter(Vector3::ZERO);
      s.setRadius(std::numeric_limits<float>::max());
    }
    return s;
  }

  static Sphere ExactSphere4(
    const Vector3 &p0, const Vector3 &p1,
    const Vector3 &p2, const Vector3 &p3, float epsilon2)
  {
    Vector3 e10 = p0 - p3;
    Vector3 e20 = p1 - p3;
    Vector3 e30 = p2 - p3;

    float a[3][3];

    a[0][0] = e10.dot(e10);
    a[0][1] = e10.dot(e20);
    a[0][2] = e10.dot(e30);
    a[1][0] = a[0][1];
    a[1][1] = e20.dot(e20);
    a[1][2] = e20.dot(e30);
    a[2][0] = a[0][2];
    a[2][1] = a[1][2];
    a[2][2] = e30.dot(e30);

    float b[3];

    b[0] = 0.5f*a[0][0];
    b[1] = 0.5f*a[1][1];
    b[2] = 0.5f*a[2][2];

    float ainv[3][3];

    ainv[0][0] = a[1][1]*a[2][2] - a[1][2]*a[2][1];
    ainv[0][1] = a[0][2]*a[2][1] - a[0][1]*a[2][2];
    ainv[0][2] = a[0][1]*a[1][2] - a[0][2]*a[1][1];
    ainv[1][0] = a[1][2]*a[2][0] - a[1][0]*a[2][2];
    ainv[1][1] = a[0][0]*a[2][2] - a[0][2]*a[2][0];
    ainv[1][2] = a[0][2]*a[1][0] - a[0][0]*a[1][2];
    ainv[2][0] = a[1][0]*a[2][1] - a[1][1]*a[2][0];
    ainv[2][1] = a[0][1]*a[2][0] - a[0][0]*a[2][1];
    ainv[2][2] = a[0][0]*a[1][1] - a[0][1]*a[1][0];

    float det = a[0][0]*ainv[0][0] + a[0][1]*ainv[1][0] + a[0][2]*ainv[2][0];

    Sphere s;

    if (Abs(det) > epsilon2) { //epsilon was specified for radius*radius

      float idet = 1.0f / det;
      int row, col;

      for (row=0; row<3; ++row) {
        for (col=0; col<3; ++col) {
          ainv[row][col] *= idet;
        }
      }

      float u[4];

      for (row=0; row<3; ++row) {
        u[row] = 0.0f;
        for (col=0; col<3; ++col) {
          u[row] += ainv[row][col] * b[col];
        }
      }
      u[3] = 1.0f - u[0] - u[1] - u[2];
      s.setCenter(u[0]*p0 + u[1]*p1 + u[2]*p2 + u[3]*p3);
      Vector3 tmp = u[0]*e10 + u[1]*e20 + u[2]*e30;
      s.setRadius(tmp.getSquaredLength());
    } else {
      s.setCenter(Vector3::ZERO);
      s.setRadius(std::numeric_limits<float>::max());
    }
    return s;
  }
  
  static Sphere UpdateSupport1(
    int idx, std::vector<Vector3*> &ppoints, Support &sup, float)
  {
    Vector3 &p0 = *ppoints[sup.indices[0]];
    Vector3 &p1 = *ppoints[idx];
    Sphere s = ExactSphere2(p0, p1);
    sup.count = 2;
    sup.indices[1] = idx;
    return s;
  }
  
  static Sphere UpdateSupport2(
    int idx, std::vector<Vector3*> &ppoints, Support &sup, float eps2)
  {
    Vector3 &p0 = *ppoints[sup.indices[0]];
    Vector3 &p1 = *ppoints[sup.indices[1]];
    Vector3 &p2 = *ppoints[idx];

    Sphere ss[3];
    float minr = std::numeric_limits<float>::max();
    float diff;
    int i = -1;

    ss[0] = ExactSphere2(p0, p2);
    if (IsPointInside(p1, ss[0], diff)) {
      minr = ss[0].getRadius();
      i = 0;
    }

    ss[1] = ExactSphere2(p1, p2);
    if (ss[1].getRadius() < minr) {
      if (IsPointInside(p0, ss[1], diff)) {
        minr = ss[1].getRadius();
        i = 1;
      }
    }

    Sphere s;

    if (i != -1) {
      s = ss[i];
      sup.indices[1-i] = idx;
    } else {
      s = ExactSphere3(p0, p1, p2, eps2);
      // assert(s.radius <= minr);
      sup.count = 3;
      sup.indices[2] = idx;
    }

    return s;
  }
  
  static Sphere UpdateSupport3(
    int idx, std::vector<Vector3*> &ppoints, Support &sup, float eps2)
  {
    const Vector3 &p0 = *ppoints[sup.indices[0]];
    const Vector3 &p1 = *ppoints[sup.indices[1]];
    const Vector3 &p2 = *ppoints[sup.indices[2]];
    const Vector3 &p3 = *ppoints[idx];

    Sphere ss[6];
    float minr = std::numeric_limits<float>::max();
    float diff;
    int i = -1;

    ss[0] = ExactSphere2(p0, p3);
    if (IsPointInside(p1, ss[0], diff) && IsPointInside(p2, ss[0], diff)) {
      minr = ss[0].getRadius();
      i = 0;
    }

    ss[1] = ExactSphere2(p1, p3);
    if (ss[1].getRadius() < minr &&
        IsPointInside(p0, ss[1], diff) && IsPointInside(p2, ss[1], diff)) {
      minr = ss[1].getRadius();
      i = 1;
    }

    ss[2] = ExactSphere2(p2, p3);
    if (ss[2].getRadius() < minr &&
        IsPointInside(p0, ss[2], diff) && IsPointInside(p1, ss[2], diff)) {
      minr = ss[2].getRadius();
      i = 2;
    }

    ss[3] = ExactSphere3(p0, p1, p3, eps2);
    if (ss[3].getRadius() < minr && IsPointInside(p2, ss[3], diff)) {
      minr = ss[3].getRadius();
      i = 3;
    }

    ss[4] = ExactSphere3(p0, p2, p3, eps2);
    if (ss[4].getRadius() < minr && IsPointInside(p1, ss[4], diff)) {
      minr = ss[4].getRadius();
      i = 4;
    }

    ss[5] = ExactSphere3(p1, p2, p3, eps2);
    if (ss[5].getRadius() < minr && IsPointInside(p0, ss[5], diff)) {
      minr = ss[5].getRadius();
      i = 5;
    }

    Sphere s;

    switch (i) {
      case 0:
          s = ss[0];
          sup.count = 2;
          sup.indices[1] = idx;
          break;
      case 1:
          s = ss[1];
          sup.count = 2;
          sup.indices[0] = idx;
          break;
      case 2:
          s = ss[2];
          sup.count = 2;
          sup.indices[0] = sup.indices[2];
          sup.indices[1] = idx;
          break;
      case 3:
          s = ss[3];
          sup.indices[2] = idx;
          break;
      case 4:
          s = ss[4];
          sup.indices[1] = idx;
          break;
      case 5:
          s = ss[5];
          sup.indices[0] = idx;
          break;
      default:
          s = ExactSphere4(p0, p1, p2, p3, eps2);
          //assert(s.radius <= minr);
          sup.count = 4;
          sup.indices[3] = idx;
          break;
    }

    return s;
  }
  
  static Sphere UpdateSupport4(
    int idx, std::vector<Vector3*> &ppoints, Support &sup, float eps2)
  {
    Vector3 p[4] = {
      *ppoints[sup.indices[0]],
      *ppoints[sup.indices[1]],
      *ppoints[sup.indices[2]],
      *ppoints[sup.indices[3]]
    };

    const Vector3 &p4 = *ppoints[idx];

    // permutations of type 1
    int t1[4][4] = {
        {0, /*4*/ 1,2,3},
        {1, /*4*/ 0,2,3},
        {2, /*4*/ 0,1,3},
        {3, /*4*/ 0,1,2}
    };

    // permutations of type 2
    int t2[6][4] = {
        {0,1, /*4*/ 2,3},
        {0,2, /*4*/ 1,3},
        {0,3, /*4*/ 1,2},
        {1,2, /*4*/ 0,3},
        {1,3, /*4*/ 0,2},
        {2,3, /*4*/ 0,1}
    };

     // permutations of type 3
    int t3[4][4] = {
        {0,1,2, /*4*/ 3},
        {0,1,3, /*4*/ 2},
        {0,2,3, /*4*/ 1},
        {1,2,3, /*4*/ 0}
    };

    Sphere ss[14];
    float minr = std::numeric_limits<float>::max();
    int i = -1;
    float diff, mindiff = std::numeric_limits<float>::max();
    int mini = -1;
    int k = 0;
    int j;

    // permutations of type 1
    for (j = 0; j < 4; j++, k++) {
      ss[k] = ExactSphere2(p[t1[j][0]], p4);
      if (ss[k].getRadius() < minr) {
        if (IsPointInside(p[t1[j][1]], ss[k], diff) &&
            IsPointInside(p[t1[j][2]], ss[k], diff) &&
            IsPointInside(p[t1[j][3]], ss[k], diff)) {
          minr = ss[k].getRadius();
          i = k;
        } else if (diff < mindiff) {
          mindiff = diff;
          mini = k;
        }
      }
    }

    // permutations of type 2
    for (j = 0; j < 6; j++, k++) {
      ss[k] = ExactSphere3(p[t2[j][0]], p[t2[j][1]], p4, eps2);
      if (ss[k].getRadius() < minr) {
        if (IsPointInside(p[t2[j][2]], ss[k], diff) &&
            IsPointInside(p[t2[j][3]], ss[k], diff)) {
          minr = ss[k].getRadius();
          i = k;
        } else if (diff < mindiff) {
          mindiff = diff;
          mini = k;
        }
      }
    }

    // permutations of type 3
    for (j = 0; j < 4; j++, k++) {
      ss[k] = ExactSphere4(p[t3[j][0]], p[t3[j][1]], p[t3[j][2]], p4, eps2);
      if (ss[k].getRadius() < minr) {
        if (IsPointInside(p[t3[j][3]], ss[k], diff)) {
          minr = ss[k].getRadius();
          i = k;
        } else if (diff < mindiff) {
          mindiff = diff;
          mini = k;
        }
      }
    }

    if (i == -1) {
      i = mini;
    }

    Sphere s = ss[i];

    switch(i) {
      case 0:
          sup.count = 2;
          sup.indices[1] = idx;
          break;
      case 1:
          sup.count = 2;
          sup.indices[0] = idx;
          break;
      case 2:
          sup.count = 2;
          sup.indices[0] = sup.indices[2];
          sup.indices[1] = idx;
          break;
      case 3:
          sup.count = 2;
          sup.indices[0] = sup.indices[3];
          sup.indices[1] = idx;
          break;
      case 4:
          sup.count = 3;
          sup.indices[2] = idx;
          break;
      case 5:
          sup.count = 3;
          sup.indices[1] = idx;
          break;
      case 6:
          sup.count = 3;
          sup.indices[1] = sup.indices[3];
          sup.indices[2] = idx;
          break;
      case 7:
          sup.count = 3;
          sup.indices[0] = idx;
          break;
      case 8:
          sup.count = 3;
          sup.indices[0] = sup.indices[3];
          sup.indices[2] = idx;
          break;
      case 9:
          sup.count = 3;
          sup.indices[0] = sup.indices[3];
          sup.indices[1] = idx;
          break;
      case 10:
          sup.indices[3] = idx;
          break;
      case 11:
          sup.indices[2] = idx;
          break;
      case 12:
          sup.indices[1] = idx;
          break;
      case 13:
          sup.indices[0] = idx;
          break;
    }

    return s;
  }
  
  typedef Sphere (*UpdateFunction)(int,std::vector<Vector3*>&,Support&,float);
  
  Sphere Sphere::MinSphere(const std::vector<Vector3> &points, float eps) {
    
    Sphere mins;
    float eps2 = eps * eps;
    
    UpdateFunction updates[5];
    
    updates[0] = 0;
    updates[1] = &UpdateSupport1;
    updates[2] = &UpdateSupport2;
    updates[3] = &UpdateSupport3;
    updates[4] = &UpdateSupport4;

    Support sup;
    float diff;

    if (points.size() >= 1) {

      std::vector<Vector3*> perm(points.size(), 0);
      size_t i;

      for (i=0; i<points.size(); ++i) {
        perm[i] = (Vector3*)&points[i];
      }

      for (i=points.size()-1; i>0; --i) {
        size_t j = rand() % (i+1);
        if (j != i) {
          Vector3 *save = perm[i];
          perm[i] = perm[j];
          perm[j] = save;
        }
      }

      mins = ExactSphere1(*perm[0]);
      sup.count = 1;
      sup.indices[0] = 0;
      i = 1;

      while (i < perm.size()) {
        if (!sup.isPointInside(i, perm, eps)) {
          if (!IsPointInside(*perm[i], mins, diff)) {
            UpdateFunction update = updates[sup.count];
            Sphere s = (*update)((int)i, perm, sup, eps2);
            if (s.getRadius() > mins.getRadius()) {
              mins = s;
              i = 0;
              continue;
            }
          }
        }
        ++i;
      }
      mins.setRadius(Sqrt(mins.getRadius()));
    }
    
    return mins;
  }
  
}

