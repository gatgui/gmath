/*
MIT License

Copyright (c) 2015 Gaetan Guidet

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


#ifndef __gmath_details_color_h__
#define __gmath_details_color_h__

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

      class GMATH_API LMS
      {
      public:

         static const int Dim = 3;

         float l;
         float m;
         float s;

         LMS();
         LMS(float v);
         LMS(const float *v);
         LMS(const LMS &rhs);
         ~LMS();

         LMS& operator=(const LMS &rhs);
         operator float* ();
         operator const float* () const;
      };

      class GMATH_API YUV
      {
      public:

         static const int Dim = 3;

         float y;
         float u;
         float v;

         YUV();
         YUV(float v);
         YUV(const float *v);
         YUV(const YUV &rhs);
         ~YUV();

         YUV& operator=(const YUV &rhs);
         operator float* ();
         operator const float* () const;
      };
      
      class GMATH_API LAB
      {
      public:

         static const int Dim = 3;

         float l;
         float a;
         float b;

         LAB();
         LAB(float v);
         LAB(const float *v);
         LAB(const LAB &rhs);
         ~LAB();

         LAB& operator=(const LAB &rhs);
         operator float* ();
         operator const float* () const;
      };
      
      class GMATH_API LUV
      {
      public:

         static const int Dim = 3;

         float l;
         float u;
         float v;

         LUV();
         LUV(float v);
         LUV(const float *v);
         LUV(const LUV &rhs);
         ~LUV();

         LUV& operator=(const LUV &rhs);
         operator float* ();
         operator const float* () const;
      };

      template <class Base>
      class TColor : public Base
      {
      public:

         TColor();
         TColor(float v1);
         TColor(float v1, float v2);
         TColor(float v1, float v2, float v3);
         TColor(float v1, float v2, float v3, float v4);
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
         TColor<Base> operator-() const;
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

      inline LMS::LMS() : l(0.0f), m(0.0f), s(0.0f) {}
      inline LMS::LMS(float v) : l(v), m(v), s(v) {}
      inline LMS::LMS(const float *v) : l(v[0]), m(v[1]), s(v[2]) {}
      inline LMS::LMS(const LMS &rhs) : l(rhs.l), m(rhs.m), s(rhs.s) {}
      inline LMS::~LMS() {}
      inline LMS& LMS::operator=(const LMS &rhs) { l = rhs.l; m = rhs.m; s = rhs.s; return *this; }
      inline LMS::operator float* () { return &(this->l); }
      inline LMS::operator const float* () const { return &(this->l); }

      inline YUV::YUV() : y(0.0f), u(0.0f), v(0.0f) {}
      inline YUV::YUV(float v) : y(v), u(v), v(v) {}
      inline YUV::YUV(const float *v) : y(v[0]), u(v[1]), v(v[2]) {}
      inline YUV::YUV(const YUV &rhs) : y(rhs.y), u(rhs.u), v(rhs.v) {}
      inline YUV::~YUV() {}
      inline YUV& YUV::operator=(const YUV &rhs) { y = rhs.y; u = rhs.u; v = rhs.v; return *this; }
      inline YUV::operator float* () { return &(this->y); }
      inline YUV::operator const float* () const { return &(this->y); }
      
      inline LAB::LAB() : l(0.0f), a(0.0f), b(0.0f) {}
      inline LAB::LAB(float v) : l(v), a(v), b(v) {}
      inline LAB::LAB(const float *v) : l(v[0]), a(v[1]), b(v[2]) {}
      inline LAB::LAB(const LAB &rhs) : l(rhs.l), a(rhs.a), b(rhs.b) {}
      inline LAB::~LAB() {}
      inline LAB& LAB::operator=(const LAB &rhs) { l = rhs.l; a = rhs.a; b = rhs.b; return *this; }
      inline LAB::operator float* () { return &(this->l); }
      inline LAB::operator const float* () const { return &(this->l); }
      
      inline LUV::LUV() : l(0.0f), u(0.0f), v(0.0f) {}
      inline LUV::LUV(float _v) : l(_v), u(_v), v(_v) {}
      inline LUV::LUV(const float *_v) : l(_v[0]), u(_v[1]), v(_v[2]) {}
      inline LUV::LUV(const LUV &rhs) : l(rhs.l), u(rhs.u), v(rhs.v) {}
      inline LUV::~LUV() {}
      inline LUV& LUV::operator=(const LUV &rhs) { l = rhs.l; u = rhs.u; v = rhs.v; return *this; }
      inline LUV::operator float* () { return &(this->l); }
      inline LUV::operator const float* () const { return &(this->l); }

#define self (*this)

      template <class Base>
      TColor<Base>::TColor()
         : Base()
      {
      }

      template <class Base>
      TColor<Base>::TColor(float v1)
         : Base(v1)
      {
      }

      template <class Base>
      TColor<Base>::TColor(float v1, float v2)
         : Base()
      {
         switch (Base::Dim > 2 ? 2 : Base::Dim)
         {
         case 2:
            self[1] = v2;
         case 1:
            self[0] = v1;
         default:
            break;
         }
      }

      template <class Base>
      TColor<Base>::TColor(float v1, float v2, float v3)
         : Base()
      {
         switch (Base::Dim > 3 ? 3 : Base::Dim)
         {
         case 3:
            self[2] = v3;
         case 2:
            self[1] = v2;
         case 1:
            self[0] = v1;
         default:
            break;
         }
      }

      template <class Base>
      TColor<Base>::TColor(float v1, float v2, float v3, float v4)
         : Base()
      {
         switch (Base::Dim > 4 ? 4 : Base::Dim)
         {
         case 4:
            self[3] = v4;
         case 3:
            self[2] = v3;
         case 2:
            self[1] = v2;
         case 1:
            self[0] = v1;
         default:
            break;
         }
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
      TColor<Base> TColor<Base>::operator-() const
      {
         TColor<Base> rv;
         for (int i=0; i<Base::Dim; ++i)
         {
            rv[i] = -self[i];
         }
         return rv;
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
   }
}

template <class Base>
gmath::details::TColor<Base> operator+(const gmath::details::TColor<Base> &c0, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c0);
   rv += c1;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator+(const gmath::details::TColor<Base> &c0, float v)
{
   gmath::details::TColor<Base> rv(c0);
   rv += v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator+(float v, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c1);
   rv += v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator-(const gmath::details::TColor<Base> &c0, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c0);
   rv -= c1;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator-(const gmath::details::TColor<Base> &c0, float v)
{
   gmath::details::TColor<Base> rv(c0);
   rv -= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator-(float v, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c1);
   rv -= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator*(const gmath::details::TColor<Base> &c0, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c0);
   rv *= c1;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator*(const gmath::details::TColor<Base> &c0, float v)
{
   gmath::details::TColor<Base> rv(c0);
   rv *= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator*(float v, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c1);
   rv *= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator/(const gmath::details::TColor<Base> &c0, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c0);
   rv /= c1;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator/(const gmath::details::TColor<Base> &c0, float v)
{
   gmath::details::TColor<Base> rv(c0);
   rv /= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator/(float v, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c1);
   rv /= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator^(const gmath::details::TColor<Base> &c0, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c0);
   rv ^= c1;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator^(const gmath::details::TColor<Base> &c0, float v)
{
   gmath::details::TColor<Base> rv(c0);
   rv ^= v;
   return rv;
}

template <class Base>
gmath::details::TColor<Base> operator^(float v, const gmath::details::TColor<Base> &c1)
{
   gmath::details::TColor<Base> rv(c1);
   rv ^= v;
   return rv;
}

template <class Base>
std::ostream& operator<<(std::ostream &os, const gmath::details::TColor<Base> &c)
{
   os << "(";
   if (gmath::details::TColor<Base>::Dim > 0)
   {
      os << c[0];
      for (int i=1; i<gmath::details::TColor<Base>::Dim; ++i)
      {
         os << ", " << c[i];
      }
   }
   os << ")";
   return os;
}

#endif
