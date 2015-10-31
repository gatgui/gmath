/*

Copyright (C) 2015  Gaetan Guidet

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

#ifndef __gmath_color_h__
#define __gmath_color_h__

#include <gmath/config.h>

namespace gmath
{
   namespace details
   {
      class GMATH_API RGB
      {
      public:

         static const int Dim = 3;

         float r;
         float g;
         float b;

         RGB();
         RGB(float v);
         RGB(const float *v);
         RGB(const RGB &rhs);
         ~RGB();

         RGB& operator=(const RGB &rhs);
         operator float* ();
         operator const float* () const;
      };

      class GMATH_API RGBA
      {
      public:

         static const int Dim = 4;

         float r;
         float g;
         float b;
         float a;

         RGBA();
         RGBA(float v);
         RGBA(const float *v);
         RGBA(const RGBA &rhs);
         ~RGBA();

         RGBA& operator=(const RGBA &rhs);
         operator float* ();
         operator const float* () const;
      };

      class GMATH_API HSL
      {
      public:

         static const int Dim = 3;

         float h;
         float s;
         float l;

         HSL();
         HSL(float v);
         HSL(const float *v);
         HSL(const HSL &rhs);
         ~HSL();

         HSL& operator=(const HSL &rhs);
         operator float* ();
         operator const float* () const;
      };

      class GMATH_API HSV
      {
      public:

         static const int Dim = 3;

         float h;
         float s;
         float v;

         HSV();
         HSV(float _v);
         HSV(const float *_v);
         HSV(const HSV &rhs);
         ~HSV();

         HSV& operator=(const HSV &rhs);
         operator float* ();
         operator const float* () const;
      };

      class GMATH_API XYZ
      {
      public:

         static const int Dim = 3;

         float x;
         float y;
         float z;

         XYZ();
         XYZ(float v);
         XYZ(const float *v);
         XYZ(const XYZ &rhs);
         ~XYZ();

         XYZ& operator=(const XYZ &rhs);
         operator float* ();
         operator const float* () const;
      };

      // ---

      inline RGB::RGB() : r(0.0f), g(0.0f), b(0.0f) {}
      inline RGB::RGB(float v) : r(v), g(v), b(v) {}
      inline RGB::RGB(const float *v) : r(v[0]), g(v[1]), b(v[2]) {}
      inline RGB::RGB(const RGB &rhs) : r(rhs.r), g(rhs.g), b(rhs.b) {}
      inline RGB::~RGB() {}
      inline RGB& RGB::operator=(const RGB &rhs) { r = rhs.r; g = rhs.g; b = rhs.b; return *this; }
      inline RGB::operator float* () { return &(this->r); }
      inline RGB::operator const float* () const { return &(this->r); }

      inline RGBA::RGBA() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
      inline RGBA::RGBA(float v) : r(v), g(v), b(v), a(v) {}
      inline RGBA::RGBA(const float *v) : r(v[0]), g(v[1]), b(v[2]), a(v[3]) {}
      inline RGBA::RGBA(const RGBA &rhs) : r(rhs.r), g(rhs.g), b(rhs.b), a(rhs.a) {}
      inline RGBA::~RGBA() {}
      inline RGBA& RGBA::operator=(const RGBA &rhs) { r = rhs.r; g = rhs.g; b = rhs.b; a = rhs.a; return *this; }
      inline RGBA::operator float* () { return &(this->r); }
      inline RGBA::operator const float* () const { return &(this->r); }

      inline HSL::HSL() : h(0.0f), s(0.0f), l(0.0f) {}
      inline HSL::HSL(float v) : h(v), s(v), l(v) {}
      inline HSL::HSL(const float *v) : h(v[0]), s(v[1]), l(v[2]) {}
      inline HSL::HSL(const HSL &rhs) : h(rhs.h), s(rhs.s), l(rhs.l) {}
      inline HSL::~HSL() {}
      inline HSL& HSL::operator=(const HSL &rhs) { h = rhs.h; s = rhs.s; l = rhs.l; return *this; }
      inline HSL::operator float* () { return &(this->h); }
      inline HSL::operator const float* () const { return &(this->h); }

      inline HSV::HSV() : h(0.0f), s(0.0f), v(0.0f) {}
      inline HSV::HSV(float _v) : h(_v), s(_v), v(_v) {}
      inline HSV::HSV(const float *_v) : h(_v[0]), s(_v[1]), v(_v[2]) {}
      inline HSV::HSV(const HSV &rhs) : h(rhs.h), s(rhs.s), v(rhs.v) {}
      inline HSV::~HSV() {}
      inline HSV& HSV::operator=(const HSV &rhs) { h = rhs.h; s = rhs.s; v = rhs.v; return *this; }
      inline HSV::operator float* () { return &(this->h); }
      inline HSV::operator const float* () const { return &(this->h); }

      inline XYZ::XYZ() : x(0.0f), y(0.0f), z(0.0f) {}
      inline XYZ::XYZ(float v) : x(v), y(v), z(v) {}
      inline XYZ::XYZ(const float *v) : x(v[0]), y(v[1]), z(v[2]) {}
      inline XYZ::XYZ(const XYZ &rhs) : x(rhs.x), y(rhs.y), z(rhs.z) {}
      inline XYZ::~XYZ() {}
      inline XYZ& XYZ::operator=(const XYZ &rhs) { x = rhs.x; y = rhs.y; z = rhs.z; return *this; }
      inline XYZ::operator float* () { return &(this->x); }
      inline XYZ::operator const float* () const { return &(this->x); }
   }

   template <class Base>
   class TColor : public Base
   {
   public:

      TColor();
      TColor(float v);
      TColor(const float *v);
      TColor(const TColor<Base> &rhs);
      ~TColor();

      bool operator==(const TColor<Base> &rhs) const;
      bool operator<(const TColor<Base> &rhs) const;
      bool operator<=(const TColor<Base> &rhs) const;
      bool operator!=(const TColor<Base> &rhs) const;
      bool operator>(const TColor<Base> &rhs) const;
      bool operator>=(const TColor<Base> &rhs) const;

      TColor<Base>& operator=(const TColor<Base> &rhs);
      TColor<Base>& operator+=(const TColor<Base> &rhs);
      TColor<Base>& operator+=(float v);
      TColor<Base>& operator-=(const TColor<Base> &rhs);
      TColor<Base>& operator-=(float v);
      TColor<Base>& operator*=(const TColor<Base> &rhs);
      TColor<Base>& operator*=(float v);
      TColor<Base>& operator/=(const TColor<Base> &rhs);
      TColor<Base>& operator/=(float v);
      TColor<Base>& operator^=(const TColor<Base> &rhs);
      TColor<Base>& operator^=(float exponent);

      operator float* ();
      operator const float* () const;

      float dot(const TColor<Base> &rhs) const;
      TColor<Base>& floor(const TColor<Base> &rhs);
      TColor<Base>& floor(float v);
      TColor<Base>& ceil(const TColor<Base> &rhs);
      TColor<Base>& ceil(float v);
   };

   typedef TColor<details::RGB> RGB;
   typedef TColor<details::RGBA> RGBA;
   typedef TColor<details::HSV> HSV;
   typedef TColor<details::HSL> HSL;
   typedef TColor<details::XYZ> XYZ;

   // Other functions here

   GMATH_API RGB HSLtoRGB(const HSL &hsl);
   GMATH_API RGB HSVtoRGB(const HSV &hsv);

   GMATH_API HSL RGBtoHSL(const RGB &rgb, float epsilon=0.000001f);
   GMATH_API HSV RGBtoHSV(const RGB &rgb, float epsilon=0.000001f);

   GMATH_API float Chroma(const RGB &rgb);
   GMATH_API float Luminance(const RGB &rgb);
   GMATH_API float Intensity(const RGB &rgb);
   GMATH_API RGB Grade(const RGB &rgb, const RGB &black, const RGB &white, const RGB &lift, const RGB &gain);

   // RGB <-> RGBA
   // RGB <-> XYZ
   // ColorSpace (chromaticities + white point)
   // Linearize/Unlinearize (Pure gamma curve, Rec 709, sRGB with pseudo gamma curves)

   // ---

// shortcut
#define self (*this)

   template <class Base>
   TColor<Base>::TColor()
      : Base()
   {
   }

   template <class Base>
   TColor<Base>::TColor(float v)
      : Base(v)
   {
   }

   template <class Base>
   TColor<Base>::TColor(const float *v)
      : Base(v)
   {
   }

   template <class Base>
   TColor<Base>::TColor(const TColor<Base> &rhs)
      : Base(rhs)
   {
   }

   template <class Base>
   TColor<Base>::~TColor()
   {
   }

   template <class Base>
   bool TColor<Base>::operator==(const TColor<Base> &rhs) const
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         if (Abs(self[i] - rhs[i]) > EPS6)
         {
            return false;
         }
      }
      return true;
   }

   template <class Base>
   bool TColor<Base>::operator<(const TColor<Base> &rhs) const
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         float d = self[i] - rhs[i];
         if (d < 0.0f)
         {
            return true;
         }
         else if (d > 0.0f)
         {
            return false;
         }
      }
      return false;
   }

   template <class Base>
   bool TColor<Base>::operator<=(const TColor<Base> &rhs) const
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         float d = self[i] - rhs[i];
         if (d < 0.0f)
         {
            return true;
         }
         else if (d > 0.0f)
         {
            return false;
         }
      }
      return true;
   }

   template <class Base>
   inline bool TColor<Base>::operator!=(const TColor<Base> &rhs) const
   {
      return !operator==(rhs);
   }

   template <class Base>
   inline bool TColor<Base>::operator>(const TColor<Base> &rhs) const
   {
      return !operator<=(rhs);
   }

   template <class Base>
   inline bool TColor<Base>::operator>=(const TColor<Base> &rhs) const
   {
      return !operator<(rhs);
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator=(const TColor<Base> &rhs)
   {
      Base::operator=(rhs);
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator+=(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] += rhs[i];
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator+=(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] += v;
      }
      return *this; 
   }
   
   template <class Base>
   TColor<Base>& TColor<Base>::operator-=(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] -= rhs[i];
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator-=(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] -= v;
      }
      return *this;
   }
   
   template <class Base>
   TColor<Base>& TColor<Base>::operator*=(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] *= rhs[i];
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator*=(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] *= v;
      }
      return *this;
   }
   
   template <class Base>
   TColor<Base>& TColor<Base>::operator/=(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] /= rhs[i];
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator/=(float v)
   {
      float iv = 1.0f / v;
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] *= iv;
      }
      return *this;
   }
   
   template <class Base>
   TColor<Base>& TColor<Base>::operator^=(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = powf(self[i], rhs[i]);
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::operator^=(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = powf(self[i], v);
      }
      return *this;
   }

   template <class Base>
   inline TColor<Base>::operator float* ()
   {
      return Base::operator float* ();
   }

   template <class Base>
   inline TColor<Base>::operator const float* () const
   {
      return Base::operator const float* ();
   }

   template <class Base>
   float TColor<Base>::dot(const TColor<Base> &rhs) const
   {
      float rv = 0.0f;
      for (int i=0; i<Base::Dim; ++i)
      {
         rv += self[i] * rhs[i];
      }
      return rv;
   }
   
   template <class Base>
   TColor<Base>& TColor<Base>::floor(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = (self[i] < rhs[i] ? self[i] : rhs[i]);
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::floor(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = (self[i] < v ? self[i] : v);
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::ceil(const TColor<Base> &rhs)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = (self[i] > rhs[i] ? self[i] : rhs[i]);
      }
      return *this;
   }

   template <class Base>
   TColor<Base>& TColor<Base>::ceil(float v)
   {
      for (int i=0; i<Base::Dim; ++i)
      {
         self[i] = (self[i] > v ? self[i] : v);
      }
      return *this;
   }

#undef self

   template <class Base>
   TColor<Base> operator+(const TColor<Base> &c0, const TColor<Base> &c1)
   {
      TColor<Base> rv(c0);
      rv += c1;
      return rv;
   }

   template <class Base>
   TColor<Base> operator+(const TColor<Base> &c0, float v)
   {
      TColor<Base> rv(c0);
      rv += v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator+(float v, const TColor<Base> &c1)
   {
      TColor<Base> rv(c1);
      rv += v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator-(const TColor<Base> &c0, const TColor<Base> &c1)
   {
      TColor<Base> rv(c0);
      rv -= c1;
      return rv;
   }
   
   template <class Base>
   TColor<Base> operator-(const TColor<Base> &c0, float v)
   {
      TColor<Base> rv(c0);
      rv -= v;
      return rv;
   }
   
   template <class Base>
   TColor<Base> operator-(float v, const TColor<Base> &c1)
   {
      TColor<Base> rv(c1);
      rv -= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator*(const TColor<Base> &c0, const TColor<Base> &c1)
   {
      TColor<Base> rv(c0);
      rv *= c1;
      return rv;
   }

   template <class Base>
   TColor<Base> operator*(const TColor<Base> &c0, float v)
   {
      TColor<Base> rv(c0);
      rv *= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator*(float v, const TColor<Base> &c1)
   {
      TColor<Base> rv(c1);
      rv *= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator/(const TColor<Base> &c0, const TColor<Base> &c1)
   {
      TColor<Base> rv(c0);
      rv /= c1;
      return rv;
   }

   template <class Base>
   TColor<Base> operator/(const TColor<Base> &c0, float v)
   {
      TColor<Base> rv(c0);
      rv /= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator/(float v, const TColor<Base> &c1)
   {
      TColor<Base> rv(c1);
      rv /= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator^(const TColor<Base> &c0, const TColor<Base> &c1)
   {
      TColor<Base> rv(c0);
      rv ^= c1;
      return rv;
   }

   template <class Base>
   TColor<Base> operator^(const TColor<Base> &c0, float v)
   {
      TColor<Base> rv(c0);
      rv ^= v;
      return rv;
   }

   template <class Base>
   TColor<Base> operator^(float v, const TColor<Base> &c1)
   {
      TColor<Base> rv(c1);
      rv ^= v;
      return rv;
   }

   template <class Base>
   std::ostream& operator<<(std::ostream &os, const TColor<Base> &c)
   {
      os << "[";
      if (TColor<Base>::Dim > 0)
      {
         os << c[0];
         for (int i=1; i<TColor<Base>::Dim; ++i)
         {
            os << ", " << c[i];
         }
      }
      os << "]";
      return os;
   }

}

#endif
