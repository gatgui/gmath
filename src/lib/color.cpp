#include <gmath/color.h>

namespace gmath
{

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

RGB Expand(const RGB &c, NonLinearTransform nlt)
{
   static float sRGBScale = 1.0f / 12.92f;

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
      rgb.r = c.r <= 0.04045f ? c.r * sRGBScale : powf((c.r + 0.055f) / 1.055f, 2.4f);
      rgb.g = c.g <= 0.04045f ? c.g * sRGBScale : powf((c.g + 0.055f) / 1.055f, 2.4f);
      rgb.b = c.b <= 0.04045f ? c.b * sRGBScale : powf((c.b + 0.055f) / 1.055f, 2.4f);
      break;
   case NLT_rec709:
      // TODO
      
   default:
      rgb = c;
   }

   return rgb;
}

RGB Compress(const RGB &c, NonLinearTransform nlt)
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
      rgb.r = c.r <= 0.0031308f ? 12.92f * c.r : 1.055f * powf(c.r, invGamma24) - 0.055f;
      rgb.g = c.g <= 0.0031308f ? 12.92f * c.g : 1.055f * powf(c.g, invGamma24) - 0.055f;
      rgb.b = c.b <= 0.0031308f ? 12.92f * c.b : 1.055f * powf(c.b, invGamma24) - 0.055f;
      break;
   case NLT_rec709:
      // TODO
   default:
      rgb = c;
   }

   return rgb;
}

ColorSpace::ColorSpace(const Chromaticity &r,
                       const Chromaticity &g,
                       const Chromaticity &b,
                       const Chromaticity &w)
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
   : mXYZtoRGB(rhs.mXYZtoRGB)
   , mRGBtoXYZ(rhs.mRGBtoXYZ)
{
}

ColorSpace& ColorSpace::operator=(const ColorSpace &rhs)
{
   if (this != &rhs)
   {
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
