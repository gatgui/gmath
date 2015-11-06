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

#include <gmath/color.h>

namespace gmath
{

const float SpectrumMin = 380.0f;
const float SpectrumMax = 780.0f;
const float SpectrumStep = 5.0f;

const float CIEStdObs1931[81][3] = {
  {0.001368f, 0.000039f, 0.006450f},
  {0.002236f, 0.000064f, 0.010550f},
  {0.004243f, 0.000120f, 0.020050f},
  {0.007650f, 0.000217f, 0.036210f},
  {0.014310f, 0.000396f, 0.067850f},
  {0.023190f, 0.000640f, 0.110200f},
  {0.043510f, 0.001210f, 0.207400f},
  {0.077630f, 0.002180f, 0.371300f},
  {0.134380f, 0.004000f, 0.645600f},
  {0.214770f, 0.007300f, 1.039050f},
  {0.283900f, 0.011600f, 1.385600f},
  {0.328500f, 0.016840f, 1.622960f},
  {0.348280f, 0.023000f, 1.747060f},
  {0.348060f, 0.029800f, 1.782600f},
  {0.336200f, 0.038000f, 1.772110f},
  {0.318700f, 0.048000f, 1.744100f},
  {0.290800f, 0.060000f, 1.669200f},
  {0.251100f, 0.073900f, 1.528100f},
  {0.195360f, 0.090980f, 1.287640f},
  {0.142100f, 0.112600f, 1.041900f},
  {0.095640f, 0.139020f, 0.812950f},
  {0.057950f, 0.169300f, 0.616200f},
  {0.032010f, 0.208020f, 0.465180f},
  {0.014700f, 0.258600f, 0.353300f},
  {0.004900f, 0.323000f, 0.272000f},
  {0.002400f, 0.407300f, 0.212300f},
  {0.009300f, 0.503000f, 0.158200f},
  {0.029100f, 0.608200f, 0.111700f},
  {0.063270f, 0.710000f, 0.078250f},
  {0.109600f, 0.793200f, 0.057250f},
  {0.165500f, 0.862000f, 0.042160f},
  {0.225750f, 0.914850f, 0.029840f},
  {0.290400f, 0.954000f, 0.020300f},
  {0.359700f, 0.980300f, 0.013400f},
  {0.433450f, 0.994950f, 0.008750f},
  {0.512050f, 1.000000f, 0.005750f},
  {0.594500f, 0.995000f, 0.003900f},
  {0.678400f, 0.978600f, 0.002750f},
  {0.762100f, 0.952000f, 0.002100f},
  {0.842500f, 0.915400f, 0.001800f},
  {0.916300f, 0.870000f, 0.001650f},
  {0.978600f, 0.816300f, 0.001400f},
  {1.026300f, 0.757000f, 0.001100f},
  {1.056700f, 0.694900f, 0.001000f},
  {1.062200f, 0.631000f, 0.000800f},
  {1.045600f, 0.566800f, 0.000600f},
  {1.002600f, 0.503000f, 0.000340f},
  {0.938400f, 0.441200f, 0.000240f},
  {0.854450f, 0.381000f, 0.000190f},
  {0.751400f, 0.321000f, 0.000100f},
  {0.642400f, 0.265000f, 0.000050f},
  {0.541900f, 0.217000f, 0.000030f},
  {0.447900f, 0.175000f, 0.000020f},
  {0.360800f, 0.138200f, 0.000010f},
  {0.283500f, 0.107000f, 0.000000f},
  {0.218700f, 0.081600f, 0.000000f},
  {0.164900f, 0.061000f, 0.000000f},
  {0.121200f, 0.044580f, 0.000000f},
  {0.087400f, 0.032000f, 0.000000f},
  {0.063600f, 0.023200f, 0.000000f},
  {0.046770f, 0.017000f, 0.000000f},
  {0.032900f, 0.011920f, 0.000000f},
  {0.022700f, 0.008210f, 0.000000f},
  {0.015840f, 0.005723f, 0.000000f},
  {0.011359f, 0.004102f, 0.000000f},
  {0.008111f, 0.002929f, 0.000000f},
  {0.005790f, 0.002091f, 0.000000f},
  {0.004109f, 0.001484f, 0.000000f},
  {0.002899f, 0.001047f, 0.000000f},
  {0.002049f, 0.000740f, 0.000000f},
  {0.001440f, 0.000520f, 0.000000f},
  {0.001000f, 0.000361f, 0.000000f},
  {0.000690f, 0.000249f, 0.000000f},
  {0.000476f, 0.000172f, 0.000000f},
  {0.000332f, 0.000120f, 0.000000f},
  {0.000235f, 0.000085f, 0.000000f},
  {0.000166f, 0.000060f, 0.000000f},
  {0.000117f, 0.000042f, 0.000000f},
  {0.000083f, 0.000030f, 0.000000f},
  {0.000059f, 0.000021f, 0.000000f},
  {0.000042f, 0.000015f, 0.000000f}
};

float Chroma(const RGB &rgb)
{
   float M = std::max(rgb.r, std::max(rgb.g, rgb.b));
   float m = std::min(rgb.r, std::min(rgb.g, rgb.b));
   return (M - m);
}

// float Luminance(const RGB &rgb)
// {
//    // Rec. 709 (sRGB)
//    //return 0.21f * r + 0.72f * g + 0.07 * b;
//    // Rec. 601 NTSC
//    return (0.3f * rgb.r + 0.59f * rgb.g + 0.11f * rgb.b);
// }

float Intensity(const RGB &rgb)
{
   static float aThird = 1.0f / 3.0f;

   return ((rgb.r + rgb.g + rgb.b) * aThird);
}

RGB Grade(const RGB &rgb, const RGB &black, const RGB &white, const RGB &lift, const RGB &gain)
{
   RGB wbdiff(white);
   wbdiff -= black;

   RGB gldiff(gain);
   gldiff -= lift;

   RGB rv(rgb);
   rv -= black;
   rv /= wbdiff;
   rv *= gldiff;
   rv += lift;

   return rv;
}

HSL RGBtoHSL(const RGB &rgb, float epsilon)
{
   HSL hsl;

   float M = std::max(rgb.r, std::max(rgb.g, rgb.b));
   float m = std::min(rgb.r, std::min(rgb.g, rgb.b));
   float C = M - m;

   hsl.h = 0;
   hsl.s = 0;
   hsl.l = 0.5 * (m + M);

   if (C >= epsilon)
   {
      if (hsl.l <= 0.5)
      {
         hsl.s = C / (2 * hsl.l);
      }
      else
      {
         hsl.s = C / (2 * (1 - hsl.l));
      }

      if (M == rgb.r)
      {
         hsl.h = (rgb.g - rgb.b) / C;
      }
      else if (M == rgb.g)
      {
         hsl.h = (rgb.b - rgb.r) / C + 2;
      }
      else
      {
         hsl.h = (rgb.r - rgb.g) / C + 4;
      }

      static float sNormalizeHue = 60.0 / 360.0;

      hsl.h *= sNormalizeHue;

      if (hsl.h < 0)
      {
         hsl.h += 1;
      }
   }

   return hsl;
}

HSV RGBtoHSV(const RGB &rgb, float epsilon)
{
   HSV hsv;

   float M = std::max(rgb.r, std::max(rgb.g, rgb.b));
   float m = std::min(rgb.r, std::min(rgb.g, rgb.b));
   float C = M - m;

   hsv.h = 0;
   hsv.s = 0;
   hsv.v = M;

   if (M >= epsilon)
   {
      hsv.s = C / M;
   }

   if (hsv.s >= epsilon)
   {
      if (M == rgb.r)
      {
         hsv.h = (rgb.g - rgb.b) / C;
      }
      else if (M == rgb.g)
      {
         hsv.h = (rgb.b - rgb.r) / C + 2;
      }
      else
      {
         hsv.h = (rgb.r - rgb.g) / C + 4;
      }

      static float sNormalizeHue = 60.0 / 360.0;

      hsv.h *= sNormalizeHue;

      if (hsv.h < 0)
      {
         hsv.h += 1;
      }
   }

   return hsv;
}

RGB HSVtoRGB(const HSV &hsv)
{
   RGB rgb;

   float C = hsv.v * hsv.s;
   float h = hsv.h * 6;
   float X = C * (1 - fabs(fmod(h, 2) - 1));

   if (h < 1)
   {
      rgb.r = C;
      rgb.g = X;
      rgb.b = 0;
   }
   else if (h < 2)
   {
      rgb.r = X;
      rgb.g = C;
      rgb.b = 0;
   }
   else if (h < 3)
   {
      rgb.r = 0;
      rgb.g = C;
      rgb.b = X;
   }
   else if (h < 4)
   {
      rgb.r = 0;
      rgb.g = X;
      rgb.b = C;
   }
   else if (h < 5)
   {
      rgb.r = X;
      rgb.g = 0;
      rgb.b = C;
   }
   else
   {
      rgb.r = C;
      rgb.g = 0;
      rgb.b = X;
   }

   float m = hsv.v - C;

   rgb.r += m;
   rgb.g += m;
   rgb.b += m;

   return rgb;
}

RGB HSLtoRGB(const HSL &hsl)
{
   RGB rgb;

   float C;

   if (hsl.l <= 0.5)
   {
      C = 2 * hsl.l * hsl.s;
   }
   else
   {
      C = (2 - 2 * hsl.l) * hsl.s;
   }

   float h = hsl.h * 6;
   float X = C * (1 - fabs(fmod(h, 2) - 1));

   if (h < 1)
   {
      rgb.r = C;
      rgb.g = X;
      rgb.b = 0;
   }
   else if (h < 2)
   {
      rgb.r = X;
      rgb.g = C;
      rgb.b = 0;
   }
   else if (h < 3)
   {
      rgb.r = 0;
      rgb.g = C;
      rgb.b = X;
   }
   else if (h < 4)
   {
      rgb.r = 0;
      rgb.g = X;
      rgb.b = C;
   }
   else if (h < 5)
   {
      rgb.r = X;
      rgb.g = 0;
      rgb.b = C;
   }
   else
   {
      rgb.r = C;
      rgb.g = 0;
      rgb.b = X;
   }

   float m = hsl.l - 0.5 * C;

   rgb.r += m;
   rgb.g += m;
   rgb.b += m;

   return rgb;
}

RGBA RGBtoRGBA(const RGB &rgb, float a)
{
   RGBA rgba;
   rgba.r = rgb.r;
   rgba.g = rgb.g;
   rgba.b = rgb.b;
   rgba.a = a;
   return rgba;
}

RGB RGBAtoRGB(const RGBA &rgba, bool premult)
{
   RGB rgb;
   rgb.r = rgba.r;
   rgb.g = rgba.g;
   rgb.b = rgba.b;
   if (premult)
   {
      rgb.r *= rgba.a;
      rgb.g *= rgba.a;
      rgb.b *= rgba.a;
   }
   return rgb;
}

RGB Linearize(const RGB &c, NonLinearTransform nlt)
{
   static float sRGBScale = 1.0f / 12.92f;
   static float Rec709Scale = 1.0f / 4.5f;
   static float Rec709Power = 1.0f / 0.45f;

   RGB rgb;

   switch (nlt)
   {
   case NLT_Gamma22:
      rgb.r = powf(c.r, 2.2f);
      rgb.g = powf(c.g, 2.2f);
      rgb.b = powf(c.b, 2.2f);
      break;
   case NLT_Gamma24:
      rgb.r = powf(c.r, 2.4f);
      rgb.g = powf(c.g, 2.4f);
      rgb.b = powf(c.b, 2.4f);
      break;
   case NLT_sRGB:
      // https://en.wikipedia.org/wiki/SRGB
      rgb.r = c.r <= 0.04045f ? c.r * sRGBScale : powf((c.r + 0.055f) / 1.055f, 2.4f);
      rgb.g = c.g <= 0.04045f ? c.g * sRGBScale : powf((c.g + 0.055f) / 1.055f, 2.4f);
      rgb.b = c.b <= 0.04045f ? c.b * sRGBScale : powf((c.b + 0.055f) / 1.055f, 2.4f);
      break;
   case NLT_Rec709:
      // https://en.wikipedia.org/wiki/Rec._709
      rgb.r = c.r < 0.081f ? c.r * Rec709Scale : powf((c.r + 0.099f) / 1.099f, Rec709Power);
      rgb.g = c.g < 0.081f ? c.g * Rec709Scale : powf((c.g + 0.099f) / 1.099f, Rec709Power);
      rgb.b = c.b < 0.081f ? c.b * Rec709Scale : powf((c.b + 0.099f) / 1.099f, Rec709Power);
      break;

   default:
      rgb = c;
   }

   return rgb;
}

RGB Unlinearize(const RGB &c, NonLinearTransform nlt)
{
   static float invGamma22 = 1.0f / 2.2f;
   static float invGamma24 = 1.0f / 2.4f;

   RGB rgb;

   switch (nlt)
   {
   case NLT_Gamma22:
      rgb.r = powf(c.r, invGamma22);
      rgb.g = powf(c.g, invGamma22);
      rgb.b = powf(c.b, invGamma22);
      break;
   case NLT_Gamma24:
      rgb.r = powf(c.r, invGamma24);
      rgb.g = powf(c.g, invGamma24);
      rgb.b = powf(c.b, invGamma24);
      break;
   case NLT_sRGB:
      // https://en.wikipedia.org/wiki/SRGB
      rgb.r = c.r <= 0.0031308f ? 12.92f * c.r : 1.055f * powf(c.r, invGamma24) - 0.055f;
      rgb.g = c.g <= 0.0031308f ? 12.92f * c.g : 1.055f * powf(c.g, invGamma24) - 0.055f;
      rgb.b = c.b <= 0.0031308f ? 12.92f * c.b : 1.055f * powf(c.b, invGamma24) - 0.055f;
      break;
   case NLT_Rec709:
      // https://en.wikipedia.org/wiki/Rec._709
      rgb.r = c.r < 0.018f ? 4.5f * c.r : 1.099f * powf(c.r, 0.45f) - 0.099f;
      rgb.g = c.g < 0.018f ? 4.5f * c.g : 1.099f * powf(c.g, 0.45f) - 0.099f;
      rgb.b = c.b < 0.018f ? 4.5f * c.b : 1.099f * powf(c.b, 0.45f) - 0.099f;
      break;

   default:
      rgb = c;
   }

   return rgb;
}

// https://en.wikipedia.org/wiki/Standard_illuminant
const Chromaticity Chromaticity::IllumA(0.44757f, 0.40745f);
const Chromaticity Chromaticity::IllumB(0.34842f, 0.35161f);
const Chromaticity Chromaticity::IllumC(0.31006f, 0.31616f);
const Chromaticity Chromaticity::IllumD50(0.34567f, 0.35850f);
const Chromaticity Chromaticity::IllumD55(0.33242f, 0.34743f);
const Chromaticity Chromaticity::IllumD65(0.31271f, 0.32902f);
const Chromaticity Chromaticity::IllumD75(0.29902f, 0.31485f);
const Chromaticity Chromaticity::IllumE(1.0f/3.0f, 1.0f/3.0f);

Chromaticity GetChromaticity(const XYZ &xyz)
{
   float isum = 1.0f / (xyz.x + xyz.y + xyz.z);
   return Chromaticity(xyz.x * isum, xyz.y * isum);
}

XYZ GetXYZ(const Chromaticity &c, float Y)
{
   XYZ rv;

   float iy = 1.0f / c.y;

   rv.x = Y * iy * c.x;
   rv.y = Y;
   rv.z = Y * iy * (1.0f - c.x - c.y);

   return rv;
}


// https://en.wikipedia.org/wiki/Rec._709
const ColorSpace ColorSpace::Rec709("Rec. 709",
                                    Chromaticity(0.64f, 0.33f),
                                    Chromaticity(0.30f, 0.60f),
                                    Chromaticity(0.15f, 0.06f),
                                    Chromaticity::IllumD65);
// https://en.wikipedia.org/wiki/NTSC#SMPTE_C
const ColorSpace ColorSpace::NTSC("NTSC 1953",
                                  Chromaticity(0.67f, 0.33f),
                                  Chromaticity(0.21f, 0.71f),
                                  Chromaticity(0.14f, 0.08f),
                                  Chromaticity::IllumC);
const ColorSpace ColorSpace::SMPTE("SMPTE C",
                                   Chromaticity(0.63f, 0.34f),
                                   Chromaticity(0.31f, 0.595f),
                                   Chromaticity(0.155f, 0.07f),
                                   Chromaticity::IllumD65);
// https://en.wikipedia.org/wiki/RGB_color_space
// http://www.brucelindbloom.com/index.html?WorkingSpaceInfo.html
// http://linuxtv.org/downloads/v4l-dvb-apis/ch02s06.html
// http://www.poynton.com/notes/colour_and_gamma/ColorFAQ.html
const ColorSpace ColorSpace::CIE("CIE RGB",
                                 Chromaticity(0.7347f, 0.2653f),
                                 Chromaticity(0.2738f, 0.7174f),
                                 Chromaticity(0.1666f, 0.0089f),
                                 Chromaticity::IllumE);
const ColorSpace ColorSpace::UHDTV("UHDTV",
                                   Chromaticity(0.708f, 0.292f),
                                   Chromaticity(0.17f, 0.797f),
                                   Chromaticity(0.131f, 0.046f),
                                   Chromaticity::IllumD65);
const ColorSpace ColorSpace::DCIP3("DCI-P3",
                                   Chromaticity(0.68f, 0.32f),
                                   Chromaticity(0.265f, 0.69f),
                                   Chromaticity(0.15f, 0.06f),
                                   Chromaticity(0.314f, 0.351f));

ColorSpace::ColorSpace(const char *name,
                       const Chromaticity &r,
                       const Chromaticity &g,
                       const Chromaticity &b,
                       const Chromaticity &w)
   : mName(name)
   , mRed(r)
   , mGreen(g)
   , mBlue(b)
   , mWhite(w)
{
   Vector3 X(r.x, r.y, 1.0f - (r.x + r.y));
   Vector3 Y(g.x, g.y, 1.0f - (g.x + g.y));
   Vector3 Z(b.x, b.y, 1.0f - (b.x + b.y));
   Vector3 W(w.x, w.y, 1.0f - (w.x + w.y));

   mRGBtoXYZ.setColumn(0, X);
   mRGBtoXYZ.setColumn(1, Y);
   mRGBtoXYZ.setColumn(2, Z);

   W /= w.y;

   Vector3 scl = mRGBtoXYZ.getInverse() * W;

   mRGBtoXYZ.setColumn(0, scl.x * mRGBtoXYZ.getColumn(0));
   mRGBtoXYZ.setColumn(1, scl.y * mRGBtoXYZ.getColumn(1));
   mRGBtoXYZ.setColumn(2, scl.z * mRGBtoXYZ.getColumn(2));

   mXYZtoRGB = mRGBtoXYZ.getInverse();
}

ColorSpace::ColorSpace(const ColorSpace &rhs)
   : mName(rhs.mName)
   , mRed(rhs.mRed)
   , mGreen(rhs.mGreen)
   , mBlue(rhs.mBlue)
   , mWhite(rhs.mWhite)
   , mXYZtoRGB(rhs.mXYZtoRGB)
   , mRGBtoXYZ(rhs.mRGBtoXYZ)
{
}

ColorSpace& ColorSpace::operator=(const ColorSpace &rhs)
{
   if (this != &rhs)
   {
      mName = rhs.mName;
      mRed = rhs.mRed;
      mGreen = rhs.mGreen;
      mBlue = rhs.mBlue;
      mWhite = rhs.mWhite;
      mXYZtoRGB = rhs.mXYZtoRGB;
      mRGBtoXYZ = rhs.mRGBtoXYZ;
   }
   return *this;
}

float ColorSpace::luminance(const RGB &rgb) const
{
   XYZ xyz = RGBtoXYZ(rgb);
   return xyz.y;
}

XYZ ColorSpace::RGBtoXYZ(const RGB &rgb) const
{
   return XYZ(mRGBtoXYZ * Vector3(rgb));
}

RGB ColorSpace::XYZtoRGB(const XYZ &xyz) const
{
   return RGB(mXYZtoRGB * Vector3(xyz));
}

} // namespace gmath

std::ostream& operator<<(std::ostream &os, const gmath::ColorSpace &cs)
{
   gmath::Chromaticity r, g, b, w;

   cs.getPrimaries(r, g, b);
   w = cs.getWhitePoint();

   os << "ColorSpace \"" << cs.getName() << "\"" << std::endl;
   os << "  Primaries" << std::endl;
   os << "    Red: (" << r.x << ", " << r.y << ")" << std::endl;
   os << "    Green: (" << g.x << ", " << g.y << ")" << std::endl;
   os << "    Blue: (" << b.x << ", " << b.y << ")" << std::endl;
   os << "  White point: (" << w.x << ", " << w.y << ")" << std::endl;
   os << "  XYZ -> RGB" << std::endl;
   os << "    " << cs.getXYZtoRGBMatrix() << std::endl;
   os << "  RGB -> XYZ" << std::endl;
   os << "    " << cs.getRGBtoXYZMatrix();
   return os;
}
