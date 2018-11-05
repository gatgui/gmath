#include <gmath/color.h>
#include <string>
#include <iostream>

enum FlagOp
{
   NoOP = 0,
   SetSrcCS,
   SetDstCS
};

const gmath::ColorSpace* GetColorspace(const std::string &name)
{
   if (name == "CIE RGB")
   {
      return &gmath::ColorSpace::CIE;
   }
   else if (name == "UHDTV")
   {
      return &gmath::ColorSpace::UHDTV;
   }
   else if (name == "DCI-P3")
   {
      return &gmath::ColorSpace::DCIP3;
   }
   else if (name == "Adobe Wide Gamut RGB")
   {
      return &gmath::ColorSpace::AdobeWide;
   }
   else if (name == "ALEXA Wide Gamut RGB")
   {
      return &gmath::ColorSpace::AlexaWide;
   }
   else if (name == "Adobe RGB")
   {
      return &gmath::ColorSpace::AdobeRGB;
   }
   else if (name == "ACES2065-1")
   {
      return &gmath::ColorSpace::ACES_AP0;
   }
   else if (name == "ACEScg")
   {
      return &gmath::ColorSpace::ACES_AP1;
   }
   else
   {
      return 0;
   }
}

int main(int argc, char **argv)
{
   std::string srcCSName;
   std::string dstCSName;
   const gmath::ColorSpace *srcCS = 0;
   const gmath::ColorSpace *dstCS = 0;
   std::string arg;
   FlagOp op = NoOP;

   for (int i=1; i<argc; ++i)
   {
      arg = argv[i];
      if (op == NoOP)
      {
         if (arg == "-sc" || arg == "--source-colorspace")
         {
            op = SetSrcCS;
         }
         else if (arg == "-dc" || arg == "--destination-colorspace")
         {
            op = SetDstCS;
         }
         else if (arg == "-h" || arg == "--help")
         {
            std::cout << "USAGE" << std::endl;
            std::cout << "  colormatrix -sc/--source-colorspace <str> -dc/--destination-colorspace <str> (-h/--help)" << std::endl;
            std::cout << std::endl;
            std::cout << "Available color spaces:" << std::endl;
            std::cout << "  CIE RGB" << std::endl;
            std::cout << "  UHDTV" << std::endl;
            std::cout << "  DCI-P3" << std::endl;
            std::cout << "  Adobe Wide Gamut RGB" << std::endl;
            std::cout << "  ALEXA Wide Gamut RGB" << std::endl;
            std::cout << "  Adobe RGB" << std::endl;
            std::cout << "  ACES2065-1" << std::endl;
            std::cout << "  ACEScg" << std::endl;
            std::cout << std::endl;
            return 0;
         }
         else
         {
            std::cerr << "Ignore argument '" << arg.c_str() << "'" << std::endl;
         }
      }
      else if (op == SetSrcCS)
      {
         srcCSName = arg;
         srcCS = GetColorspace(arg);
         op = NoOP;
      }
      else if (op == SetDstCS)
      {
         dstCSName = arg;
         dstCS = GetColorspace(arg);
         op = NoOP;
      }
      else
      {
         std::cerr << "Unknown operation. Ignore argument '" << arg.c_str() << "'" << std::endl;
         op = NoOP;
      }
   }

   if (!srcCS || !dstCS)
   {
      std::cerr << "Missing source and/or destination color space" << std::endl;
      return 1;
   }
   else
   {
      gmath::RGB w(1, 1, 1);
      gmath::XYZ srcW = gmath::ChromaticityYtoXYZ(srcCS->getWhitePoint(), 1.0f);
      gmath::XYZ dstW = gmath::ChromaticityYtoXYZ(dstCS->getWhitePoint(), 1.0f);
      gmath::Matrix3 CAM;

      std::cout << "-- RGB / XYZ conversion" << std::endl;
      std::cout << srcCSName << " -> XYZ: " << srcCS->getRGBtoXYZMatrix() << std::endl;
      std::cout << "XYZ -> " << dstCSName << ": " << dstCS->getXYZtoRGBMatrix() << std::endl;

      std::cout << "== No adaptation:" << std::endl;
      std::cout << (srcCS->getRGBtoXYZMatrix() * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== VonKries adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_VonKries);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== Bradford adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_Bradford);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== Sharp adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_Sharp);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== CMC2000 adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_CMC2000);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== 02 adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_02);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;
      std::cout << "== XYZ adaptation:" << std::endl;
      CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, gmath::CAT_XYZ);
      std::cout << (srcCS->getRGBtoXYZMatrix() * CAM * dstCS->getXYZtoRGBMatrix()) << std::endl;

      return 0;
   }
}
