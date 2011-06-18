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

#ifndef __gmath_linsys_h_
#define __gmath_linsys_h_

#include <gmath/vector.h>

namespace gmath {

  template <unsigned int dim>
  class LinearSystem {
    public:
      
      LinearSystem(float eps=EPS6) : EPS(eps) {
        assert(dim > 1);
      }
      
      LinearSystem(const LinearSystem<dim> &rhs) :EPS(rhs.EPS) {
        assert(dim > 1);
        for (unsigned int i=0; i<dim; ++i) {
          matrix[i] = rhs.matrix[i];
        }
      }
      
      ~LinearSystem() {
      }
      
      LinearSystem<dim>& operator=(const LinearSystem<dim> &rhs) {
        if (this != &rhs) {
          for (unsigned int i=0; i<dim; ++i) {
            matrix[i] = rhs.matrix[i];
          }
          EPS = rhs.EPS;
        }
        return *this;
      }
      
      Vector<dim+1>& operator[](unsigned int i) {
        return matrix[i];
      }
      
      const Vector<dim+1>& operator[](unsigned int i) const {
        return matrix[i];
      }
      
      void setEpsilon(float eps) {
        EPS = eps;
      }
      
      void setEq(unsigned int i, const float *lhs, float rhs) {
        Vector<dim+1> tmp;
        for (unsigned int j=0; j<dim; ++j) {
          tmp[j] = lhs[j];
        }
        tmp[dim] = rhs;
        matrix[i] = tmp;
      }
      
      void setEq(unsigned int i, const Vector<dim> &lhs, float rhs) {
        Vector<dim+1> tmp;
        for (unsigned int j=0; j<dim; ++j) {
          tmp[j] = lhs[j];
        }
        tmp[dim] = rhs;
        matrix[i] = tmp;
      }
      
      // in the following 2 rows are augmented with the rhs of the equation
      
      void setEq(unsigned int i, const Vector<dim+1> &v) {
        matrix[i] = v;
      }
      
      void setEq(unsigned int i, const float *v) {
        matrix[i].set(v);
      }
      
      bool solve(Vector<dim> &result) {
        unsigned int i, j, k;
        unsigned int ccol = 0;
        unsigned int crow = 0;
        unsigned int mrow = 0;
        float cval;
        float mval;
        
        // initialize result
        for (i=0; i<dim; ++i) {
          rmatrix[i] = matrix[i];
        }
        
        // gauss-jordan reduction
        for (ccol=0; ccol<dim; ++ccol) {
          
          mrow = ccol;
          mval = cval = Abs(rmatrix[mrow][ccol]);
          
          // select pivot
          for (crow=ccol+1; crow<dim; ++crow) {
            cval = Abs(rmatrix[crow][ccol]);
            if (cval > mval) {
              mval = cval;
              mrow = crow;
            }
          }
          
          // check if pivot is valid
          if (mval >= EPS) {
            
            float factor = 1.0f / rmatrix[mrow][ccol];
          
            swap(ccol, mrow);
          
            for (crow=ccol; crow<dim; ++crow) {
              rmatrix[crow] *= factor;
            }
          
            for (crow=ccol+1; crow<dim; ++crow) {
              factor = rmatrix[crow][ccol];
              rmatrix[crow] -= (factor * rmatrix[ccol]);
            }
          } else {
            // maximum value on this column is zero, cannot reduce
            // should swap column here maybe
          }
        }
        
        // Now can backsubstitute
        //   - beware of stability
        //   - what if we have a zero ?
        //   - can optimize crow/ccol and use the same
        
        result.zero();
        
        j = dim-1;
        
        if (Abs(rmatrix[j][j]) >= EPS) {
          result[j] = rmatrix[j][dim];
        }
        
        while (j > 0) {
          --j;
          result[j] = rmatrix[j][dim];
          for (k=dim-1; k>j; --k) {
            result[j] -= rmatrix[j][k] * result[k];
          }
        }
        
        return true;
      }
    
    protected:
      
      void swap(unsigned int i, unsigned int j) {
        Vector<dim+1> tmp = rmatrix[i];
        rmatrix[i] = rmatrix[j];
        rmatrix[j] = tmp;
      }
      
      void multiply(unsigned int i, float s) {
        rmatrix[i] *= s;
      }
      
      Vector<dim+1> matrix[dim]; //rows : augmented
      Vector<dim+1> rmatrix[dim]; // rmatrix is the matrix to be modified
      
      float EPS;
  };

}


template <unsigned int d>
inline std::ostream& operator<<(std::ostream &os, const gmath::LinearSystem<d> l) {
  os << "LinSys{";
  for (unsigned int i=0; i<d; ++i) {
    os << "{" << l[i] << "}" << std::endl;
  }
  os << "}";
  return os;
}

#endif

