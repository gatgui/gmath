/*

Copyright (C) 2009, 2010  Gaetan Guidet

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

#ifndef __gmath_curve_h_
#define __gmath_curve_h_

#include <gmath/config.h>
#include <gmath/vector.h>
#include <gmath/polynomial.h>
#include <sstream>

namespace gmath {
  
  template <typename T>
  struct ValueComp {
    enum {
      Count = 1
    };
    static inline float Get(const T &v, size_t) { return float(v); }
    static inline void Set(T &v, size_t, float nv) { v = (T)nv; }
  };

  template <> struct ValueComp<Vector2> {
    enum {
      Count = 2
    };
    static inline float Get(const Vector2 &v, size_t idx) { return v[idx]; }
    static inline void Set(Vector2 &v, size_t idx, float nv) { v[idx] = nv; }
  };

  template <> struct ValueComp<Vector3> {
    enum {
      Count = 3
    };
    static inline float Get(const Vector3 &v, size_t idx) { return v[idx]; }
    static inline void Set(Vector3 &v, size_t idx, float nv) { v[idx] = nv; }
  };

  template <> struct ValueComp<Vector4> {
    enum {
      Count = 4
    };
    static inline float Get(const Vector4 &v, size_t idx) { return v[idx]; }
    static inline void Set(Vector4 &v, size_t idx, float nv) { v[idx] = nv; }
  };

  // ---

  class GMATH_API Curve {
    
    public:
      
      // interpolation method
      enum Interpolation
      {
        IT_CONSTANT = 0,
        IT_LINEAR,
        IT_SPLINE
      };
      
      // how is the curve repeated out of its time range
      enum Infinity
      {
        IF_CONSTANT = 0,
        IF_LINEAR,
        IF_LOOP,
        IF_LOOP_OFFSET,
        IF_PING_PONG
      };
      
      // tangent presets
      enum Tangent
      {
        T_FLAT = 0,
        T_LINEAR,
        T_SMOOTH,
        T_CUSTOM
      };
      
      static size_t InvalidIndex;
      
    public:
      
      Curve();
      Curve(const Curve &rhs);
      virtual ~Curve();
      
      Curve& operator=(const Curve &rhs);
      
      void setPreInfinity(Infinity it);
      void setPostInfinity(Infinity it);
      Infinity getPreInfinity() const;
      Infinity getPostInfinity() const;
      
    protected:
      
      Infinity mPreInf;
      Infinity mPostInf;
  };
  
  
  template <typename T>
  class TCurve : public Curve {
    public:
      
      struct Key {
        float t;
        T v;
        Interpolation interp;
        Tangent ottype;
        T ot;
        float ow;
        Tangent ittype;
        T it;
        float iw;
      };
      
      typedef typename std::deque<Key> KeyList;
      
    protected:
        
      inline friend bool operator<(const Key &k, float t) {
        return (k.t < t);
      }
      
      void updateTangents(size_t idx) {
        Key &k = mKeys[idx];
        
        T sit = T(0);
        T sot = T(0);
        T lit = T(0);
        T lot = T(0);
        
        if (idx > 0) {
          Key &pk = mKeys[idx-1];
          
          if (idx < (mKeys.size() - 1)) {
            Key &nk = mKeys[idx+1];
            
            lit = (k.v - pk.v) / (k.t - pk.t);
            lot = (nk.v - k.v) / (nk.t - k.t);
            
            float dt = nk.t - pk.t;
            T dv = nk.v - pk.v;
            
            sit = dv / dt;
            sot = sit;
          
          } else {
            lit = (k.v - pk.v) / (k.t - pk.t);
            lot = lit;
            
            sit = lit;
            sot = sit;
          }
        
        } else if (idx + 1 < mKeys.size()) {
          Key &nk = mKeys[idx+1];
          
          lot = (nk.v - k.v) / (nk.t - k.t);
          lit = lot;
          
          sot = lot;
          sit = sot;
        }
        
        if (k.ittype == T_FLAT) {
          k.it = T(0);
          k.iw = 1.0f;
        } else if (k.ittype == T_LINEAR) {
          k.it = lit;
          k.iw = 1.0f;
        } else if (k.ittype == T_SMOOTH) {
          k.it = sit;
          k.iw = 1.0f;
        } else {
          // T_CUSTOM
          // keep value
        }
        
        if (k.ottype == T_FLAT) {
          k.ot = T(0);
          k.ow = 1.0f;
        } else if (k.ottype == T_LINEAR) {
          k.ot = lot;
          k.ow = 1.0f;
        } else if (k.ottype == T_SMOOTH) {
          k.ot = sot;
          k.ow = 1.0f;
        } else {
          // T_CUSTOM
          // keep value
        }
      }
      
      void update(size_t idx) {
        if (idx > 0) {
          updateTangents(idx-1);
          // if first key output tangent is set to smooth, it depends on the second key input tangent
          // second key input tangent may have been re-computed above if it is not set to T_CUSTOM
          if (idx == 2 && mKeys[idx-1].ittype != T_CUSTOM && mKeys[idx-2].ottype == T_SMOOTH) {
            updateTangents(idx-2);
          }
        }
        
        updateTangents(idx);
        
        if (idx+1 < mKeys.size()) {
          updateTangents(idx+1);
          // if last key input tangent is set to smooth, it depends on the second to last key output tangent
          // second to last key output tangent may have been re-computed above if it is not set to T_CUSTOM
          if (idx+3 == mKeys.size() && mKeys[idx+1].ottype != T_CUSTOM && mKeys[idx+2].ittype == T_SMOOTH) {
            updateTangents(idx+2);
          }
        }
      }
      
      bool find(float t, float e, typename KeyList::iterator &it) {
        it = std::lower_bound(mKeys.begin(), mKeys.end(), t);
        
        float dt;
        
        if (it != mKeys.end()) {
          dt = it->t - t;
          if (fabsf(dt) < e) {
            return true;
          }
        }
        
        if (it != mKeys.begin()) {
          dt = t - (it - 1)->t;
          if (fabsf(dt) < e) {
            --it;
            return true;
          }
        }
        
        return false;
      }
      
      bool find(float t, float e, typename KeyList::const_iterator &it) const {
        it = std::lower_bound(mKeys.begin(), mKeys.end(), t);
        
        float dt;
        
        if (it != mKeys.end()) {
          dt = it->t - t;
          if (fabsf(dt) < e) {
            return true;
          }
        }
        
        if (it != mKeys.begin()) {
          dt = t - (it - 1)->t;
          if (fabsf(dt) < e) {
            --it;
            return true;
          }
        }
        
        return false;
      }
      
    public:
      
      TCurve() {
      }
      
      TCurve(const TCurve<T> &rhs)
        : Curve(rhs), mKeys(rhs.mKeys) {
      }
      
      virtual ~TCurve() {
        removeAll();
      }
      
      TCurve& operator=(const TCurve<T> &rhs) {
        if (this != &rhs) {
          Curve::operator=(rhs);
          mKeys = rhs.mKeys;
        }
        return *this;
      }
      
      size_t numKeys() const {
        return mKeys.size();
      }
      
      float tmin() const {
        return (numKeys() > 0 ? mKeys[0].t : 0.0f);
      }
      
      float tmax() const {
        return (numKeys() > 0 ? mKeys.back().t : 0.0f);
      }
      
      float trange() const {
        return (tmax() - tmin());
      }
      
      size_t find(float t, float e=EPS6) const {
        typename KeyList::const_iterator it;
        if (find(t, e, it)) {
          return (it - mKeys.begin());
        } else {
          return InvalidIndex;
        }
      }
      
      size_t insert(float t, T v, bool overwrite=false, float e=EPS6) {
        typename KeyList::iterator it;
        
        if (find(t, e, it)) {
          if (overwrite == false) {
            return (it - mKeys.begin());
          }
          
        } else {
          Key nk;
          
          nk.t = t;
          nk.interp = IT_SPLINE;
          nk.ittype = T_SMOOTH;
          nk.ottype = T_SMOOTH;
          
          it = mKeys.insert(it, nk);
        }
        
        it->v = v;
        
        size_t idx = it - mKeys.begin();
        
        update(idx);
        
        return idx;
      }
      
      void remove(int idx) {
        if (idx < numKeys()) {
          mKeys.erase(mKeys.begin() + idx);
          
          if (idx > 0) {
            updateTangents(idx-1);
            // the first key smooth output tangent depends on second key input tangent
            if (idx == 2 && mKeys[idx-2].ottype == T_SMOOTH) {
              updateTangents(idx-2);
            }
          }
          
          if (idx < mKeys.size()) {
            updateTangents(idx);
            // the last key smooth input tangent depends on second to last key output tangent
            if (idx+2 == mKeys.size() && mKeys[idx+1].ittype == T_SMOOTH) {
              updateTangents(idx+1);
            }
          }
        }
      }
      
      void remove(float t, float e=EPS6) {
        typename KeyList::iterator it;
        
        if (find(t, e, it)) {
          it = mKeys.erase(it);
          
          size_t idx = it - mKeys.begin();
          
          if (idx > 0) {
            updateTangents(idx-1);
            // the first key smooth output tangent depends on second key input tangent
            if (idx == 2 && mKeys[idx-2].ottype == T_SMOOTH) {
              updateTangents(idx-2);
            }
          }
          
          if (idx < mKeys.size()) {
            updateTangents(idx);
            // the last key smooth input tangent depends on second to last key output tangent
            if (idx+2 == mKeys.size() && mKeys[idx+1].ittype == T_SMOOTH) {
              updateTangents(idx+1);
            }
          }
        }
      }
      
      void removeAll() {
        mKeys.clear();
      }
      
      // polies is a polynomial pair for weighted evaluation
      // if not passed, they will be created on stack at each eval call
      T eval(float t, bool weighted=false, Polynomial *polies=NULL) const {
        if (numKeys() == 0) {
          return 0.0f;
        } else if (numKeys() == 1) {
          return mKeys[0].v;
        }
        
        float u;
        T offset = T(0);
        T value = T(0);
        
        float tmin = mKeys.front().t;
        float tmax = mKeys.back().t;
        float trange = tmax - tmin;
        
        // handle pre/post inf
        if (t < tmin) {
          if (mPreInf == IF_CONSTANT) {
            return mKeys[0].v;
            
          } else if (mPreInf == IF_LINEAR) {
            const Key &k0 = mKeys[0];
            const Key &k1 = mKeys[1];
            T slope = T(0);
            
            if (k0.interp == IT_SPLINE) {
              slope = k0.ot / (k1.t - k0.t);
            } else {
              slope = (k1.v - k0.v) / (k1.t - k0.t);
            }
            
            return k0.v + slope * (t - k0.t);
            
          } else {
            u = (t - tmin) / trange;
            
            if (mPreInf == IF_LOOP) {
              t = tmin + (u - floorf(u)) * trange;
              
            } else if (mPreInf == IF_LOOP_OFFSET) {
              float f = floorf(u);
              offset = f * (mKeys.back().v - mKeys.front().v);
              t = tmin + (u - f) * trange;
              
            } else {
              // IF_PING_PONG
              int f = int(floorf(u));
              u = u - f;
              if (f % 2 != 0)
              {
                u = 1.0f - u;
              }
              t = tmin + u * trange;
            }
          }
          
        } else if (t > tmax) {
          if (mPostInf == IF_CONSTANT) {
            return mKeys.back().v;
            
          } else if (mPostInf == IF_LINEAR) {
            const Key &k0 = mKeys[mKeys.size()-2];
            const Key &k1 = mKeys[mKeys.size()-1];
            T slope = T(0);
            
            if (k1.interp == IT_SPLINE) {
              slope = k1.it / (k1.t - k0.t);
            } else {
              slope = (k1.v - k0.v) / (k1.t - k0.t);
            }
            
            return k1.v + slope * (t - k1.t);
            
          } else {
            u = (t - tmin) / trange;
            
            if (mPostInf == IF_LOOP) {
              t = tmin + (u - floorf(u)) * trange;
              
            } else if (mPostInf == IF_LOOP_OFFSET) {
              float f = floorf(u);
              offset = f * (mKeys.back().v - mKeys.front().v);
              t = tmin + (u - f) * trange;
              
            } else {
              int f = int(floorf(u));
              u = u - f;
              if (f % 2 != 0)
              {
                u = 1.0f - u;
              }
              t = tmin + u * trange;
            }
          }
        }
        
        // if we reach here, t has been put back if the [tmin, tmax] range
        // t can take both tmin and tmax value, so check for those 2 cases
        typename KeyList::const_iterator it1 = std::lower_bound(mKeys.begin(), mKeys.end(), t);
        
        if (it1 == mKeys.begin()) {
          value = it1->v;
          
        } else if (it1 == mKeys.end()) {
          value = (it1 - 1)->v;
          
        } else {
          typename KeyList::const_iterator it0 = it1 - 1;
        
          const Key &k0 = *it0;
          const Key &k1 = *it1;

          float dt = k1.t - k0.t;
          u = (t - k0.t) / dt;
        
          if (k0.interp == IT_CONSTANT) {
            value = k0.v;
            
          } else if (k0.interp == IT_LINEAR) {
            value = k0.v + u * (k1.v - k0.v);
            
          } else {
            if (weighted) {
              Polynomial _polies[2];
              int nroots = 0;
              float roots[3];

              T dv = k1.v - k0.v;
              
              float tout = dt * k0.ow;
              float tin = dt * k1.iw;

              T vout = tout * k0.ot;
              T vin = tin * k1.it;

              if (!polies) {
                polies = _polies;
              }

              Polynomial &tpoly = polies[0];
              Polynomial &vpoly = polies[1];

              tpoly.setDegree(3);
              vpoly.setDegree(3);

              tpoly[0] = -u * dt; // -((t - prev) / (next - prev)) * (next - prev) = prev - t
              tpoly[1] = tout;
              tpoly[2] = 3*dt - 2*tout - tin;
              tpoly[3] = -2*dt + tout + tin;

              int iroot = -1;
              // Use the first root in [0,1] range
              // Note: - roots are already sorted by getDegree3Roots
              //       - if more than one root, we may want to smooth out the result
              if (tpoly.getDegree3Roots(nroots, roots)) {
                if (nroots > 1) {
                  std::cout << "t(" << t << "): More than 1 root: " << std::endl;
                  for (int i=0; i<nroots; ++i) {
                    std::cout << "  " << roots[i] << std::endl;
                  }
                }
                for (int i=0; i<nroots; ++i) {
                  if (roots[i] < 0.0f || roots[i] > 1.0f) {
                    continue;
                  }
                  iroot = i;
                  break;
                }
              }

              if (iroot >= 0) {
                float idv, ivout, ivin;
                for (int i=0; i<ValueComp<T>::Count; ++i) {
                  idv = ValueComp<T>::Get(dv, i);
                  ivout = ValueComp<T>::Get(vout, i);
                  ivin = ValueComp<T>::Get(vin, i);
                  vpoly[0] = ValueComp<T>::Get(k0.v, i);
                  vpoly[1] = ivout;
                  vpoly[2] = 3*idv - 2*ivout - ivin;
                  vpoly[3] = -2*idv + ivout + ivin;
                  ValueComp<T>::Set(value, i, vpoly.eval(roots[iroot]));
                }

              } else {
                value = k0.v;
              }

            } else {
              float u2 = u * u;
              float u3 = u * u2;
              float h1 =  2 * u3 - 3 * u2 + 1;
              float h2 = -2 * u3 + 3 * u2;
              float h3 =      u3 - 2 * u2 + u;
              float h4 =      u3 -     u2;
              value = h1 * k0.v +
                      h2 * k1.v +
                      h3 * dt * k0.ot +
                      h4 * dt * k1.it;
            }
          }
        }
        
        return (value + offset);
      }
      
      const Key& getKey(size_t idx) const {
        return mKeys[idx];
      }
      
      const T& getValue(size_t idx) const {
        return mKeys[idx].v;
      }
      
      const T& getInTangent(size_t idx) const {
        return mKeys[idx].it;
      }
      
      const T& getOutTangent(size_t idx) const {
        return mKeys[idx].ot;
      }

      float getOutWeight(size_t idx) const {
        return mKeys[idx].ow;
      }

      float getInWeight(size_t idx) const {
        return mKeys[idx].iw;
      }
      
      Interpolation getInterpolation(size_t idx) const {
        return mKeys[idx].interp;
      }
      
      void setValue(size_t idx, const T &val) {
        mKeys[idx].v = val;
        update(idx);
      }
      
      void setInTangent(size_t idx, Tangent t, const T &val=T(0)) {
        mKeys[idx].ittype = t;
        if (t == T_CUSTOM) {
          mKeys[idx].it = val;
        } else {
          updateTangents(idx);
        }
        // the first key smooth output tangent depends on second key input tangent
        if (idx == 1 && mKeys[idx-1].ottype == T_SMOOTH) {
          updateTangents(idx-1);
        }
      }

      void setInWeight(size_t idx, float w) {
        mKeys[idx].iw = w;
      }
      
      void setOutTangent(size_t idx, Tangent t, const T &val=T(0)) {
        mKeys[idx].ottype = t;
        if (t == T_CUSTOM) {
          mKeys[idx].ot = val;
        } else {
          updateTangents(idx);
        }
        // the last key smooth input tangent depends on second to last key output tangent
        if (idx+2 == mKeys.size() && mKeys[idx+1].ittype == T_SMOOTH) {
          updateTangents(idx+1);
        }
      }

      void setOutWeight(size_t idx, float w) {
        mKeys[idx].ow = w;
      }
       
      void setInterpolation(size_t idx, Interpolation it) {
        mKeys[idx].interp = it;
      }
      
      std::string toString() const {
        static const char *sInterpolationStr[] = {
          "constant",
          "linear",
          "spline"
        };
          
        static const char *sInfinityStr[] = {
          "constant",
          "linear",
          "loop",
          "loop offset",
          "ping pong"
        };
        
        static const char *sTangentStr[] = {
          "flat",
          "linear",
          "smooth",
          "custom"
        };
        
        std::ostringstream os;
        
        os << "pre-infinity = " << sInfinityStr[int(mPreInf)] << ", ";
        os << "post-infinity = " << sInfinityStr[int(mPostInf)] << ", keys = [";
        if (mKeys.size() > 0) {
          os << "(t = " << mKeys[0].t << " -> "
             << mKeys[0].v
             << ", in: " << mKeys[0].it << ":" << mKeys[0].iw << " (" << sTangentStr[int(mKeys[0].ittype)] << ")"
             << ", out: " << mKeys[0].ot << ":" << mKeys[0].ow << " (" << sTangentStr[int(mKeys[0].ottype)] << ")"
             << ", " << sInterpolationStr[int(mKeys[0].interp)] << ")";
          for (size_t i=1; i<mKeys.size(); ++i) {
            os << ", (t = " << mKeys[i].t << " -> "
               << mKeys[i].v
               << ", in: " << mKeys[i].it << ":" << mKeys[i].iw << " (" << sTangentStr[int(mKeys[i].ittype)] << ")"
               << ", out: " << mKeys[i].ot << ":" << mKeys[i].ow << " (" << sTangentStr[int(mKeys[i].ottype)] << ")"
               << ", " << sInterpolationStr[int(mKeys[i].interp)] << ")";
          }
        }
        os << "]";
        
        return os.str();
      }
      
    protected:
      
      KeyList mKeys;
  };
  
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const gmath::TCurve<T> &c) {
  os << c.toString();
  return os;
}

#endif
