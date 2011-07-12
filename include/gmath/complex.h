/*

Copyright (C) 2011  Gaetan Guidet

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

#ifndef __gmath_complex_h_
#define __gmath_complex_h_

#include <gmath/config.h>

namespace gmath
{
   template <typename T>
   class Complex
   {
   public:
      
      static const Complex<T> i;
      static const Complex<T> j;
      static const Complex<T> zero;
      
      T re;
      T im;
      
      Complex();
      Complex(const T &r);
      Complex(const T &r, const T &i);
      Complex(const Complex<T> &rhs);
      ~Complex();
      
      
      Complex<T> conjugate() const;
      T squaredNorm() const;
      
      // assignment
      
      Complex<T>& operator=(const Complex<T> &rhs);
      Complex<T>& operator=(const T &r);
      
      // comparison
      
      bool operator==(const Complex<T> &rhs) const;
      bool operator==(const T &r) const;
      
      bool operator!=(const Complex<T> &rhs) const;
      bool operator!=(const T &r) const;
      
      // add
      
      Complex<T>& operator+=(const Complex<T> &rhs);
      Complex<T>& operator+=(const T &r);
      Complex<T> operator+(const Complex<T> &rhs) const;
      Complex<T> operator+(const T &r) const;
      
      // subtract
      
      Complex& operator-=(const Complex<T> &rhs);
      Complex& operator-=(const T &r);
      Complex<T> operator-(const Complex<T> &rhs) const;
      Complex<T> operator-(const T &r) const;
      
      // multiply
      
      Complex<T>& operator*=(const Complex<T> &rhs);
      Complex<T>& operator*=(const T &r);
      Complex<T> operator*(const Complex<T> &rhs) const;
      Complex<T> operator*(const T &r) const;
      
      // divide
      
      Complex<T>& operator/=(const Complex<T> &rhs);
      Complex<T>& operator/=(const T &r);
      Complex<T> operator/(const Complex<T> &rhs) const;
      Complex<T> operator/(const T &r) const;
      
      // opposite
      
      Complex<T> operator-() const;
   };
}

// ---

template <typename T>
bool operator==(const T &r, const gmath::Complex<T> &c)
{
   return (r == c.re && c.im == T(0));
}

template <typename T>
bool operator!=(const T &r, const gmath::Complex<T> &c)
{
   return (r != c.re || c.im != T(0));
}

template <typename T>
gmath::Complex<T> operator+(const T &r, const gmath::Complex<T> &c)
{
   return gmath::Complex<T>(r + c.re, c.im);
}

template <typename T>
gmath::Complex<T> operator-(const T &r, const gmath::Complex<T> &c)
{
   return gmath::Complex<T>(r - c.re, c.im);
}

template <typename T>
gmath::Complex<T> operator*(const T &r, const gmath::Complex<T> &c)
{
   return gmath::Complex<T>(c.re * r, c.im * r);
}


template <typename T>
gmath::Complex<T> operator/(const T &r, const gmath::Complex<T> &c)
{
   T tmp = r / c.squaredNorm();
   return gmath::Complex<T>(tmp * c.re, -tmp * c.im);
}

template <typename T>
std::ostream& operator<<(std::ostream &os, const gmath::Complex<T> &c)
{
   os << "(" << c.re << " + i(" << c.im << "))";
   return os;
}

// ---

template <typename T>
const gmath::Complex<T> gmath::Complex<T>::i(T(0), T(1));

template <typename T>
const gmath::Complex<T> gmath::Complex<T>::j(T(0), T(1));

template <typename T>
const gmath::Complex<T> gmath::Complex<T>::zero(T(0), T(0));


template <typename T>
gmath::Complex<T>::Complex()
   : re(T(0)), im(T(0))
{
}

template <typename T>
gmath::Complex<T>::Complex(const T &r)
   : re(r), im(T(0))
{
}

template <typename T>
gmath::Complex<T>::Complex(const T &r, const T &i)
   : re(r), im(i)
{
}

template <typename T>
gmath::Complex<T>::Complex(const gmath::Complex<T> &rhs)
   : re(rhs.re), im(rhs.im)
{
}

template <typename T>
gmath::Complex<T>::~Complex()
{
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::conjugate() const
{
   return gmath::Complex<T>(re, -im);
}

template <typename T>
T gmath::Complex<T>::squaredNorm() const
{
   return (re * re + im * im);
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator=(const gmath::Complex<T> &rhs)
{
   re = rhs.re;
   im = rhs.im;
   return *this;
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator=(const T &r)
{
   re = r;
   im = T(0);
   return *this;
}

template <typename T>
bool gmath::Complex<T>::operator==(const Complex<T> &rhs) const
{
   return (re == rhs.re && im == rhs.im);
}

template <typename T>
bool gmath::Complex<T>::operator==(const T &r) const
{
   return (re == r && im == T(0));
}

template <typename T>
bool gmath::Complex<T>::operator!=(const gmath::Complex<T> &rhs) const
{
   return (re != rhs.re || im != rhs.im);
}

template <typename T>
bool gmath::Complex<T>::operator!=(const T &r) const
{
   return (re != r || im != T(0));
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator+=(const gmath::Complex<T> &rhs)
{
   re += rhs.re;
   im += rhs.im;
   return *this;
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator+=(const T &r)
{
   re += r;
   return *this;
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator+(const gmath::Complex<T> &rhs) const
{
   return gmath::Complex<T>(re + rhs.re, im + rhs.im);
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator+(const T &r) const
{
   return gmath::Complex<T>(re + r, im);
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator-=(const gmath::Complex<T> &rhs)
{
   re -= rhs.re;
   im -= rhs.im;
   return *this;
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator-=(const T &r)
{
   re -= r;
   return *this;
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator-(const gmath::Complex<T> &rhs) const
{
   return gmath::Complex<T>(re - rhs.re, im - rhs.im);
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator-(const T &r) const
{
   return gmath::Complex<T>(re - r, im);
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator*=(const gmath::Complex<T> &rhs)
{
   // (a + ib) * (c + id)
   // -> ac - bd + i(ad + bc)
   T tmp = re * rhs.re - im * rhs.im;
   im = re * rhs.im + im * rhs.re;
   re = tmp;
   return *this;
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator*=(const T &r)
{
   re *= r;
   im *= r;
   return *this;
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator*(const gmath::Complex<T> &rhs) const
{
   return gmath::Complex<T>(re*rhs.re - im*rhs.im, re*rhs.im + im*rhs.re);
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator*(const T &r) const
{
   return gmath::Complex<T>(re * r, im * r);
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator/=(const gmath::Complex<T> &rhs)
{
   // (a + ib) / (c + id)
   // (a + ib) * (c - id) / (c - id) * (c + id)
   // ac + bd  + i(bc - ad) / (c^2 + d^2)
   T inrm = T(1) / rhs.squaredNorm();
   T tmp = re * rhs.re + im * rhs.im;
   im = inrm * (im * rhs.re - re * rhs.im);
   re = inrm * tmp;
   return *this;
}

template <typename T>
gmath::Complex<T>& gmath::Complex<T>::operator/=(const T &r)
{
   T tmp = T(1) / r;
   re *= tmp;
   im *= tmp;
   return *this;
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator/(const gmath::Complex<T> &rhs) const
{
   T inrm = T(1) / rhs.squaredNorm();
   return gmath::Complex<T>(inrm * (re * rhs.re + im * rhs.im),
                            inrm * (im * rhs.re - re * rhs.im));
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator/(const T &r) const
{
   T tmp = T(1) / r;
   return gmath::Complex<T>(re * tmp, im * tmp);
}

template <typename T>
gmath::Complex<T> gmath::Complex<T>::operator-() const
{
   return gmath::Complex<T>(-re, -im);
}


#endif

