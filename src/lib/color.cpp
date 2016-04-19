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

const float StandardObserver::CIE1931[81][3] =
{
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

const float StandardObserver::CIE1964[81][3] =
{
  {0.000160f, 0.000017f, 0.000705f},
  {0.000662f, 0.000072f, 0.002928f},
  {0.002362f, 0.000253f, 0.010482f},
  {0.007242f, 0.000769f, 0.032344f},
  {0.019110f, 0.002004f, 0.086011f},
  {0.043400f, 0.004509f, 0.197120f},
  {0.084736f, 0.008756f, 0.389366f},
  {0.140638f, 0.014456f, 0.656760f},
  {0.204492f, 0.021391f, 0.972542f},
  {0.264737f, 0.029497f, 1.282500f},
  {0.314679f, 0.038676f, 1.553480f},
  {0.357719f, 0.049602f, 1.798500f},
  {0.383734f, 0.062077f, 1.967280f},
  {0.386726f, 0.074704f, 2.027300f},
  {0.370702f, 0.089456f, 1.994800f},
  {0.342957f, 0.106256f, 1.900700f},
  {0.302273f, 0.128201f, 1.745370f},
  {0.254085f, 0.152761f, 1.554900f},
  {0.195618f, 0.185190f, 1.317560f},
  {0.132349f, 0.219940f, 1.030200f},
  {0.080507f, 0.253589f, 0.772125f},
  {0.041072f, 0.297665f, 0.570060f},
  {0.016172f, 0.339133f, 0.415254f},
  {0.005132f, 0.395379f, 0.302356f},
  {0.003816f, 0.460777f, 0.218502f},
  {0.015444f, 0.531360f, 0.159249f},
  {0.037465f, 0.606741f, 0.112044f},
  {0.071358f, 0.685660f, 0.082248f},
  {0.117749f, 0.761757f, 0.060709f},
  {0.172953f, 0.823330f, 0.043050f},
  {0.236491f, 0.875211f, 0.030451f},
  {0.304213f, 0.923810f, 0.020584f},
  {0.376772f, 0.961988f, 0.013676f},
  {0.451584f, 0.982200f, 0.007918f},
  {0.529826f, 0.991761f, 0.003988f},
  {0.616053f, 0.999110f, 0.001091f},
  {0.705224f, 0.997340f, 0.000000f},
  {0.793832f, 0.982380f, 0.000000f},
  {0.878655f, 0.955552f, 0.000000f},
  {0.951162f, 0.915175f, 0.000000f},
  {1.014160f, 0.868934f, 0.000000f},
  {1.074300f, 0.825623f, 0.000000f},
  {1.118520f, 0.777405f, 0.000000f},
  {1.134300f, 0.720353f, 0.000000f},
  {1.123990f, 0.658341f, 0.000000f},
  {1.089100f, 0.593878f, 0.000000f},
  {1.030480f, 0.527963f, 0.000000f},
  {0.950740f, 0.461834f, 0.000000f},
  {0.856297f, 0.398057f, 0.000000f},
  {0.754930f, 0.339554f, 0.000000f},
  {0.647467f, 0.283493f, 0.000000f},
  {0.535110f, 0.228254f, 0.000000f},
  {0.431567f, 0.179828f, 0.000000f},
  {0.343690f, 0.140211f, 0.000000f},
  {0.268329f, 0.107633f, 0.000000f},
  {0.204300f, 0.081187f, 0.000000f},
  {0.152568f, 0.060281f, 0.000000f},
  {0.112210f, 0.044096f, 0.000000f},
  {0.081261f, 0.031800f, 0.000000f},
  {0.057930f, 0.022602f, 0.000000f},
  {0.040851f, 0.015905f, 0.000000f},
  {0.028623f, 0.011130f, 0.000000f},
  {0.019941f, 0.007749f, 0.000000f},
  {0.013842f, 0.005375f, 0.000000f},
  {0.009577f, 0.003718f, 0.000000f},
  {0.006605f, 0.002565f, 0.000000f},
  {0.004553f, 0.001768f, 0.000000f},
  {0.003145f, 0.001222f, 0.000000f},
  {0.002175f, 0.000846f, 0.000000f},
  {0.001506f, 0.000586f, 0.000000f},
  {0.001045f, 0.000407f, 0.000000f},
  {0.000727f, 0.000284f, 0.000000f},
  {0.000508f, 0.000199f, 0.000000f},
  {0.000356f, 0.000140f, 0.000000f},
  {0.000251f, 0.000098f, 0.000000f},
  {0.000178f, 0.000070f, 0.000000f},
  {0.000126f, 0.000050f, 0.000000f},
  {0.000090f, 0.000036f, 0.000000f},
  {0.000065f, 0.000025f, 0.000000f},
  {0.000046f, 0.000018f, 0.000000f},
  {0.000033f, 0.000013f, 0.000000f}
};

// ---

// https://en.wikipedia.org/wiki/Standard_illuminant
const Chromaticity Chromaticity::IllumA(0.44757f, 0.40745f);
const Chromaticity Chromaticity::IllumB(0.34842f, 0.35161f);
const Chromaticity Chromaticity::IllumC(0.31006f, 0.31616f);
const Chromaticity Chromaticity::IllumD50(0.34567f, 0.35850f);
const Chromaticity Chromaticity::IllumD55(0.33242f, 0.34743f);
const Chromaticity Chromaticity::IllumD65(0.31271f, 0.32902f);
const Chromaticity Chromaticity::IllumD75(0.29902f, 0.31485f);
const Chromaticity Chromaticity::IllumE(1.0f/3.0f, 1.0f/3.0f);

Chromaticity::Chromaticity()
   : x(0.0f), y(0.0f)
{
}

Chromaticity::Chromaticity(float _x, float _y)
   : x(_x), y(_y)
{
}

Chromaticity::Chromaticity(const Chromaticity &rhs)
   : x(rhs.x), y(rhs.y)
{
}

Chromaticity& Chromaticity::operator=(const Chromaticity &rhs)
{
   x = rhs.x;
   y = rhs.y;
   return *this;
}

// ---

struct LogCParams
{
   float cut;
   float a;
   float b;
   float c;
   float d;
   float e;
   float f;
   float ecut_f; // e * cut + f
};

static const LogCParams LogCv2_params[11] =
{
   {0.000000f, 5.061087f, 0.089004f, 0.269035f, 0.391007f, 6.332427f, 0.108361f, 0.108361f},
   {0.000000f, 5.061087f, 0.089004f, 0.266007f, 0.391007f, 6.189953f, 0.111543f, 0.111543f},
   {0.000000f, 5.061087f, 0.089004f, 0.262978f, 0.391007f, 6.034414f, 0.114725f, 0.114725f},
   {0.000000f, 5.061087f, 0.089004f, 0.259627f, 0.391007f, 5.844973f, 0.118246f, 0.118246f},
   {0.000000f, 5.061087f, 0.089004f, 0.256598f, 0.391007f, 5.656190f, 0.121428f, 0.121428f},
   {0.000000f, 5.061087f, 0.089004f, 0.253569f, 0.391007f, 5.449261f, 0.124610f, 0.124610f},
   {0.000000f, 5.061087f, 0.089004f, 0.250218f, 0.391007f, 5.198031f, 0.128130f, 0.128130f},
   {0.000000f, 5.061087f, 0.089004f, 0.247189f, 0.391007f, 4.950469f, 0.131313f, 0.131313f},
   {0.000000f, 5.061087f, 0.089004f, 0.244161f, 0.391007f, 4.684112f, 0.134495f, 0.134495f},
   {0.000000f, 5.061087f, 0.089004f, 0.240810f, 0.391007f, 4.369609f, 0.138015f, 0.138015f},
   {0.000000f, 5.061087f, 0.089004f, 0.237781f, 0.391007f, 4.070466f, 0.141197f, 0.141197f}
};

static const LogCParams LogCv3_params[11] =
{
   {0.005561f, 5.555556f, 0.080216f, 0.269036f, 0.381991f, 5.842037f, 0.092778f, 0.125266f},
   {0.006208f, 5.555556f, 0.076621f, 0.266007f, 0.382478f, 5.776265f, 0.092782f, 0.128643f},
   {0.006871f, 5.555556f, 0.072941f, 0.262978f, 0.382966f, 5.710494f, 0.092786f, 0.132021f},
   {0.007622f, 5.555556f, 0.068768f, 0.259627f, 0.383508f, 5.637732f, 0.092791f, 0.135761f},
   {0.008318f, 5.555556f, 0.064901f, 0.256598f, 0.383999f, 5.571960f, 0.092795f, 0.139142f},
   {0.009031f, 5.555556f, 0.060939f, 0.253569f, 0.384493f, 5.506188f, 0.092800f, 0.142526f},
   {0.009840f, 5.555556f, 0.056443f, 0.250219f, 0.385040f, 5.433426f, 0.092805f, 0.146271f},
   {0.010591f, 5.555556f, 0.052272f, 0.247190f, 0.385537f, 5.367655f, 0.092809f, 0.149658f},
   {0.011361f, 5.555556f, 0.047996f, 0.244161f, 0.386036f, 5.301883f, 0.092814f, 0.153047f},
   {0.012235f, 5.555556f, 0.043137f, 0.240810f, 0.386590f, 5.229121f, 0.092819f, 0.156799f},
   {0.013047f, 5.555556f, 0.038625f, 0.237781f, 0.387093f, 5.163350f, 0.092824f, 0.160192f}
};

static const float Cineon_white = 685.0f;
static const float Cineon_black = 95.0f;
static const float Cineon_ic0 = 0.6f / 0.002f;
static const float Cineon_c0 = 0.002f / 0.6f;
static const float Cineon_c1 = 1.0f / 1023.0f;
static const float Cineon_igain = 1.0f - powf(10.0f, (Cineon_black - Cineon_white) * Cineon_c0);
static const float Cineon_gain = 1.0f / Cineon_igain;
static const float Cineon_offset = Cineon_gain - 1.0f;

RGB Gamma::Linearize(const RGB &c, Gamma::Function gf)
{
   static float sRGBScale = 1.0f / 12.92f;
   static float Rec709Scale = 1.0f / 4.5f;
   static float Rec709Power = 1.0f / 0.45f;

   RGB rgb;
   const LogCParams *lcp = 0;

   if (gf > Rec709 && gf <= LogCv2 + EL1600)
   {
      lcp = &LogCv2_params[(gf - LogCv2) + 7];
      gf = LogC;
   }
   else if (gf > LogCv2 + EL1600 && gf <= LogCv3 + EL1600)
   {
      lcp = &LogCv3_params[(gf - LogCv3) + 7];
      gf = LogC;
   }

   switch (gf)
   {
   case Power22:
      // Exact Adobe RGB: 563.0 / 256.0f
      rgb.r = powf(c.r, 2.2f);
      rgb.g = powf(c.g, 2.2f);
      rgb.b = powf(c.b, 2.2f);
      break;
   case Power24:
      rgb.r = powf(c.r, 2.4f);
      rgb.g = powf(c.g, 2.4f);
      rgb.b = powf(c.b, 2.4f);
      break;
   case sRGB:
      // https://en.wikipedia.org/wiki/SRGB
      rgb.r = c.r <= 0.04045f ? c.r * sRGBScale : powf((c.r + 0.055f) / 1.055f, 2.4f);
      rgb.g = c.g <= 0.04045f ? c.g * sRGBScale : powf((c.g + 0.055f) / 1.055f, 2.4f);
      rgb.b = c.b <= 0.04045f ? c.b * sRGBScale : powf((c.b + 0.055f) / 1.055f, 2.4f);
      break;
   case Rec709:
      // https://en.wikipedia.org/wiki/Rec._709
      rgb.r = c.r < 0.081f ? c.r * Rec709Scale : powf((c.r + 0.099f) / 1.099f, Rec709Power);
      rgb.g = c.g < 0.081f ? c.g * Rec709Scale : powf((c.g + 0.099f) / 1.099f, Rec709Power);
      rgb.b = c.b < 0.081f ? c.b * Rec709Scale : powf((c.b + 0.099f) / 1.099f, Rec709Power);
      break;

   case LogC:
      // http://www.vocas.nl/webfm_send/964
      {
         float ia = 1.0f / lcp->a;
         float ic = 1.0f / lcp->c;
         float ie = 1.0f / lcp->e;
         rgb.r = (c.r > lcp->ecut_f ? ia * (powf(10.0f, ic * (c.r - lcp->d)) - lcp->b) : ie * (c.r - lcp->f));
         rgb.g = (c.g > lcp->ecut_f ? ia * (powf(10.0f, ic * (c.g - lcp->d)) - lcp->b) : ie * (c.g - lcp->f));
         rgb.b = (c.b > lcp->ecut_f ? ia * (powf(10.0f, ic * (c.b - lcp->d)) - lcp->b) : ie * (c.b - lcp->f));
      }
      break;

   case Cineon:
      // http://www.cineon.com/conv_10to8bit.php
      // http://www.digital-intermediate.co.uk/film/pdf/Cineon.pdf
      // Note: cineon values have 1024 steps [0, 1023]
      rgb.r = powf(10.0f, (1023.0f * c.r - Cineon_white) * Cineon_c0) * Cineon_gain - Cineon_offset;
      rgb.g = powf(10.0f, (1023.0f * c.g - Cineon_white) * Cineon_c0) * Cineon_gain - Cineon_offset;
      rgb.b = powf(10.0f, (1023.0f * c.b - Cineon_white) * Cineon_c0) * Cineon_gain - Cineon_offset;
      rgb.ceil(0.0f);
      break;

   default:
      rgb = c;
   }

   return rgb;
}

RGB Gamma::Unlinearize(const RGB &c, Gamma::Function gf)
{
   static float oneOver22 = 1.0f / 2.2f;
   static float oneOver24 = 1.0f / 2.4f;

   RGB rgb;
   const LogCParams *lcp = 0;

   if (gf > Rec709 && gf <= LogCv2 + EL1600)
   {
      lcp = &LogCv2_params[(gf - LogCv2) + 7];
      gf = LogC;
   }
   else if (gf > LogCv2 + EL1600 && gf <= LogCv3 + EL1600)
   {
      lcp = &LogCv3_params[(gf - LogCv3) + 7];
      gf = LogC;
   }

   switch (gf)
   {
   case Power22:
      rgb.r = powf(c.r, oneOver22);
      rgb.g = powf(c.g, oneOver22);
      rgb.b = powf(c.b, oneOver22);
      break;

   case Power24:
      rgb.r = powf(c.r, oneOver24);
      rgb.g = powf(c.g, oneOver24);
      rgb.b = powf(c.b, oneOver24);
      break;

   case sRGB:
      // https://en.wikipedia.org/wiki/SRGB
      rgb.r = c.r <= 0.0031308f ? 12.92f * c.r : 1.055f * powf(c.r, oneOver24) - 0.055f;
      rgb.g = c.g <= 0.0031308f ? 12.92f * c.g : 1.055f * powf(c.g, oneOver24) - 0.055f;
      rgb.b = c.b <= 0.0031308f ? 12.92f * c.b : 1.055f * powf(c.b, oneOver24) - 0.055f;
      break;

   case Rec709:
      // https://en.wikipedia.org/wiki/Rec._709
      rgb.r = c.r < 0.018f ? 4.5f * c.r : 1.099f * powf(c.r, 0.45f) - 0.099f;
      rgb.g = c.g < 0.018f ? 4.5f * c.g : 1.099f * powf(c.g, 0.45f) - 0.099f;
      rgb.b = c.b < 0.018f ? 4.5f * c.b : 1.099f * powf(c.b, 0.45f) - 0.099f;
      break;

   case Rec2020:
      // https://en.wikipedia.org/wiki/Rec._2020
      rgb.r = c.r < 0.0181f ? 4.5f * c.r : 1.0993f * powf(c.r, 0.45f) - 0.0993f;
      rgb.g = c.g < 0.0181f ? 4.5f * c.g : 1.0993f * powf(c.g, 0.45f) - 0.0993f;
      rgb.b = c.b < 0.0181f ? 4.5f * c.b : 1.0993f * powf(c.b, 0.45f) - 0.0993f;
      break;
   
   case LogC:
      // http://www.vocas.nl/webfm_send/964
      rgb.r = (c.r > lcp->cut ? lcp->c * log10f(lcp->a * c.r + lcp->b) + lcp->d : lcp->e * c.r + lcp->f);
      rgb.g = (c.g > lcp->cut ? lcp->c * log10f(lcp->a * c.g + lcp->b) + lcp->d : lcp->e * c.g + lcp->f);
      rgb.b = (c.b > lcp->cut ? lcp->c * log10f(lcp->a * c.b + lcp->b) + lcp->d : lcp->e * c.b + lcp->f);
      break;

   case Cineon:
      // http://www.cineon.com/conv_10to8bit.php
      // http://www.digital-intermediate.co.uk/film/pdf/Cineon.pdf
      // Note: cineon values have 1024 steps [0, 1023]
      rgb.r = Cineon_c1 * (Cineon_white + Cineon_ic0 * log10f(Cineon_igain * (c.r + Cineon_offset)));
      rgb.g = Cineon_c1 * (Cineon_white + Cineon_ic0 * log10f(Cineon_igain * (c.g + Cineon_offset)));
      rgb.b = Cineon_c1 * (Cineon_white + Cineon_ic0 * log10f(Cineon_igain * (c.b + Cineon_offset)));
      break;

   default:
      rgb = c;
   }

   return rgb;
}

// ---

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
// https://en.wikipedia.org/wiki/Wide-gamut_RGB_color_space
// http://www.vocas.nl/webfm_send/964
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
const ColorSpace ColorSpace::AdobeWide("Adobe Wide Gamut RGB",
                                       Chromaticity(0.7347f, 0.2653f),
                                       Chromaticity(0.1152f, 0.8264f),
                                       Chromaticity(0.1566f, 0.0177f),
                                       Chromaticity::IllumD50);
const ColorSpace ColorSpace::AlexaWide("ALEXA Wide Gamut RGB",
                                       Chromaticity(0.6840f,  0.313f),
                                       Chromaticity(0.2210f,  0.848f),
                                       Chromaticity(0.0861f, -0.102f),
                                       Chromaticity::IllumD65);
const ColorSpace ColorSpace::AdobeRGB("Adobe RGB",
                                      Chromaticity(0.64f, 0.33f),
                                      Chromaticity(0.21f, 0.71f),
                                      Chromaticity(0.15f, 0.06f),
                                      Chromaticity::IllumD65);

// https://en.wikipedia.org/wiki/YUV
static const float Umax = 0.436f;
static const float Vmax = 0.615f;

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

YUV ColorSpace::RGBtoYUV(const RGB &rgb) const
{
   YUV yuv;

   float Wr = mRGBtoXYZ(1, 0);
   float Wg = mRGBtoXYZ(1, 1);
   float Wb = mRGBtoXYZ(1, 2);

   yuv.y = Wr * rgb.r + Wg * rgb.g + Wb * rgb.b; // = luminance(rgb)
   yuv.u = Umax * (rgb.b - yuv.y) / (1.0f - Wb);
   yuv.v = Vmax * (rgb.r - yuv.y) / (1.0f - Wr);

   return yuv;
}

RGB ColorSpace::YUVtoRGB(const YUV &yuv) const
{
   RGB rgb;

   float Wr = mRGBtoXYZ(1, 0);
   float Wg = mRGBtoXYZ(1, 1);
   float Wb = mRGBtoXYZ(1, 2);
   float invWg = 1.0f / Wg;
   float utmp = yuv.u * (1.0f - Wb) / Umax;
   float vtmp = yuv.v * (1.0f - Wr) / Vmax;

   rgb.r = yuv.y + vtmp;
   rgb.g = yuv.y - invWg * (Wb * utmp + Wr * vtmp);
   rgb.b = yuv.y + utmp;

   return rgb;
}

static float s6over29 = 6.0f / 29.0f;
static float s6over29s = s6over29 * s6over29;
static float s6over29c = s6over29 * s6over29s;
static float s29over6s = (29.0f * 29.0f) / (6.0f * 6.0f);
static float s3over29 = 3.0f / 29.0f;
static float s3over29s = s3over29 * s3over29;
static float s3over29c = s3over29 * s3over29s;
static float s29over3 = 29.0f / 3.0f;
static float s29over3s = s29over3 * s29over3;
static float s29over3c = s29over3 * s29over3s;
static float s1over116 = 1.0f / 116.0f;
static float s1over500 = 1.0f / 500.0f;
static float s1over200 = 1.0f / 200.0f;
static float s4over29 = 4.0f / 29.0f;
static float s1over3 = 1.0f / 3.0f;

static float LABf(float t, bool inverse)
{
   if (!inverse)
   {
      if (t > s6over29c)
      {
         return powf(t, s1over3);
      }
      else
      {
         return s1over3 * s29over6s * t + s4over29; 
      }
   }
   else
   {
      if (t > s6over29) // t^3 > s6over29c
      {
         return powf(t, 3.0f);
      }
      else
      {
         return 3.0f * s6over29s * (t - s4over29);
      }
   }
}

LAB ColorSpace::XYZtoLAB(const XYZ &xyz) const
{
   return XYZtoLAB(xyz, mWhite);
}

XYZ ColorSpace::LABtoXYZ(const LAB &lab) const
{
   return LABtoXYZ(lab, mWhite);
}

LAB ColorSpace::XYZtoLAB(const XYZ &xyz, const Chromaticity &w) const
{
   LAB lab;
   
   XYZ W = ChromaticityYtoXYZ(w, 1.0f);
   
   float fYoverYw = LABf(xyz.y / W.y, false);
   
   lab.l = 116.0f * fYoverYw - 16.0f;
   lab.a = 500.0f * (LABf(xyz.x / W.x, false) - fYoverYw);
   lab.b = 200.0f * (fYoverYw - LABf(xyz.z / W.z, false));
   
   return lab;
}

XYZ ColorSpace::LABtoXYZ(const LAB &lab, const Chromaticity &w) const
{
   XYZ xyz;
   
   XYZ W = ChromaticityYtoXYZ(w, 1.0f);
   
   float Lplus16over116 = s1over116 * (lab.l + 16.0f);
   
   xyz.x = W.x * LABf(Lplus16over116 + s1over500 * lab.a, true);
   xyz.y = W.y * LABf(Lplus16over116, true);
   xyz.z = W.z * LABf(Lplus16over116 - s1over200 * lab.b, true);
   
   return xyz;
}

LUV ColorSpace::XYZtoLUV(const XYZ &xyz) const
{
   return XYZtoLUV(xyz, mWhite);
}

XYZ ColorSpace::LUVtoXYZ(const LUV &luv) const
{
   return LUVtoXYZ(luv, mWhite);
}

LUV ColorSpace::XYZtoLUV(const XYZ &xyz, const Chromaticity &w) const
{
   LUV luv;
   
   XYZ W = ChromaticityYtoXYZ(w, 1.0f);
   
   float uprimeW = (4.0f * W.x) / (W.x + 15.0f * W.y + 3.0f * W.z);
   float vprimeW = (9.0f * W.y) / (W.x + 15.0f * W.y + 3.0f * W.z);
   float uprime = (4.0f * xyz.x) / (xyz.x + 15.0f * xyz.y + 3.0f * xyz.z);
   float vprime = (9.0f * xyz.y) / (xyz.x + 15.0f * xyz.y + 3.0f * xyz.z);
   
   float YoverYw = xyz.y / W.y;
   
   if (YoverYw <= s6over29c)
   {
      luv.l = s29over3c * YoverYw;
   }
   else
   {
      luv.l = 116.0f * powf(YoverYw, s1over3) - 16.0f;
   }
   luv.u = 13.0f * luv.l * (uprime - uprimeW);
   luv.v = 13.0f * luv.l * (vprime - vprimeW);
   
   return luv;
}

XYZ ColorSpace::LUVtoXYZ(const LUV &luv, const Chromaticity &w) const
{
   XYZ xyz;
   
   XYZ W = ChromaticityYtoXYZ(w, 1.0f);
   
   float uprimeW = (4.0f * W.x) / (W.x + 15.0f * W.y + 3.0f * W.z);
   float vprimeW = (9.0f * W.y) / (W.x + 15.0f * W.y + 3.0f * W.z);
   float uprime = luv.u / (13.0f * luv.l) + uprimeW;
   float vprime = luv.v / (13.0f * luv.l) + vprimeW;
   
   if (luv.l <= 8.0f)
   {
      xyz.y = W.y * luv.l * s3over29c;
   }
   else
   {
      xyz.y = W.y * powf((luv.l + 16.0f) / 116.0f, 3.0f);
   }
   xyz.x = xyz.y * (9.0f * uprime) / (4.0f * vprime);
   xyz.z = xyz.y * (12.0f - 3.0f * uprime - 20.0f * vprime) / (4.0f * vprime);
   
   return xyz;
}

const std::string& ColorSpace::getName() const
{
   return mName;
}

const Matrix3& ColorSpace::getXYZtoRGBMatrix() const
{
   return mXYZtoRGB;
}

const Matrix3& ColorSpace::getRGBtoXYZMatrix() const
{
   return mRGBtoXYZ;
}

void ColorSpace::getPrimaries(Chromaticity &r, Chromaticity &g, Chromaticity &b) const
{
   r = mRed;
   g = mGreen;
   b = mBlue;
}

const Chromaticity ColorSpace::getWhitePoint() const
{
   return mWhite;
}

// ---

template <class ParamAccessors>
struct Impl
{
   ParamAccessors accessors;
   Params params;
};

ToneMappingOperator::ToneMappingOperator(const ColorSpace &cs)
   : mColorSpace(cs)
   , mMethod(Undefined)
   , mImpl(0)
   , mValid(false)
{
}
   
ToneMappingOperator::~ToneMappingOperator()
{
   setMethod(Undefined);
}

void ToneMappingOperator::setMethod(Method m)
{
   if (mMethod != m)
   {
      if (mImpl)
      {
         switch (mMethod)
         {
         case Linear:
            delete (Impl<LinearParams>*)mImpl;
            break;
         case Gamma:
            delete (Impl<GammaParams>*)mImpl;
            break;
         case Reinhard:
            delete (Impl<ReinhardParams>*)mImpl;
         default:
            break;
         }
         mImpl = 0;
      }
      
      mMethod = m;
      mValid = true;
      
      switch (mMethod)
      {
      case Linear:
         {
            Impl<LinearParams> *impl = new Impl<LinearParams>();
            impl->params.set("Lmax", 0.0f);
            impl->accessors.Lmax = Params::accessor(impl->params, "Lmax");
            mImpl = impl;
            mValid = false;
         }
         break;
      case Gamma:
         {
            Impl<GammaParams> *impl = new Impl<GammaParams>();
            impl->params.set("gain", 1.0f);
            impl->params.set("gamma", 1.0f);
            impl->accessors.gain = Params::accessor(impl->params, "gain");
            impl->accessors.gamma = Params::accessor(impl->params, "gamma");
            mImpl = impl;
         }
         break;
      case Reinhard:
         {
            Impl<ReinhardParams> *impl = new Impl<ReinhardParams>();
            impl->params.set("key", 0.18f);
            impl->params.set("Lavg", 0.0f);
            impl->params.set("Lwht", 0.0f);
            impl->accessors.key = Params::accessor(impl->params, "key");
            impl->accessors.Lavg = Params::accessor(impl->params, "Lavg");
            impl->accessors.Lwht = Params::accessor(impl->params, "Lwht");
            mImpl = impl;
            mValid = false;
         }
      default:
         break;
      }
   }
}

void ToneMappingOperator::setMethod(ToneMappingOperator::Method m, const Params &params)
{
   setMethod(m);
   updateParams(params);
}

void ToneMappingOperator::updateParams(const Params &params)
{
   if (!mImpl)
   {
      return;
   }
   
   mValid = true;
   
   switch (mMethod)
   {
   case Linear:
      {
         Impl<LinearParams> *impl = (Impl<LinearParams>*)mImpl;
         float Lmax = 0.0f;
         if (params.get("Lmax", Lmax))
         {
            impl->accessors.Lmax = Lmax;
         }
         mValid = (float(impl->accessors.Lmax) > 0.000001f);
      }
      break;
   case Gamma:
      {
         Impl<GammaParams> *impl = (Impl<GammaParams>*)mImpl;
         float gain = 1.0f;
         float gamma = 1.0f;
         if (params.get("gain", gain))
         {
            impl->accessors.gain = gain;
         }
         if (params.get("gamma", gamma))
         {
            impl->accessors.gamma = gamma;
         }
      }
      break;
   case Reinhard:
      {
         Impl<ReinhardParams> *impl = (Impl<ReinhardParams>*)mImpl;
         float key = 0.18f;
         float Lavg = 0.0f;
         float Lwht = 0.0f;
         if (params.get("key", key))
         {
            impl->accessors.key = key;
         }
         if (params.get("Lavg", Lavg))
         {
            impl->accessors.Lavg = Lavg;
         }
         if (params.get("Lwht", Lwht))
         {
            impl->accessors.Lwht = Lwht;
         }
         mValid = (float(impl->accessors.Lavg) > 0.000001f);
      }
   default:
      break;
   }
}

bool ToneMappingOperator::validate()
{
   if (!mImpl)
   {
      mValid = (mMethod == Simple);
   }
   else
   {
      mValid = true;
      
      switch (mMethod)
      {
      case Linear:
         {
            Impl<LinearParams> *impl = (Impl<LinearParams>*)mImpl;
            mValid = (float(impl->accessors.Lmax) > 0.000001f);
         }
         break;
      case Reinhard:
         {
            Impl<ReinhardParams> *impl = (Impl<ReinhardParams>*)mImpl;
            mValid = (float(impl->accessors.Lavg) > 0.000001f);
         }
      default:
         break;
      }
   }
   
   return mValid;
}

bool ToneMappingOperator::isValid() const
{
  return mValid;
}

ToneMappingOperator::Method ToneMappingOperator::getMethod() const
{
   return mMethod;
}

void ToneMappingOperator::copyParams(Params &params) const
{
   params.clear();
   
   if (mImpl)
   {
      switch (mMethod)
      {
      case Linear:
         params = ((Impl<LinearParams>*)mImpl)->params;
         break;
      case Gamma:
         params = ((Impl<GammaParams>*)mImpl)->params;
         break;
      case Reinhard:
         params = ((Impl<ReinhardParams>*)mImpl)->params;
      default:
         break;
      }
   }
}

XYZ ToneMappingOperator::operator()(const XYZ &input) const
{
   if (!mValid)
   {
      return input;
   }
   
   Chromaticity chroma = XYZtoChromaticity(input, mColorSpace.getWhitePoint());
   float Lout = input.y;
   
   switch (mMethod)
   {
   case Simple:
      Lout = Lout / (1.0f + Lout);
      break;
   case Linear:
      {
         Impl<LinearParams> *impl = (Impl<LinearParams>*)mImpl;
         Lout = Lout / float(impl->accessors.Lmax);
      }
      break;
   case Gamma:
      {
         Impl<GammaParams> *impl = (Impl<GammaParams>*)mImpl;
         Lout = float(impl->accessors.gain) * powf(Lout, float(impl->accessors.gamma));
      }
      break;
   case Reinhard:
      {
         Impl<ReinhardParams> *impl = (Impl<ReinhardParams>*)mImpl;
         float L = float(impl->accessors.key) * Lout / float(impl->accessors.Lavg);
         float Lwht = float(impl->accessors.Lwht);
         if (Lwht > 0.000001f)
         {
            Lout = L * (1.0f + L / (Lwht * Lwht)) / (1.0f + L);
         }
         else
         {
            Lout = L / (1.0f + L);
         }
      }
      break;
   default:
      break;
   }
   
   return ChromaticityYtoXYZ(chroma, Lout);
}

RGB ToneMappingOperator::operator()(const RGB &input) const
{
   return mColorSpace.XYZtoRGB(this->operator()(mColorSpace.RGBtoXYZ(input)));
}

// ---

class BlackbodyColor
{
public:
   BlackbodyColor(int maxTemp=20000)
   {
      int evi = 0;
      char *ev = 0;

      ev = getenv("GMATH_BLACKBODY_STDOBS1964");
      mUseObs1964 = (ev && sscanf(ev, "%d", &evi) == 1 && evi != 0);

      ev = getenv("GMATH_BLACKBODY_CACHE");
      if (!ev || (sscanf(ev, "%d", &evi) == 1 && evi != 0))
      {
         ev = getenv("GMATH_BLACKBODY_CACHE_MAX_TEMPERATURE");

         if (ev && sscanf(ev, "%d", &evi) == 1 && evi >= 0)
         {
            maxTemp = evi;
         }

         mCount = maxTemp + 1;
         mValues = new XYZ[mCount];

         for (int i=0; i<mCount; ++i)
         {
            Blackbody bb((float)i);
            mValues[i] = IntegrateVisibleSpectrum(bb, (mUseObs1964 ? StandardObserver::CIE1964 : StandardObserver::CIE1931));
         }
      }
      else
      {
         mCount = 0;
         mValues = 0;
      }
   }

   ~BlackbodyColor()
   {
      if (mValues)
      {
         delete[] mValues;
      }
   }

   XYZ operator()(float temp)
   {
      int idx = int(temp);
      if (idx < 0 || idx >= mCount)
      {
         // value not cached, compute it
         Blackbody bb(temp);
         return IntegrateVisibleSpectrum(bb, (mUseObs1964 ? StandardObserver::CIE1964 : StandardObserver::CIE1931));
      }
      else
      {
         return mValues[idx];
      }
   }

private:

   int mCount;
   XYZ *mValues;
   bool mUseObs1964;
};

static BlackbodyColor BBC;
static const double SpeedOfLight = 2.99792458e8;
static const double Planck = 6.62607004e-34;
static const double Boltzmann = 1.3806485279e-23;

Blackbody::Blackbody(float t)
   : temperature(t)
{
}

float Blackbody::operator()(float lambda) const
{
   // https://en.wikipedia.org/wiki/Planck%27s_law
   static double c1 = 2 * M_PI * Planck * SpeedOfLight * SpeedOfLight;
   static double c2 = Planck * SpeedOfLight / Boltzmann;

   // c1 = 3.746914726083474e-16
   // c2 = 1.4387773455951101e-2

   double l = double(lambda) * 1e-9;

   return float(c1 * pow(l, -5) / (exp(c2 / (l * temperature)) - 1));
}

void Blackbody::OutOfGamutRemap(RGB &col)
{
   float w = -std::min(0.0f, std::min(col.r, std::min(col.g, col.b)));
   if (w > 0.0f)
   {
      // col lies outside of the target color gamut
      col.r += w;
      col.g += w;
      col.b += w;
   }
}

void Blackbody::Normalize(RGB &col)
{
   float M = std::max(col.r, std::max(col.g, col.b));
   if (M > 0.000001f)
   {
      col /= M;
   }
}

XYZ Blackbody::GetXYZ(float temp)
{
   return BBC(temp);
}

RGB Blackbody::GetRGB(float temp, const ColorSpace &cs, bool normalize)
{
   RGB out = cs.XYZtoRGB(BBC(temp));

   OutOfGamutRemap(out);

   if (normalize)
   {
      Normalize(out);
   }

   return out;
}

XYZ Blackbody::GetPlanckianLocusXYZ(float temp)
{
   float xc = 0.0f;
   float yc = 0.0f;
   float temp2 = temp * temp;
   float arg1 = 1e9f / (temp * temp2);
   float arg2 = 1e6f / temp2;
   float arg3 = 1e3f / temp;
   
   if (temp >= 1667 && temp <= 4000)
   {
      xc = -0.2661239f * arg1 - 0.2343580f * arg2 + 0.8776956f * arg3 + 0.179910f;
   }
   else if (temp > 4000 && temp <= 25000)
   {
      xc = -3.0258469f * arg1 + 2.1070379f * arg2 + 0.2226347f * arg3 + 0.240390f;
   }
   
   float xc2 = xc * xc;
   float xc3 = xc * xc2;
   
   if (temp >= 1667 && temp <= 2222)
   {
      yc = -1.1063814f * xc3 - 1.34811020f * xc2 + 2.18555832f * xc - 0.20219683f;
   }
   else if (temp > 2222 && temp <= 4000)
   {
      yc = -0.9549476f * xc3 - 1.37418593f * xc2 + 2.09137015f * xc - 0.16748867f;
   }
   else if (temp > 4000 && temp <= 25000)
   {
      yc = 3.0817580f * xc3 - 5.87338670f * xc2 + 3.75112997f * xc - 0.37001483f;
   }
   
   if (fabsf(yc) > 0.000001f)
   {
      float iyc = 1.0f / yc;
      
      return XYZ(xc * iyc, 1.0f, (1.0f - xc - yc) * iyc);
   }
   else
   {
      float athird = 1.0f / 3.0f;
      
      return ChromaticityYtoXYZ(Chromaticity(athird, athird), (temp < 1667 ? 0.0f : 1.0f));
   }
}

RGB Blackbody::GetPlanckianLocusRGB(float temp, const ColorSpace &cs, bool normalize)
{
   RGB out = cs.XYZtoRGB(GetPlanckianLocusXYZ(temp));
   
   OutOfGamutRemap(out);

   if (normalize)
   {
      Normalize(out);
   }
   
   return out;
}

// ---

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

   hsl.h = 0.0f;
   hsl.s = 0.0f;
   hsl.l = 0.5f * (m + M);

   if (C >= epsilon)
   {
      if (hsl.l <= 0.5f)
      {
         hsl.s = C / (2.0f * hsl.l);
      }
      else
      {
         hsl.s = C / (2.0f * (1.0f - hsl.l));
      }

      if (M == rgb.r)
      {
         hsl.h = (rgb.g - rgb.b) / C;
      }
      else if (M == rgb.g)
      {
         hsl.h = (rgb.b - rgb.r) / C + 2.0f;
      }
      else
      {
         hsl.h = (rgb.r - rgb.g) / C + 4.0f;
      }

      static float sNormalizeHue = 60.0f / 360.0f;

      hsl.h *= sNormalizeHue;

      if (hsl.h < 0.0f)
      {
         hsl.h += 1.0f;
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

   hsv.h = 0.0f;
   hsv.s = 0.0f;
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
         hsv.h = (rgb.b - rgb.r) / C + 2.0f;
      }
      else
      {
         hsv.h = (rgb.r - rgb.g) / C + 4.0f;
      }

      static float sNormalizeHue = 60.0f / 360.0f;

      hsv.h *= sNormalizeHue;

      if (hsv.h < 0.0f)
      {
         hsv.h += 1.0f;
      }
   }

   return hsv;
}

RGB HSVtoRGB(const HSV &hsv)
{
   RGB rgb;

   float C = hsv.v * hsv.s;
   float h = hsv.h * 6.0f;
   float X = C * (1.0f - fabs(fmod(h, 2.0f) - 1.0f));

   if (h < 1.0f)
   {
      rgb.r = C;
      rgb.g = X;
      rgb.b = 0.0f;
   }
   else if (h < 2.0f)
   {
      rgb.r = X;
      rgb.g = C;
      rgb.b = 0.0f;
   }
   else if (h < 3.0f)
   {
      rgb.r = 0.0f;
      rgb.g = C;
      rgb.b = X;
   }
   else if (h < 4.0f)
   {
      rgb.r = 0.0f;
      rgb.g = X;
      rgb.b = C;
   }
   else if (h < 5.0f)
   {
      rgb.r = X;
      rgb.g = 0.0f;
      rgb.b = C;
   }
   else
   {
      rgb.r = C;
      rgb.g = 0.0f;
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

   if (hsl.l <= 0.5f)
   {
      C = 2.0f * hsl.l * hsl.s;
   }
   else
   {
      C = (2.0f - 2.0f * hsl.l) * hsl.s;
   }

   float h = hsl.h * 6.0f;
   float X = C * (1.0f - fabs(fmod(h, 2.0f) - 1.0f));

   if (h < 1.0f)
   {
      rgb.r = C;
      rgb.g = X;
      rgb.b = 0.0f;
   }
   else if (h < 2.0f)
   {
      rgb.r = X;
      rgb.g = C;
      rgb.b = 0.0f;
   }
   else if (h < 3.0f)
   {
      rgb.r = 0.0f;
      rgb.g = C;
      rgb.b = X;
   }
   else if (h < 4.0f)
   {
      rgb.r = 0.0f;
      rgb.g = X;
      rgb.b = C;
   }
   else if (h < 5.0f)
   {
      rgb.r = X;
      rgb.g = 0.0f;
      rgb.b = C;
   }
   else
   {
      rgb.r = C;
      rgb.g = 0.0f;
      rgb.b = X;
   }

   float m = hsl.l - 0.5f * C;

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

static const Matrix3 CAM_VonKries( 0.40024f, 0.70760f, -0.08081f,
                                  -0.22630f, 1.16532f,  0.04570f,
                                   0.00000f, 0.00000f,  0.91822f);
static const Matrix3 CAM_Bradford( 0.89510f,  0.26640f, -0.16140f,
                                  -0.75020f,  1.71350f,  0.03670f,
                                   0.03890f, -0.06850f,  1.02960f);
static const Matrix3 CAM_Sharp( 1.2694f, -0.0988f, -0.1706f,
                               -0.8364f,  1.8006f,  0.0357f,
                                0.0297f, -0.0315f,  1.0018f);
static const Matrix3 CAM_CMCCAT2000( 0.7982f, 0.3389f, -0.1371f,
                                    -0.5918f, 1.5512f,  0.0406f,
                                     0.0008f, 0.2390f,  0.9753f);
static const Matrix3 CAM_CAT02( 0.7328f, 0.4296f, -0.1624f,
                               -0.7036f, 1.6975f,  0.0061f,
                                0.0030f, 0.0136f,  0.9834f);
static const Matrix3 CAM_XYZ(1.0f, 0.0f, 0.0f,
                             0.0f, 1.0f, 0.0f,
                             0.0f, 0.0f, 1.0f);
static const Matrix3 CAM_InvVonKries(CAM_VonKries.getInverse());
static const Matrix3 CAM_InvBradford(CAM_Bradford.getInverse());
static const Matrix3 CAM_InvSharp(CAM_Sharp.getInverse());
static const Matrix3 CAM_InvCMCCAT2000(CAM_CMCCAT2000.getInverse());
static const Matrix3 CAM_InvCAT02(CAM_CAT02.getInverse());
static const Matrix3 CAM_InvXYZ(CAM_XYZ.getInverse());

LMS XYZtoLMS(const XYZ &xyz, ChromaticAdaptationTransform cat)
{
   switch (cat)
   {
   case CAT_VonKries:
      return LMS(CAM_VonKries * Vector3(xyz));
   case CAT_Bradford:
      return LMS(CAM_Bradford * Vector3(xyz));
   case CAT_Sharp:
      return LMS(CAM_Sharp * Vector3(xyz));
   case CAT_CMC2000:
      return LMS(CAM_CMCCAT2000 * Vector3(xyz));
   case CAT_02:
      return LMS(CAM_CAT02 * Vector3(xyz));
   case CAT_XYZ:
   default:
      return LMS(CAM_XYZ * Vector3(xyz));
   }
}

XYZ LMStoXYZ(const LMS &lms, ChromaticAdaptationTransform cat)
{
   switch (cat)
   {
   case CAT_VonKries:
      return XYZ(CAM_InvVonKries * Vector3(lms));
   case CAT_Bradford:
      return XYZ(CAM_InvBradford * Vector3(lms));
   case CAT_Sharp:
      return XYZ(CAM_InvSharp * Vector3(lms));
   case CAT_CMC2000:
      return XYZ(CAM_InvCMCCAT2000 * Vector3(lms));
   case CAT_02:
      return XYZ(CAM_InvCAT02 * Vector3(lms));
   case CAT_XYZ:
   default:
      return XYZ(CAM_InvXYZ * Vector3(lms));
   }
}

Matrix3 ChromaticAdaptationMatrix(const XYZ &from, const XYZ &to, ChromaticAdaptationTransform cat)
{
   LMS scl = XYZtoLMS(to, cat) / XYZtoLMS(from, cat);

   Matrix3 diag(scl.l, 0.0f, 0.0f,
                0.0f, scl.m, 0.0f,
                0.0f, 0.0f, scl.s);

   switch (cat)
   {
   case CAT_VonKries:
      return CAM_InvVonKries * diag * CAM_VonKries;
   case CAT_Bradford:
      return CAM_InvBradford * diag * CAM_Bradford;
   case CAT_Sharp:
      return CAM_InvSharp * diag * CAM_Sharp;
   case CAT_CMC2000:
      return CAM_InvCMCCAT2000 * diag * CAM_CMCCAT2000;
   case CAT_02:
      return CAM_InvCAT02 * diag * CAM_CAT02;
   case CAT_XYZ:
   default:
      return CAM_InvXYZ * diag * CAM_XYZ;
   }
}

Chromaticity XYZtoChromaticity(const XYZ &xyz, const Chromaticity &Wc)
{
   float sum = (xyz.x + xyz.y + xyz.z);
   if (sum >= 0.000001f)
   {
      float isum = 1.0f / sum;
      return Chromaticity(xyz.x * isum, xyz.y * isum);
   }
   else
   {
      return Wc;
   }
}

XYZ ChromaticityYtoXYZ(const Chromaticity &c, float Y)
{
   XYZ rv;

   float iy = 1.0f / c.y;

   rv.x = Y * iy * c.x;
   rv.y = Y;
   rv.z = Y * iy * (1.0f - c.x - c.y);

   return rv;
}

} // namespace gmath

std::ostream& operator<<(std::ostream &os, const gmath::ColorSpace &cs)
{
   gmath::Chromaticity r, g, b, w;

   cs.getPrimaries(r, g, b);
   w = cs.getWhitePoint();

   os << "ColorSpace \"" << cs.getName().c_str() << "\"" << std::endl;
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
