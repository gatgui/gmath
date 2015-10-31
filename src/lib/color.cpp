#include <gmath/color.h>

namespace gmath
{

float Chroma(const RGB &rgb)
{
   float M = std::max(rgb.r, std::max(rgb.g, rgb.b));
   float m = std::min(rgb.r, std::min(rgb.g, rgb.b));
   return (M - m);
}

float Luminance(const RGB &rgb)
{
   // Rec. 709 (sRGB)
   //return 0.21f * r + 0.72f * g + 0.07 * b;
   // Rec. 601 NTSC
   return (0.3f * rgb.r + 0.59f * rgb.g + 0.11f * rgb.b);
}

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

} // namespace gmath
