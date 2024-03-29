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

#ifndef __gmath_color_h__
#define __gmath_color_h__

#include <gmath/config.h>
#include <gmath/vector.h>
#include <gmath/matrix.h>
#include <gmath/details/color.h>
#include <gmath/params.h>

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
   typedef details::TColor<details::LAB> LAB;
   typedef details::TColor<details::LUV> LUV;

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
      static const Chromaticity IllumD60;
      static const Chromaticity IllumD65;
      static const Chromaticity IllumD75;
      static const Chromaticity IllumE;
   };

   class GMATH_API Gamma
   {
   public:
      enum Function
      {
         Power22 = 0,
         Power24,
         sRGB,
         Rec709, // == 10 bits Rec2020
         LogCv2 = Rec709 + 8, // Base exposure level: 800 (160, 200, 250, 320, 400, 500, 640, 800, 1000, 1280, 1600)
         LogCv3 = LogCv2 + 11, // Base exposure level: 800 (160, 200, 250, 320, 400, 500, 640, 800, 1000, 1280, 1600)
         LogC = LogCv3,
         Cineon = LogCv3 + 4,
         Rec2020 // == 12 bits Rec2020
      };
      
      // LogC exposure levels
      enum ExposureLevel
      {
         EL160 = -7,
         EL200 = -6,
         EL250 = -5,
         EL320 = -4,
         EL400 = -3,
         EL500 = -2,
         EL640 = -1,
         EL800 = 0,
         EL1000 = 1,
         EL1280 = 2,
         EL1600 = 3
      };

      // To use LogC gamma with el 160 -> LogC + EL160
      static RGB Linearize(const RGB &c, Function gf=sRGB);
      static RGB Unlinearize(const RGB &c, Function gf=sRGB);
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
      
      LAB XYZtoLAB(const XYZ &xyz) const;
      LAB XYZtoLAB(const XYZ &xyz, const Chromaticity &w) const;
      XYZ LABtoXYZ(const LAB &lab) const;
      XYZ LABtoXYZ(const LAB &lab, const Chromaticity &w) const;
      
      LUV XYZtoLUV(const XYZ &xyz) const;
      LUV XYZtoLUV(const XYZ &xyz, const Chromaticity &w) const;
      XYZ LUVtoXYZ(const LUV &luv) const;
      XYZ LUVtoXYZ(const LUV &luv, const Chromaticity &w) const;

      const std::string& getName() const;

      void getPrimaries(Chromaticity &r, Chromaticity &g, Chromaticity &b) const;
      const Chromaticity getWhitePoint() const;

      // NOTE: Colors to transform must be postmultiplied
      // XYZ_Vector = RGBtoXYZ_Matrix * RGB_Vector
      // RGB_Vector = XYZtoRGB_Matrix * XYZ_Vector
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
      static const ColorSpace ACES_AP0; // ACES2065-1
      static const ColorSpace ACES_AP1; // ACEScg

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
   
   class GMATH_API ToneMappingOperator
   {
   private:
      template <typename T>
      struct LinearParamsT
      {
         T Lmax;
      };
      
      template <typename T>
      struct GammaParamsT
      {
         T gain;
         T gamma;
      };
      
      template <typename T>
      struct ReinhardParamsT
      {
         T key;
         T Lavg;
         T Lwht;
      };
   
   public:
      enum Method
      {
         Undefined = -1,
         Simple,  // params: -                       [L' = L / (1 + L)]
         Linear,  // params: Lmax (0.0)              [L' = L / Lmax]
         Gamma,   // params: gain (1.0), gamma (1.0) [L' = gain * L^gamma]
         Reinhard // params: key (0.18), Lavg (0.0), Lwht (0.0) (<=0 to disable)
      };
      
      typedef LinearParamsT<Params::accessor> LinearParams;
      typedef LinearParamsT<Params::const_accessor> LinearConstParams;
      
      typedef GammaParamsT<Params::accessor> GammaParams;
      typedef GammaParamsT<Params::const_accessor> GammaConstParams;
      
      typedef ReinhardParamsT<Params::accessor> ReinhardParams;
      typedef ReinhardParamsT<Params::const_accessor> ReinhardConstParams;
      
   public:
      
      ToneMappingOperator(const ColorSpace &cs=ColorSpace::Rec709);
      ~ToneMappingOperator();
      
      void setMethod(Method m);
      void setMethod(Method m, const Params &params);
      void updateParams(const Params &params);  // don't need to call validate()
      bool validate();
      
      bool isValid() const;
      Method getMethod() const;
      void copyParams(Params &params) const;
      
      // when accessing params via the returned pointer don't forget to call
      //   validate() after any change
      template <class P> bool getParams(P &p);
      template <class P> bool getParams(P &p) const;
      
      RGB operator()(const RGB &input) const;
      XYZ operator()(const XYZ &input) const;
   
   private:
      ToneMappingOperator& operator=(const ToneMappingOperator&);
   
   private:
      const ColorSpace &mColorSpace;
      Method mMethod;
      void *mImpl;
      bool mValid;
   };
   
   namespace details
   {
      template <typename P> struct ToneMappingParams
      {
         static bool Bind(ToneMappingOperator &, void *, P &)
         {
            return false;
         }
         
         static bool Bind(const ToneMappingOperator &, void *, P &)
         {
            return false;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::LinearParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::LinearParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Linear || !impl)
            {
               return false;
            }
            ToneMappingOperator::LinearParams *pp = (ToneMappingOperator::LinearParams *)impl;
            p = *pp;
            return true;
         }
         
         static bool Bind(const ToneMappingOperator &, void *, ToneMappingOperator::LinearParams &)
         {
            return false;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::LinearConstParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::LinearConstParams &p)
         {
            return Bind((const ToneMappingOperator&)tmo, impl, p);
         }
         
         static bool Bind(const ToneMappingOperator &tmo, void *impl, ToneMappingOperator::LinearConstParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Linear || !impl)
            {
               return false;
            }
            ToneMappingOperator::LinearParams *pp = (ToneMappingOperator::LinearParams *)impl;
            p.Lmax = pp->Lmax;
            return true;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::GammaParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::GammaParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Gamma || !impl)
            {
               return false;
            }
            ToneMappingOperator::GammaParams *pp = (ToneMappingOperator::GammaParams *)impl;
            p = *pp;
            return true;
         }
         
         static bool Bind(const ToneMappingOperator &, void *, ToneMappingOperator::GammaParams &)
         {
            return false;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::GammaConstParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::GammaConstParams &p)
         {
            return Bind((const ToneMappingOperator&)tmo, impl, p);
         }
         
         static bool Bind(const ToneMappingOperator &tmo, void *impl, ToneMappingOperator::GammaConstParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Gamma || !impl)
            {
               return false;
            }
            ToneMappingOperator::GammaParams *pp = (ToneMappingOperator::GammaParams *)impl;
            p.gain = pp->gain;
            p.gamma = pp->gamma;
            return true;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::ReinhardParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::ReinhardParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Reinhard || !impl)
            {
               return false;
            }
            ToneMappingOperator::ReinhardParams *pp = (ToneMappingOperator::ReinhardParams *)impl;
            p = *pp;
            return true;
         }
         
         static bool Bind(const ToneMappingOperator &, void *, ToneMappingOperator::ReinhardParams &)
         {
            return false;
         }
      };
      
      template <> struct ToneMappingParams<ToneMappingOperator::ReinhardConstParams>
      {
         static bool Bind(ToneMappingOperator &tmo, void *impl, ToneMappingOperator::ReinhardConstParams &p)
         {
            return Bind((const ToneMappingOperator&)tmo, impl, p);
         }
         
         static bool Bind(const ToneMappingOperator &tmo, void *impl, ToneMappingOperator::ReinhardConstParams &p)
         {
            if (tmo.getMethod() != ToneMappingOperator::Reinhard || !impl)
            {
               return false;
            }
            ToneMappingOperator::ReinhardParams *pp = (ToneMappingOperator::ReinhardParams *)impl;
            p.key = pp->key;
            p.Lavg = pp->Lavg;
            p.Lwht = pp->Lwht;
            return true;
         }
      };
   }
   
   template <class P>
   bool ToneMappingOperator::getParams(P &p)
   {
      return details::ToneMappingParams<P>::Bind(*this, mImpl, p);
   }
   
   template <class P>
   bool ToneMappingOperator::getParams(P &p) const
   {
      return details::ToneMappingParams<P>::Bind(*this, mImpl, p);
   }
   
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

      // Planckian Locus aprroximation 
      //   https://en.wikipedia.org/wiki/Planckian_locus
      // Valid for temp in [1667, 25000]
      static bool CanApprox(float temp);
      static XYZ GetXYZApprox(float temp);
      static RGB GetRGBApprox(float temp, const ColorSpace &cs, bool normalize=true);
      
   protected:
      static void OutOfGamutRemap(RGB &col);
      static void Normalize(RGB &col);
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

   GMATH_API Chromaticity XYZtoChromaticity(const XYZ &xyz, const Chromaticity &Wc=Chromaticity::IllumD65);
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
