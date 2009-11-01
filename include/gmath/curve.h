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

#ifndef __gmath_curve_h_
#define __gmath_curve_h_

#include <gmath/config.h>
#include <deque>
#include <algorithm>

namespace gmath {
  
  class GMATH_API Curve {
  
    public:
      
      struct GMATH_API Key {
          
        inline Key()
          :pos(0.0f), val(0.0f) {
        }
        
        inline Key(float p, float v)
          :pos(p), val(v) {
        }
        
        inline Key(const Key &rhs)
          :pos(rhs.pos), val(rhs.val) {
        }
        
        inline ~Key() {
        }
        
        Key& operator=(const Key &rhs) {
          pos = rhs.pos;
          val = rhs.val;
          return *this;
        }
        
        inline bool operator<(float p) const {
          return pos < p;
        }
        
        float pos;
        float val;
      };
      
      typedef std::deque<Key> KeyList;
  
      
    public:
      
      Curve();
      Curve(const Curve &);
      ~Curve();
      
      Curve& operator=(const Curve&);
      
      void setEpsilon(float eps) {
        mEpsilon = eps;
        KeyList::iterator it0 = mKeys.begin();
        if (it0 != mKeys.end()) {
          KeyList::iterator it1 = it0 + 1;
          while (it1 != mKeys.end()) {
            if ((it1->pos - it0->pos) < mEpsilon) {
              it0->val = 0.5f * (it0->val + it1->val);
              it1 = mKeys.erase(it1);
            }
            ++it0;
            ++it1;
          }
        }
      }
      
      inline float getEpsilon() const {
        return mEpsilon;
      }
      
      inline int numKeys() const {
        return int(mKeys.size());
      }
      
      int insertKey(const Key &k, bool overwrite=true) {
        KeyList::iterator it = std::lower_bound(mKeys.begin(), mKeys.end(), k.pos);
        if (it != mKeys.end()) {
          if (fabs(it->pos - k.pos) < mEpsilon) {
            if (!overwrite) {
              return -1;
            }
            it->val = k.val;
            return int(it - mKeys.begin());
          }
        }
        if (it != mKeys.begin()) {
          KeyList::iterator pit = it;
          --pit;
          if (fabs(pit->pos - k.pos) < mEpsilon) {
            if (!overwrite) {
              return -1;
            }
            pit->val = k.val;
            return int(pit - mKeys.begin());
          }
        }
        mKeys.insert(it, k);
      }
      
      inline void removeKey(int idx) {
        if (idx >= 0 && idx < numKeys()) {
          mKeys.erase(mKeys.begin() + idx);
        }
      }
      
      // findKey
      // findInterval
      // eval ?
      
      
    protected:
      
      KeyList mKeys;
      float mEpsilon;
  };
  
}

#endif
