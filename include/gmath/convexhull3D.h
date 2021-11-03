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

#ifndef __gmath_convexhull3D_h_
#define __gmath_convexhull3D_h_

#include <gmath/aabox.h>
#include <gmath/frustum.h>
#include <gmath/ray.h>

namespace gmath {
  
  class GMATH_API ConvexHull3D {
    public:
      
      class Polygon {
        public:
          
          typedef Vector3 Vertex;
          typedef std::vector<Vertex> VertexArray;
          typedef VertexArray::iterator VertexIt;
          typedef VertexArray::const_iterator VertexConstIt;
          
          typedef Vector3 Normal;
          
          struct Edge {
            inline Edge() {
            }
            inline Edge(const Vertex &a, const Vertex &b) :v0(a), v1(b) {
            }
            inline Edge(const Edge &rhs) : v0(rhs.v0), v1(rhs.v1) {
            }
            inline ~Edge() {
            }
            inline Edge& operator=(const Edge &rhs) {
              if (this != &rhs) {
                v0 = rhs.v0;
                v1 = rhs.v1;
              }
              return *this;
            }
            inline bool operator==(const Edge &rhs) const {
              return ((v0 == rhs.v0) && (v1 == rhs.v1));
            }
            inline bool operator!=(const Edge &rhs) const {
              return !operator==(rhs);
            }
            inline bool oppositeOf(const Edge &rhs) const {
              return ((v0 == rhs.v1) && (v1 == rhs.v0));
            }
            Vertex v0;
            Vertex v1;
          };
          
          typedef std::vector<Edge> EdgeArray;
          typedef EdgeArray::iterator EdgeIt;
          typedef EdgeArray::const_iterator EdgeConstIt;
          
        public:
          
          inline Polygon() :mNormal(Vector3::ZERO), mDirty(true) {
          }
          inline Polygon(const Polygon &rhs)
            :mVertices(rhs.mVertices), mNormal(rhs.mNormal), mDirty(rhs.mDirty) {
          }
          inline ~Polygon() {
          }
          inline Polygon& operator=(const Polygon &rhs) {
            if (this != &rhs) {
              mVertices = rhs.mVertices;
              mNormal = rhs.mNormal;
              mDirty = rhs.mDirty;
            }
            return *this;
          }
          inline const Normal& getNormal() const {
            return (mDirty ? updateNormal() : mNormal);
          }
          inline int getNumVertices() const {
            return (int)(mVertices.size());
          }
          inline const Vertex& getVertex(int i) const {
            return mVertices[i];
          }
          inline void setVertex(int i, const Vertex &v) {
            if (i>=0 && i<getNumVertices()) {
              mDirty = true;
              mVertices[i] = v;
            }
          }
          inline void insertVertex(int i, const Vertex &v) {
            VertexIt it = mVertices.begin() + i;
            mVertices.insert(it, v);
          }
          inline void prependVertex(const Vertex &v) {
            insertVertex(0, v);
          }
          inline void appendVertex(const Vertex &v) {
            insertVertex(getNumVertices(), v);
          }
          inline void deleteVertex(int i) {
            VertexIt it = mVertices.begin() + i;
            mVertices.erase(it);
          }
          inline void reset() {
            mVertices.clear();
            mNormal = Vector3::ZERO;
            mDirty = true;
          }
          inline void removeDoubles() {
            VertexIt nit = mVertices.begin();
            VertexIt cit = nit++;
            if (cit == mVertices.end()) {
              return;
            }
            while (nit != mVertices.end()) {
              if (*cit == *nit) {
                nit = mVertices.erase(cit);
                cit = nit++;
              } else {
                ++cit;
                ++nit;
              }
            }
          }
          inline void buildEdges(EdgeArray &edges) const {
            int n = getNumVertices();
            if (n >= 2) {
              --n;
              for (int i=0; i<n; ++i) {
                edges.push_back(Edge(getVertex(i), getVertex(i+1)));
              }
              edges.push_back(Edge(getVertex(n), getVertex(0)));
            }
          }
          
        private:
          
          inline const Normal& updateNormal() const {
            if (getNumVertices() >= 3) {
              Vector3 e0 = (getVertex(1) - getVertex(0)).normalize();
              Vector3 e1 = (getVertex(2) - getVertex(1)).normalize();
              mNormal = (e0.cross(e1)).normalize();
              mDirty = false;
            }
            return mNormal;
          }
          
          VertexArray mVertices;
          mutable Normal mNormal;
          mutable bool mDirty;
      };
      
      typedef std::vector<Polygon> PolygonArray;
      typedef PolygonArray::iterator PolygonIt;
      typedef PolygonArray::const_iterator PolygonConstIt;
  
    public:
  
      ConvexHull3D();
      inline ConvexHull3D(const Frustum &f) {
        from(f);
      }
      inline ConvexHull3D(const AABox &b) {
        from(b);
      }
      inline ConvexHull3D(const Vector3 b[8]) {
        from(b);
      }
      ConvexHull3D(const ConvexHull3D &rhs);
      ~ConvexHull3D();
      
      ConvexHull3D& operator=(const ConvexHull3D &rhs);
      
      void from(const Frustum &f);
      void from(const AABox &b);
      void from(const Vector3 box[8]); // with same ordering as AABox of Frustum
      
      void clip(const Frustum &f);
      void clip(const AABox &b);
      void clip(const ConvexHull3D &rhs);
      void clip(const Plane &p);
      
      void add(const Vector3 &pt);
      
      void mergePolygons();
      
      inline void reset() {
        mPolygons.clear();
      }
      inline int getNumPolygons() const {
        return (int)(mPolygons.size());
      }
      inline const Polygon& getPolygon(int i) const {
        return mPolygons[i];
      }
      
      // TOTEST: mergePolygons

      AABox getAAB() const;
      
    private:
      
      inline void insertPolygon(int i, const Polygon &p) {
        PolygonIt it = mPolygons.begin() + i;
        mPolygons.insert(it, p);
      }
      inline void appendPolygon(const Polygon &p) {
        insertPolygon(getNumPolygons(), p);
      }
      inline void prependPolygon(const Polygon &p) {
        insertPolygon(0, p);
      }
      inline void deletePolygon(int i) {
        PolygonIt it = mPolygons.begin() + i;
        mPolygons.erase(it);
      }
      bool findNextAndErase(
        Polygon::EdgeArray &edges,
        const Polygon::Vertex &from,
        Polygon::Vertex &next);
      
      PolygonArray mPolygons;
  };
  
  class GMATH_API PointList {
    public:
  
      PointList();
      PointList(const ConvexHull3D &hull);
      ~PointList();
      
      void reset();
      
      void merge(const PointList &rhs);
      void build(const ConvexHull3D &hull, bool removeDuplicates=true);
      void buildAndIncludeDir(const ConvexHull3D &hull, const AABox &aab, const Vector3 &dir);
      void addPoint(const Vector3 &p);
      void addAAB(const AABox &aab);
      
      inline const AABox& getAAB() const {
        return mAAB;
      }
      inline size_t size() const {
        return mPoints.size();
      }
      inline const Vector3& operator[](size_t i) const {
        return mPoints[i];
      }
      inline PointList& transform(const Matrix4 &M) {
        mAAB.reset();
        for (size_t i=0; i<mPoints.size(); ++i) {
          mPoints[i] = M * mPoints[i];
          mAAB.merge(mPoints[i]);
        }
        return *this;
      }
      
    protected:
      
      std::vector<Vector3> mPoints;
      AABox mAAB;
  };
  
}

inline gmath::PointList operator*(const gmath::Matrix4 &m, const gmath::PointList &pts) {
  gmath::PointList tmp(pts);
  return tmp.transform(m);
}

#endif
