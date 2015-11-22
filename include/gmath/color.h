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
#include <gmath/vector.h>
#include <gmath/matrix.h>
#include <gmath/details/color.h>

namespace gmath
{
   namespace StandardObserver
   {
      GMATH_DATA_API const float CIE1931[81][3];
      GMATH_DATA_API const float CIE1964[81][3];
   };

   enum ChromaticAdaptationTransform
   {
      CAT_VonKries = 0,
      CAT_Bradford,
      CAT_Sharp,
      CAT_CMC2000,
      CAT_02,
      CAT_XYZ
   };

   typedef details::TColor<details::RGB> RGB;
   typedef details::TColor<details::RGBA> RGBA;
   typedef details::TColor<details::HSV> HSV;
   typedef details::TColor<details::HSL> HSL;
   typedef details::TColor<details::XYZ> XYZ;
   typedef details::TColor<details::LMS> LMS;
   typedef details::TColor<details::YUV> YUV;

   class GMATH_API Chromaticity
   {
   public:
      float x;
      float y;

      Chromaticity();
      Chromaticity(float _x, float _y);
      Chromaticity(const Chromaticity &rhs);

      Chromaticity& operator=(const Chromaticity &rhs);

   public:
      static const Chromaticity IllumA;
      static const Chromaticity IllumB;
      static const Chromaticity IllumC;
      static const Chromaticity IllumD50;
      static const Chromaticity IllumD55;
      static const Chromaticity IllumD65;
      static const Chromaticity IllumD75;
      static const Chromaticity IllumE;
   };

   class GMATH_API Gamma
   {
   public:
      enum NonLinearTransform
      {
         NLT_Gamma22 = 0,
         NLT_Gamma24,
         NLT_sRGB,
         NLT_Rec709,
         NLT_LogCv2 = NLT_Rec709 + 8, // Base exposure level: 800 (160, 200, 250, 320, 400, 500, 640, 800, 1000, 1280, 1600)
         NLT_LogCv3 = NLT_LogCv2 + 11, // Base exposure level: 800 (160, 200, 250, 320, 400, 500, 640, 800, 1000, 1280, 1600)
         NLT_LogC = NLT_LogCv3,
         NLT_Cineon = NLT_LogCv3 + 4
      };

      enum LogCExposureLevel
      {
         EL_160 = -7,
         EL_200 = -6,
         EL_250 = -5,
         EL_320 = -4,
         EL_400 = -3,
         EL_500 = -2,
         EL_640 = -1,
         EL_800 = 0,
         EL_1000 = 1,
         EL_1280 = 2,
         EL_1600 = 3
      };

      // To use LogC gamma with el 160 -> NLT_LogC + EL_160
      static RGB Linearize(const RGB &c, NonLinearTransform nlt=NLT_sRGB);
      static RGB Unlinearize(const RGB &c, NonLinearTransform nlt=NLT_sRGB);
   };

   class GMATH_API ColorSpace
   {
   public:
      ColorSpace(const char *name,
                 const Chromaticity &r,
                 const Chromaticity &g,
                 const Chromaticity &b,
                 const Chromaticity &w);
      ColorSpace(const ColorSpace &rhs);

      ColorSpace& operator=(const ColorSpace &rhs);

      float luminance(const RGB &c) const;

      XYZ RGBtoXYZ(const RGB &rgb) const;
      RGB XYZtoRGB(const XYZ &xyz) const;
      YUV RGBtoYUV(const RGB &rgb) const;
      RGB YUVtoRGB(const YUV &yuv) const;

      const std::string& getName() const;

      void getPrimaries(Chromaticity &r, Chromaticity &g, Chromaticity &b) const;
      const Chromaticity getWhitePoint() const;

      const Matrix3& getRGBtoXYZMatrix() const;
      const Matrix3& getXYZtoRGBMatrix() const;

   public:

      static const ColorSpace Rec709;
      static const ColorSpace NTSC;
      static const ColorSpace SMPTE;
      static const ColorSpace CIE;
      static const ColorSpace UHDTV; // Rec. 2020
      static const ColorSpace DCIP3;
      static const ColorSpace AdobeWide;
      static const ColorSpace AlexaWide;
      static const ColorSpace AdobeRGB;

   private:
      ColorSpace();

      std::string mName;
      Chromaticity mRed;
      Chromaticity mGreen;
      Chromaticity mBlue;
      Chromaticity mWhite;
      Matrix3 mXYZtoRGB;
      Matrix3 mRGBtoXYZ;
   };

   class GMATH_API Blackbody
   {
   public:
      Blackbody(float temperature);

      float operator()(float lambda) const;

      float temperature;

      // Note: Using Blackbody::GetXYZ rather than IntegrateVisibleSpectrum(Blackbody(temp))
      //       enables the use of a cache (1K steps)
      //   The following environment variable controls the caching
      //     GMATH_BLACKBODY_CACHE: enables blackbody cache (0 or 1, 1 by default)
      //     GMATH_BLACKBODY_CACHE_MAX_TEMPERATURE: set the cache max temperature (20000 by default)
      //   Additionally
      //     GMATH_BLACKBODY_STDOBS1964: set to 1 to use CIE Standard Observer 1964 rather than 1931
      static XYZ GetXYZ(float temp);

      // Note: Using Blackbody::GetRGB rather than ColorSpace::XYZtoRGB(Blackbody::GetXYZ())
      //       will remap out of gamut colors (uniform color shifting) and gives you the option
      //       to normalize the color to a human visible range
      static RGB GetRGB(float temp, const ColorSpace &cs, bool normalize=true);
   };

   // ---

   GMATH_API RGB HSLtoRGB(const HSL &hsl);
   GMATH_API RGB HSVtoRGB(const HSV &hsv);

   GMATH_API HSL RGBtoHSL(const RGB &rgb, float epsilon=EPS6);
   GMATH_API HSV RGBtoHSV(const RGB &rgb, float epsilon=EPS6);

   GMATH_API RGBA RGBtoRGBA(const RGB &rgb, float a=1.0f);
   GMATH_API RGB RGBAtoRGB(const RGBA &rgba, bool premult=false);

   GMATH_API float Chroma(const RGB &rgb);
   // GMATH_API float Luminance(const RGB &rgb);
   GMATH_API float Intensity(const RGB &rgb);
   GMATH_API RGB Grade(const RGB &rgb, const RGB &black, const RGB &white, const RGB &lift, const RGB &gain);

   GMATH_API Chromaticity XYZtoChromaticity(const XYZ &xyz);
   GMATH_API XYZ ChromaticityYtoXYZ(const Chromaticity &c, float Y);

   GMATH_API LMS XYZtoLMS(const XYZ &xyz, ChromaticAdaptationTransform cat=CAT_VonKries);
   GMATH_API XYZ LMStoXYZ(const LMS &lms, ChromaticAdaptationTransform cat=CAT_VonKries);
   GMATH_API Matrix3 ChromaticAdaptationMatrix(const XYZ &from, const XYZ &to, ChromaticAdaptationTransform cat=CAT_VonKries);

   template <class SpectralPowerDensityFunc>
   XYZ IntegrateVisibleSpectrum(const SpectralPowerDensityFunc &spd, const float stdobs[81][3]=0)
   {
      if (stdobs == 0)
      {
         stdobs = StandardObserver::CIE1931;
      }

      // Using composite trapezoidal rule to integrate over 80 intervals of 5nm.

      // Add first and last sample contributions
      XYZ rv = 0.5f * (spd(380.0f) * XYZ(stdobs[0]) + spd(780.0f) * XYZ(stdobs[80]));

      // Sum contributions from 385nm to 775nm
      float lambda = 385.0f;
      for (int i=1; i<80; ++i, lambda+=5.0f)
      {
         rv += spd(lambda) * XYZ(stdobs[i]);
      }

      // Multiply by interval length in meters
      rv *= 5e-9f;

      return rv;
   }
}

GMATH_API std::ostream& operator<<(std::ostream &os, const gmath::ColorSpace &cs);

#endif
