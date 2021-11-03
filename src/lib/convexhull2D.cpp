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

#include <gmath/convexhull2D.h>

std::ostream& operator<<(std::ostream &os, const gmath::ConvexHull2D &hull) {
  os << "Hull [";
  if (hull.size() > 1) {
    for (size_t i=0; i<hull.size()-1; ++i) {
      os << hull[i] << ", ";
    }
    os << hull[hull.size()-1];
  }
  os << "]";
  return os;
}

namespace gmath {

  // ---
  
  ConvexHull2D::AngularSorter::AngularSorter() {
  }
  
  ConvexHull2D::AngularSorter::AngularSorter(const Vector2 &rml)
    : mRML(rml) {
  }
  
  ConvexHull2D::AngularSorter::AngularSorter(const ConvexHull2D::AngularSorter &rhs)
    : mRML(rhs.mRML) {
  }
  
  ConvexHull2D::AngularSorter&
  ConvexHull2D::AngularSorter::operator=(const ConvexHull2D::AngularSorter &rhs) {
    mRML = rhs.mRML;
    return *this;
  }
  
  bool ConvexHull2D::AngularSorter::operator()(const Vector2 &v0, const Vector2 &v1) const {
    float l = ConvexHull2D::IsLeft(mRML, v0, v1);
    if (Abs(l) < EPS6) {
      // points a aligned, keep closes
      return ((v0 - mRML).getSquaredLength() < (v1 - mRML).getSquaredLength());
    } else if (l > 0) {
      // v1 on left of mRML->v0 --> greater angle
      return true;
    } else {
      // l < 0
      // v1 on right of mRML->v0 --> smaller angle
      return false;
    }
  }
  
  // ---

  ConvexHull2D::LinearSorter::LinearSorter() {
  }
  
  ConvexHull2D::LinearSorter::LinearSorter(const ConvexHull2D::LinearSorter &) {
  }
  
  ConvexHull2D::LinearSorter&
  ConvexHull2D::LinearSorter::operator=(const ConvexHull2D::LinearSorter &) {
    return *this;
  }
  
  bool ConvexHull2D::LinearSorter::operator()(const Vector2 &v0, const Vector2 &v1) const {
    if (Abs(v0.x - v1.x) < EPS6) {
      return v0.y < v1.y;
    } else {
      return v0.x < v1.x;
    }
  }

  // ---
  
  float ConvexHull2D::IsLeft(const Vector2 &P0, const Vector2 &P1, const Vector2 &P2) {
    return (P1.x - P0.x)*(P2.y - P0.y) - (P2.x - P0.x)*(P1.y - P0.y);
  }
  
  ConvexHull2D::ConvexHull2D() {
  }
  
  ConvexHull2D::ConvexHull2D(const ConvexHull2D::PointArray &pts, ConvexHull2D::Algorithm algo) {
    compute(pts, algo);
  }
  
  ConvexHull2D::ConvexHull2D(const ConvexHull2D &rhs)
    : mPts(rhs.mPts) {
  }
  
  ConvexHull2D::~ConvexHull2D() {
  }
  
  ConvexHull2D& ConvexHull2D::operator=(const ConvexHull2D &rhs) {
    if (this != &rhs) {
      mPts = rhs.mPts;
    }
    return *this;
  }
  
  void ConvexHull2D::computeGS(const ConvexHull2D::PointArray &inPts) {
    mPts.clear();
    if (inPts.size() <= 1) {
      return;
    }
    size_t i;
    // find rightmost lowest point
    Vector2 rmlPt = inPts[0];
    for (i=1; i<inPts.size(); ++i) {
      if (Abs(inPts[i].y - rmlPt.y) < EPS6) {
        if (inPts[i].x > rmlPt.x) {
          rmlPt = inPts[i];
        }
      } else if (inPts[i].y < rmlPt.y) {
        rmlPt = inPts[i];
      }
    }
    // sort angulary (same angle, discard closest) [using isLeft]
    AngularSorter sorter(rmlPt);
    PointArray pts = inPts;
    std::sort(pts.begin(), pts.end(), sorter);
    // and no here we go !
    mPts.push_back(pts[0]);
    mPts.push_back(pts[1]);
    i = 2;
    while (i < pts.size()) {
      const Vector2 &pi = pts[i];
      if (size() == 1) {
        mPts.push_back(pi);
        ++i;
        continue;
      }
      const Vector2 &p1 = mPts[size()-1];
      const Vector2 &p2 = mPts[size()-2];
      if (IsLeft(p2, p1, pi) > 0) {
        mPts.push_back(pi);
        ++i;
      } else {
        mPts.pop_back();
      }
    }
  }
  
  void ConvexHull2D::computeMC(const ConvexHull2D::PointArray &inPts) {
    // minmin, minmax
    // maxmin, maxmax
    int minmin, minmax, maxmin, maxmax, i, n;
    mPts.clear();
    if (inPts.size() <= 1) {
      return;
    }
    PointArray pts = inPts;
    LinearSorter sorter;
    std::sort(pts.begin(), pts.end(), sorter);
    n = int(pts.size());
    // min x coord points
    i = minmin = 0;
    while (i < n) {
      if (Abs(pts[minmin].x - pts[i].x) >= EPS6) {
        break;
      }
      ++i;
    }
    minmax = i-1;
    if (i == n) {
      // all points have the same x !
      mPts.push_back(pts[minmin]);
      mPts.push_back(pts[minmax]);
      return;
    }
    // max x coord points
    i = maxmax = n - 1;
    while (i >= 0) {
      if (Abs(pts[maxmax].x - pts[i].x) >= EPS6) {
        break;
      }
      --i;
    }
    maxmin = i+1;
    // lower hull (minmin -> maxmin)
    i = minmax;
    mPts.push_back(pts[minmin]);
    while (++i <= maxmin) {
      const Vector2 &pi = pts[i];
      if (IsLeft(pts[minmin], pts[maxmin], pi) >= 0 && i < maxmin) {
        continue;
      }
      while (size() > 1) {
        const Vector2 &p0 = mPts[size()-2];
        const Vector2 &p1 = mPts[size()-1];
        if (IsLeft(p0, p1, pi) > 0) {
          break;
        } else {
          mPts.pop_back();
        }
      }
      mPts.push_back(pi);
    }
    // upper hull (minmax -> maxmax)
    if (maxmax != maxmin) {
      mPts.push_back(pts[maxmax]);
    }
    i = maxmin;
    size_t sz = mPts.size();
    while (--i >= minmax) {
      const Vector2 &pi = pts[i];
      if (IsLeft(pts[maxmax], pts[minmax], pi) >= 0 && i > minmax) {
        continue;
      }
      while (size() > sz) {
        const Vector2 &p0 = mPts[size()-2];
        const Vector2 &p1 = mPts[size()-1];
        if (IsLeft(p0, p1, pi) > 0) {
          break;
        } else {
          mPts.pop_back();
        }
      }
      mPts.push_back(pi);
    }
    if (minmax == minmin) {
      mPts.pop_back();
    }
  }
}
