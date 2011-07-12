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

#ifndef __gmath_fft_h_
#define __gmath_fft_h_

#include <gmath/complex.h>

namespace gmath
{
   class GMATH_API FFT
   {
   private:
      
      template <typename T>
      static void Swap(T &a, T &b);
      
      static void ReverseIncrement(int N, int &cnt);
      
      static bool IsPowerOf2(int N);
      
      template <typename T>
      static void Scale(int N, T scl, T *data, int stride=1);
      
      template <typename T>
      static void Transform(int N, Complex<T> *data, bool inverse, int stride=1);
      
   public:
      
      // Utilities
      
      template <typename T>
      static void BitReverseSort(int N, T *data, int stride=1);
      
      template <typename T>
      static void BitReverseSort(int N, const T *src, T *dst, int srcStride=1, int dstStride=1);
      
      // 1D
      
      template <typename T>
      static bool Forward(int N, const Complex<T> *src, Complex<T> *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Forward(int N, Complex<T> *data, int stride=1);
      
      template <typename T>
      static bool Inverse(int N, const Complex<T> *src, Complex<T> *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Inverse(int N, Complex<T> *data, int stride=1);
      
      // 2D
      // takes a 1D array whose elements are arranged row major format (dimension W)
      
      template <typename T>
      static bool Forward(int W, int H, const T *src, T *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Forward(int W, int H, T *data, int stride=1);
      
      template <typename T>
      static bool Inverse(int W, int H, const T *src, T *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Inverse(int W, int H, T *data, int stride=1);
      
      // 3D
      // takes a 1D array whose elements are arranged row (dimension W) then column (dimension H) major format
      
      template <typename T>
      static bool Forward(int W, int H, int D, const T *src, T *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Forward(int W, int H, int D, T *data, int stride=1);
      
      template <typename T>
      static bool Inverse(int W, int H, int D, const T *src, T *dst, int srcStride=1, int dstStride=1);
      
      template <typename T>
      static bool Inverse(int W, int H, int D, int N, T *data, int stride=1);
   };
}

// ---

template <typename T>
inline void gmath::FFT::Swap(T &a, T &b)
{
   T tmp = a;
   a = b;
   b = tmp;
}

inline void gmath::FFT::ReverseIncrement(int N, int &cnt)
{
  // adds 1 to highest order bit propagating carry
  // to the right
  
  while (cnt & (N >>= 1))
  {
    cnt &= ~N;
  }
  cnt |= N;
}

bool gmath::FFT::IsPowerOf2(int N)
{
   return ((N & (N - 1)) == 0);
}

template <typename T>
void gmath::FFT::BitReverseSort(int N, T *data, int stride)
{
   // Naive approach: compute bit reversed i inside the for loop
   //
   // int j = i;
   // int hMask = hN;
   // int lMask = 0x01;
   // while (hMask > lMask)
   // {
   //    j = (j & ~(hMask | lMask)) | ((j & hMask) ? lMask : 0) | ((j & lMask) ? hMask : 0);
   //    hMask >>= 1;
   //    lMask <<= 1;
   // }
   
   for (int i=0, j=0, k=0; i<N; ++i, k+=stride)
   {
      if (j > i)
      {
         Swap(data[k], data[j*stride]);
      }
      ReverseIncrement(N, j);
   }
}

template <typename T>
void gmath::FFT::BitReverseSort(int N, const T *src, T *dst, int srcStride, int dstStride)
{
   for (int i=0, j=0, k=0; i<N; ++i, k+=srcStride)
   {
      dst[j*dstStride] = src[k];
      ReverseIncrement(N, j);
   }
}

template <typename T>
void gmath::FFT::Scale(int N, T scl, T *data, int stride)
{
   for (int i=0, j=0; i<N; ++i, j+=stride)
   {
      data[j] *= scl;
   }
}

template <typename T>
void gmath::FFT::Transform(int N, Complex<T> *data, bool inverse, int stride)
{
   int sm = 0;
   int step = 1;
   int sstep = stride;
   int period = 0;
   int speriod = 0;
   double angle = 0.0;
   double angleScale = (inverse ? 2.0 : -2.0) * M_PI;
   Complex<T> factor, factorStep, product;
   
   while (period < N)
   {
      period = step << 1;
      speriod = sstep << 1;
      
      angle = angleScale / double(period);
      
      factor = Complex<T>(T(1));
      factorStep = Complex<T>(T(cos(angle)), T(sin(angle)));
      
      for (int f=0, sf=0; f<step; ++f, sf+=stride)
      {
         for (int n=f, sn=sf; n<N; n+=period, sn+=speriod)
         {
            sm = sn + sstep;
            product = factor * data[sm];
            data[sm] = data[sn] - product;
            data[sn] += product;
         }
         
         factor = factor * factorStep;
      }
      
      step = period; // == step <<= 1;
      sstep = step * stride;
   }
   
   if (inverse)
   {
      Scale(N, Complex<T>(T(1.0 / double(N))), data, stride);
   }
}

template <typename T>
bool gmath::FFT::Forward(int N, Complex<T> *data, int stride)
{
   if (!data || N <= 0 || !IsPowerOf2(N))
   {
      return false;
   }
   BitReverseSort(N, data, stride);
   Transform(N, data, false, stride);
   return true;
}

template <typename T>
bool gmath::FFT::Forward(int N, const Complex<T> *src, Complex<T> *dst, int srcStride, int dstStride)
{
   if (!src || !dst || N <= 0 || !IsPowerOf2(N))
   {
      return false;
   }
   BitReverseSort(N, src, dst, srcStride, dstStride);
   Transform(N, dst, false, dstStride);
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int N, Complex<T> *data, int stride)
{
   if (!data || N <= 0 || !IsPowerOf2(N))
   {
      return false;
   }
   BitReverseSort(N, data, stride);
   Transform(N, data, true, stride);
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int N, const Complex<T> *src, Complex<T> *dst, int srcStride, int dstStride)
{
   if (!src || !dst || N <= 0 || !IsPowerOf2(N))
   {
      return false;
   }
   BitReverseSort(N, src, dst, srcStride, dstStride);
   Transform(N, dst, true, dstStride);
   return true;
}

template <typename T>
bool gmath::FFT::Forward(int W, int H, const T *src, T *dst, int srcStride, int dstStride)
{
   if (!src || !dst || W <= 0 || H <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H))
   {
      return false;
   }
   
   int srcRowStride = srcStride * W;
   int dstRowStride = dstStride * W;
   
   for (int y=0, srcOff=0, dstOff=0; y<H; ++y, srcOff+=srcRowStride, dstOff+=dstRowStride)
   {
      Forward(W, src+srcOff, dst+dstOff, srcStride, dstStride);
   }
   
   for (int x=0, off=0; x<W; ++x, off+=dstStride)
   {
      Forward(H, dst+off, dstRowStride);
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Forward(int W, int H, T *data, int stride)
{
   if (!data || W <= 0 || H <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H))
   {
      return false;
   }
   
   int rowStride = stride * W;
   
   for (int y=0, off=0; y<H; ++y, off+=rowStride)
   {
      Forward(W, data+off, stride);
   }
   
   for (int x=0, off=0; x<W; ++x, off+=stride)
   {
      Forward(H, data+off, rowStride);
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int W, int H, const T *src, T *dst, int srcStride, int dstStride)
{
   if (!src || !dst || W <= 0 || H <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H))
   {
      return false;
   }
   
   int srcRowStride = srcStride * W;
   int dstRowStride = dstStride * W;
   
   for (int y=0, srcOff=0, dstOff=0; y<H; ++y, srcOff+=srcRowStride, dstOff+=dstRowStride)
   {
      Inverse(W, src+srcOff, dst+dstOff, srcStride, dstStride);
   }
   
   for (int x=0, off=0; x<W; ++x, off+=dstStride)
   {
      Inverse(H, dst+off, dstRowStride);
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int W, int H, T *data, int stride)
{
   if (!data || W <= 0 || H <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H))
   {
      return false;
   }
   
   int rowStride = stride * W;
   
   for (int y=0, off=0; y<H; ++y, off+=rowStride)
   {
      Inverse(W, data+off, stride);
   }
   
   for (int x=0, off=0; x<W; ++x, off+=stride)
   {
      Inverse(H, data+off, rowStride);
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Forward(int W, int H, int D, const T *src, T *dst, int srcStride, int dstStride)
{
   if (!src || !dst || W <= 0 || H <= 0 || D <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H) || !IsPowerOf2(D))
   {
      return false;
   }
   
   int srcRowStride = W * srcStride;
   int srcColStride = H * srcRowStride;
   int dstRowStride = W * dstStride;
   int dstColStride = H * dstRowStride;
   
   // Process each 2D slide
   for (int d=0, srcOff=0, dstOff=0; d<D; ++d, srcOff+=srcColStride, dstOff+=dstColStride)
   {
      Forward(W, H, src+srcOff, dst+dstOff, srcStride, dstStride);
   }
   
   // Process each X/Y plane sample along depth
   for (int y=0, off=0; y<H; ++y)
   {
      for (int x=0; x<W; ++x, off+=dstStride)
      {
         Forward(D, dst+off, dstColStride);
      }
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Forward(int W, int H, int D, T *data, int stride)
{
   if (!data || W <= 0 || H <= 0 || D <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H) || !IsPowerOf2(D))
   {
      return false;
   }
   
   int rowStride = W * stride;
   int colStride = H * rowStride;
   
   // Process each 2D slide
   for (int d=0, off=0; d<D; ++d, off+=colStride)
   {
      Forward(W, H, data+off, stride);
   }
   
   // Process each X/Y plane sample along depth
   for (int y=0, off=0; y<H; ++y)
   {
      for (int x=0; x<W; ++x, off+=stride)
      {
         Forward(D, data+off, colStride);
      }
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int W, int H, int D, const T *src, T *dst, int srcStride, int dstStride)
{
   if (!src || !dst || W <= 0 || H <= 0 || D <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H) || !IsPowerOf2(D))
   {
      return false;
   }
   
   int srcRowStride = W * srcStride;
   int srcColStride = H * srcRowStride;
   int dstRowStride = W * dstStride;
   int dstColStride = H * dstRowStride;
   
   // Process each 2D slide
   for (int d=0, srcOff=0, dstOff=0; d<D; ++d, srcOff+=srcColStride, dstOff+=dstColStride)
   {
      Inverse(W, H, src+srcOff, dst+dstOff, srcStride, dstStride);
   }
   
   // Process each X/Y plane sample along depth
   for (int y=0, off=0; y<H; ++y)
   {
      for (int x=0; x<W; ++x, off+=dstStride)
      {
         Inverse(D, dst+off, dstColStride);
      }
   }
   
   return true;
}

template <typename T>
bool gmath::FFT::Inverse(int W, int H, int D, int N, T *data, int stride)
{
   if (!data || W <= 0 || H <= 0 || D <= 0 || !IsPowerOf2(W) || !IsPowerOf2(H) || !IsPowerOf2(D))
   {
      return false;
   }
   
   int rowStride = W * stride;
   int colStride = H * rowStride;
   
   // Process each 2D slide
   for (int d=0, off=0; d<D; ++d, off+=colStride)
   {
      Inverse(W, H, data+off, stride);
   }
   
   // Process each X/Y plane sample along depth
   for (int y=0, off=0; y<H; ++y)
   {
      for (int x=0; x<W; ++x, off+=stride)
      {
         Inverse(D, data+off, colStride);
      }
   }
   
   return true;
}

#endif

