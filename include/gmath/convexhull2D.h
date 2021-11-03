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

#ifndef __gmath_convexhull2D_h_
#define __gmath_convexhull2D_h_

#include <gmath/vector.h>

namespace gmath {
  
  class GMATH_API ConvexHull2D {
    public:
      
      enum Algorithm {
        GRAHAM_SCAN = 0,
        MONOTONE_CHAIN
      };
      
      typedef std::vector<Vector2> PointArray;
      
      ConvexHull2D();
      ConvexHull2D(const PointArray &pts, Algorithm algo=GRAHAM_SCAN);
      ConvexHull2D(const ConvexHull2D &rhs);
      ~ConvexHull2D();
      
      ConvexHull2D& operator=(const ConvexHull2D &rhs);
      
      inline void compute(const PointArray &pts, Algorithm algo = GRAHAM_SCAN) {
        algo == GRAHAM_SCAN ? computeGS(pts) : computeMC(pts);
      }
      
      inline size_t size() const {
        return mPts.size();
      }
      
      inline const Vector2& operator[](size_t i) const {
        return mPts[i];
      }
      
      static float IsLeft(const Vector2 &P0, const Vector2 &P1, const Vector2 &P2);
      
    protected:
      
      struct LinearSorter {
        LinearSorter();
        LinearSorter(const LinearSorter &rhs);
        LinearSorter& operator=(const LinearSorter &rhs);
        bool operator()(const Vector2 &v0, const Vector2 &v1) const;
      };
      
      struct AngularSorter {
        AngularSorter();
        AngularSorter(const Vector2 &rml);
        AngularSorter(const AngularSorter &rhs);
        AngularSorter& operator=(const AngularSorter &rhs);
        bool operator()(const Vector2 &v0, const Vector2 &v1) const;
        private:
          Vector2 mRML;
      };
    
    protected:
      
      void computeGS(const PointArray &inPts);
      void computeMC(const PointArray &inPts);
      
      PointArray mPts;
  };

}

GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::ConvexHull2D &hull);

#endif
