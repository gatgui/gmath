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

