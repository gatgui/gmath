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
