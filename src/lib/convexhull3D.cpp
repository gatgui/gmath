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

#include <gmath/convexhull3D.h>
using namespace std;

#define C_NEAR_TOP_LEFT \
  Box::CORNER_FRONT|Box::CORNER_TOP|Box::CORNER_LEFT

#define C_NEAR_TOP_RIGHT \
  Box::CORNER_FRONT|Box::CORNER_TOP|Box::CORNER_RIGHT

#define C_NEAR_BOTTOM_LEFT \
  Box::CORNER_FRONT|Box::CORNER_BOTTOM|Box::CORNER_LEFT

#define C_NEAR_BOTTOM_RIGHT \
  Box::CORNER_FRONT|Box::CORNER_BOTTOM|Box::CORNER_RIGHT

#define C_FAR_TOP_LEFT \
  Box::CORNER_BACK|Box::CORNER_TOP|Box::CORNER_LEFT

#define C_FAR_TOP_RIGHT \
  Box::CORNER_BACK|Box::CORNER_TOP|Box::CORNER_RIGHT

#define C_FAR_BOTTOM_LEFT \
  Box::CORNER_BACK|Box::CORNER_BOTTOM|Box::CORNER_LEFT

#define C_FAR_BOTTOM_RIGHT \
  Box::CORNER_BACK|Box::CORNER_BOTTOM|Box::CORNER_RIGHT


namespace gmath {
  
  ConvexHull3D::ConvexHull3D() {
  }
  
  ConvexHull3D::ConvexHull3D(const ConvexHull3D &rhs)
    :mPolygons(rhs.mPolygons) {
  }
  
  ConvexHull3D::~ConvexHull3D() {
    mPolygons.clear();
  }
  
  ConvexHull3D& ConvexHull3D::operator=(const ConvexHull3D &rhs) {
    if (this != &rhs) {
      mPolygons = rhs.mPolygons;
    }
    return *this;
  }
  
  AABox ConvexHull3D::getAAB() const {
    AABox box;
    for (int i=0; i<getNumPolygons(); ++i) {
      const Polygon &poly = getPolygon(i);
      for (int j=0; j<poly.getNumVertices(); ++j) {
        box.merge(poly.getVertex(j));
      }
    }
    return box;
  }
  
  void ConvexHull3D::from(const Vector3 pts[8]) {
    reset();
    mPolygons.resize(6);
    {
      Polygon &poly = mPolygons[0];
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
    }
    // far
    {
      Polygon &poly = mPolygons[1];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
    }
    // left
    {
      Polygon &poly = mPolygons[2];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
    }
    // right
    {
      Polygon &poly = mPolygons[3];
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // top
    {
      Polygon &poly = mPolygons[4];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // bottom
    {
      Polygon &poly = mPolygons[5];
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
    }
  }

  void ConvexHull3D::from(const Frustum &frustum) {
    reset();
    Vector3 pts[8];
    for (unsigned char i=0; i<8; ++i)  {
      pts[i] = frustum.getCorner(i);
    }
    mPolygons.resize(6);
    // near
    {
      Polygon &poly = mPolygons[0];
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
    }
    // far
    {
      Polygon &poly = mPolygons[1];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
    }
    // left
    {
      Polygon &poly = mPolygons[2];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
    }
    // right
    {
      Polygon &poly = mPolygons[3];
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // top
    {
      Polygon &poly = mPolygons[4];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // bottom
    {
      Polygon &poly = mPolygons[5];
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
    }
  }
  
  void ConvexHull3D::from(const AABox &aab) {
    reset();
    Vector3 pts[8];
    for (unsigned char i=0; i<8; ++i)  {
      pts[i] = aab.getCorner(i);
    }
    mPolygons.resize(6);
    // front
    {
      Polygon &poly = mPolygons[0];
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
    }
    // back
    {
      Polygon &poly = mPolygons[1];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
    }
    // left
    {
      Polygon &poly = mPolygons[2];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
    }
    // right
    {
      Polygon &poly = mPolygons[3];
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // top
    {
      Polygon &poly = mPolygons[4];
      poly.appendVertex(pts[C_FAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_LEFT]);
      poly.appendVertex(pts[C_NEAR_TOP_RIGHT]);
      poly.appendVertex(pts[C_FAR_TOP_RIGHT]);
    }
    // bottom
    {
      Polygon &poly = mPolygons[5];
      poly.appendVertex(pts[C_FAR_BOTTOM_LEFT]);
      poly.appendVertex(pts[C_FAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_RIGHT]);
      poly.appendVertex(pts[C_NEAR_BOTTOM_LEFT]);
    }
  }
  
  void ConvexHull3D::clip(const Frustum &frustum) {
    for (unsigned char i=0; i<6; ++i) {
      clip(frustum.getPlane(i));
    }
  }
  
  void ConvexHull3D::clip(const AABox &aab) {
    for (unsigned char i=0; i<6; ++i) {
      clip(aab.getPlane(i));
    }
  }
  
  void ConvexHull3D::clip(const ConvexHull3D &rhs) {
    Plane plane;
    for (int i=0; i<rhs.getNumPolygons(); ++i) {
      const Polygon &poly = rhs.getPolygon(i);
      if (poly.getNumVertices() >= 3) {
        plane.setup(poly.getVertex(0), poly.getVertex(1), poly.getVertex(2));
        clip(plane);
      }
    }
  }
  
  void ConvexHull3D::clip(const Plane &pl) {
    // for each polygon, check all intersecting edges
    int i, j, k;
    std::vector<Plane::Side> sides;
    ConvexHull3D current = *this;
    reset();
    Polygon::EdgeArray interEdges;
    
    for (i=0; i<current.getNumPolygons(); ++i) {
      const Polygon &poly = current.getPolygon(i);
      if (poly.getNumVertices() < 3) {
        continue;
      }
      Polygon pNew;
      Polygon pInter;
      int nVerts = poly.getNumVertices();
      sides.resize(nVerts);
      for (j=0; j<nVerts; ++j) {
        sides[j] = pl.getSide(poly.getVertex(j));
      }
      for (j=0; j<nVerts; ++j) {
        k = (j+1) % nVerts;
        const Polygon::Vertex &v0 = poly.getVertex(j);
        const Polygon::Vertex &v1 = poly.getVertex(k);
        // well not that easy in fact, considier ON also !
        if (sides[j] != Plane::POSITIVE && sides[k] != Plane::POSITIVE) {
          // both vertex inside
          pNew.appendVertex(v1);
        } else if (sides[j] != Plane::POSITIVE && sides[k] == Plane::POSITIVE) {
          // i inside, k outside --> find intersection
          Ray ray(v1, (v0 - v1).normalize());
          float t;
          if (ray.intersect(pl, &t)) {
            Vector3 ip = ray.getPoint(t);
            pNew.appendVertex(ip);
            pInter.appendVertex(ip);
          }
        } else if (sides[j] == Plane::POSITIVE && sides[k] != Plane::POSITIVE) {
          // i outside, k inside --> find intersection
          Ray ray(v0, (v1 - v0).normalize());
          float t;
          if (ray.intersect(pl, &t)) {
            Vector3 ip = ray.getPoint(t);
            pNew.appendVertex(ip);
            pInter.appendVertex(ip);
          }
          pNew.appendVertex(v1);
        } else {
          // both vertex outside !
          // NOOP
        }
      }
      pNew.removeDoubles();
      if (pNew.getNumVertices() >= 3) {
        // we have a new polygon
        appendPolygon(pNew);
      }
      if (pInter.getNumVertices() == 2) {
        // add a new intersecion edge
        interEdges.push_back(Polygon::Edge(pInter.getVertex(0), pInter.getVertex(1)));
      }
    }
    // ok now we have a list of all intersecting edges
    // must close the hull with that
    if (interEdges.size() >= 3) {
      Polygon pClose;
      Polygon::EdgeIt it = interEdges.begin();
      Polygon::Vertex v0 = it->v0;
      Polygon::Vertex v1 = it->v1;
      interEdges.erase(it);
      // beware of polygon winding ! normal must point same direction as the
      // plane one
      Polygon::Vertex v2;
      // find next vertex [find an edge with one end equal to v1]
      if (findNextAndErase(interEdges, v1, v2)) {
        // figure
        Polygon::Normal n = (v1 - v0).cross(v2 - v1).normalize();
        Polygon::Vertex cur;
        if (n.dot(pl.getNormal()) >= 0) {
          // correct winding
          pClose.appendVertex(v0);
          pClose.appendVertex(v1);
          pClose.appendVertex(v2);
          cur = v2;
        } else {
          pClose.appendVertex(v2);
          pClose.appendVertex(v1);
          pClose.appendVertex(v0);
          cur = v0;
        }
        while (!interEdges.empty()) {
          if (findNextAndErase(interEdges, cur, v2)) {
            if (!interEdges.empty()) {
              pClose.appendVertex(v2);
              cur = v2;
            } else {
              // that was the last one, v2 is already inserted
            }
          } else {
            // degenerated
            break;
          }
        }
        appendPolygon(pClose);
      }
    }
  }
  
  bool ConvexHull3D::findNextAndErase(
    ConvexHull3D::Polygon::EdgeArray &edges,
    const ConvexHull3D::Polygon::Vertex &from,
    ConvexHull3D::Polygon::Vertex &next)
  {
    Polygon::EdgeIt it = edges.begin();
    while (it != edges.end()) {
      if (it->v0 == from) {
        next = it->v1;
        edges.erase(it);
        return true;
      } else if (it->v1 == from) {
        next = it->v0;
        edges.erase(it);
        return true;
      }
      ++it;
    }
    return false;
  }
  
  void ConvexHull3D::add(const Vector3 &pt) {
    // for each polygon test if point is above
    //   if above, store polygon edges and remove it
    // last step is to look for edges that don't have their opposite in the list
    // [so called single edge]
    // for each of them create a new triangle with the point and add it to hull
    Polygon::EdgeArray edges;
    for (int i=0; i<getNumPolygons(); ++i) {
      const Polygon &poly = getPolygon(i);
      if (poly.getNumVertices() == 0) {
        continue;
      }
      Vector3 n = (pt - poly.getVertex(0)).normalize();
      if (n.dot(poly.getNormal()) >= 0) {
        poly.buildEdges(edges);
        deletePolygon(i);
        --i;
      }
    }
    if (edges.empty()) {
      // point lies inside the convex hull
      return;
    }
    // now remove internal edges
    Polygon::EdgeIt cit = edges.begin();
    Polygon::EdgeIt nit;
    bool removed;
    while (cit != edges.end()) {
      nit = cit;
      ++nit;
      removed = false;
      while (nit != edges.end()) {
        if (cit->oppositeOf(*nit)) {
          // remove both edges
          edges.erase(nit);
          cit = edges.erase(cit);
          removed = true;
          break;
        } else {
          ++nit;
        }
      }
      if (!removed) {
        ++cit;
      }
    }
    // for each remaining edge, build a polygon
    int pi = getNumPolygons();
    mPolygons.resize(mPolygons.size()+edges.size());
    while (! edges.empty()) {
      cit = edges.begin();
      Polygon &poly = mPolygons[pi];
      poly.appendVertex(cit->v0);
      poly.appendVertex(cit->v1);
      poly.appendVertex(pt);
      edges.erase(cit);
      ++pi;
    }
  }
  
  void ConvexHull3D::mergePolygons() {
    // For each polygon, find all neighbours and compare normal
    // if normals a close enough merge the polygon into one.
    // If two non-neightbour polygons have the same normal set the dirty flag
    // in order the do one more merge pass
    bool dirty = false; 
    for (int i=0; i<getNumPolygons(); ++i) {
      const Polygon &p0 = getPolygon(i);
      for (int j=i+1; j<getNumPolygons(); ++j) {
        const Polygon &p1 = getPolygon(j);
        if (p0.getNormal().dirEquals(p1.getNormal(), 0.00001f)) {
          // polygon have same normal
          // are they neighbour ? [== do they share an edge]
          bool found = false;
          int nVerts0 = p0.getNumVertices();
          int nVerts1 = p1.getNumVertices();
          for (int k=0; k<nVerts0; ++k) {
            const Polygon::Vertex &cv0 = p0.getVertex(k);
            const Polygon::Vertex &nv0 = p0.getVertex((k+1)%nVerts0);
            for (int l=0; l<nVerts1; ++l) {
              const Polygon::Vertex &cv1 = p1.getVertex(l);
              const Polygon::Vertex &nv1 = p1.getVertex((l+1)%nVerts1);
              if ((cv1 == nv0) && (cv0 == nv1)) {
                // got it !
                found = true;
                Polygon pNew;
                int m;
                for (m=0; m<=k; ++m) {
                  pNew.appendVertex(p0.getVertex(m));
                }
                for (m=l+2; m<=nVerts1; ++m) {
                  pNew.appendVertex(p1.getVertex(m));
                }
                for (m=0; m<=l; ++m) {
                  pNew.appendVertex(p1.getVertex(m));
                }
                for (m=k+2; m<=nVerts0; ++m) {
                  pNew.appendVertex(p0.getVertex(m));
                }
                pNew.removeDoubles();
                deletePolygon(i);
                deletePolygon(j);
                appendPolygon(pNew);
                --i;
                --j;
                break;
              }
            }
            if (found) {
              break;
            }
          }
          if (!found) {
            dirty = true;
            break;
          }
        }
      }
    }
    if (dirty) {
      mergePolygons();
    }
  }

  // ---
  
  PointList::PointList() {
  }
  
  PointList::PointList(const ConvexHull3D &hull) {
    build(hull);
  }
  
  PointList::~PointList() {
    reset();
  }
  
  void PointList::reset() {
    mPoints.clear();
    mAAB.reset();
  }
  
  void PointList::merge(const PointList &rhs) {
    for (size_t i=0; i<rhs.size(); ++i) {
      addPoint(rhs[i]);
    }
  }
  
  void PointList::build(const ConvexHull3D &hull, bool removeDuplicates) {
    reset();
    for (int i=0; i<hull.getNumPolygons(); ++i) {
      const ConvexHull3D::Polygon &poly = hull.getPolygon(i);
      for (int j=0; j<poly.getNumVertices(); ++j) {
        mPoints.push_back(poly.getVertex(j));
      }
    }
    if (removeDuplicates) {
      std::vector<Vector3>::iterator it0 = mPoints.begin();
      std::vector<Vector3>::iterator it1;
      while (it0 != mPoints.end()) {
        it1 = it0 + 1;
        while (it1 != mPoints.end()) {
          if (*it0 == *it1) {
            size_t d = it0 - mPoints.begin();
            it1 = mPoints.erase(it1);
            it0 = mPoints.begin() + d;
            if (it1 == it0) ++it1;
          } else {
            ++it1;
          }
        }
        ++it0;
      }
    }
    mAAB = hull.getAAB();
  }
  
  void PointList::buildAndIncludeDir(
    const ConvexHull3D &hull, const AABox &aab, const Vector3 &dir)
  {
    float t;
    Plane pl[6];
    for (unsigned char c=0; c<6; ++c) {
      pl[c] = aab.getPlane(c);
    }
    Vector3 min = aab.getMin() - Vector3(EPS6);
    Vector3 max = aab.getMax() + Vector3(EPS6);
    build(hull);
    for (size_t i=0; i<size(); ++i) {
      const Vector3 &pt = (*this)[i];
      Ray ray(pt, dir);
      for (unsigned char j=0; j<6; ++j) {
        if (ray.intersect(pl[j], &t)) {
          if (t > 0) {
            Vector3 ptInter = ray.getPoint(t);
            if (ptInter < max && ptInter > min) {
              if (ptInter == pt) {
                continue;
              }
              addPoint(ptInter);
            }
          }
        }
      }
    }
  }
  
  void PointList::addPoint(const Vector3 &p) {
    mPoints.push_back(p);
    mAAB.merge(p);
  }
  
  void PointList::addAAB(const AABox &aab) {
    for (unsigned char i=0; i<8; ++i) {
      addPoint(aab.getCorner(i));
    }
  }  
}

