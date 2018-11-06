#include <gmath/color.h>
#include <string>
#include <iostream>

enum FlagOp
{
   NoOP = 0,
   SetSrcCS,
   SetDstCS,
   SetCAT
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

int GetChromaticAdaptationTransform(const std::string &name)
{
   if (name == "VonKries")
   {
      return gmath::CAT_VonKries;
   }
   else if (name == "Bradford")
   {
      return gmath::CAT_Bradford;
   }
   else if (name == "Sharp")
   {
      return gmath::CAT_Sharp;
   }
   else if (name == "CMC2000")
   {
      return gmath::CAT_CMC2000;
   }
   else if (name == "CAT02")
   {
      return gmath::CAT_02;
   }
   else if (name == "XYZ")
   {
      return gmath::CAT_XYZ;
   }
   else
   {
      return -1;
   }
}

int main(int argc, char **argv)
{
   std::string srcCSName;
   std::string dstCSName;
   std::string catName;
   const gmath::ColorSpace *srcCS = 0;
   const gmath::ColorSpace *dstCS = 0;
   int cat = -1;
   std::string arg;
   FlagOp op = NoOP;
   bool verbose = false;

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
         else if (arg == "-c" || arg == "--cat")
         {
            op = SetCAT;
         }
         else if (arg == "-v" || arg == "--verbose")
         {
            verbose = true;
         }
         else if (arg == "-h" || arg == "--help")
         {
            std::cout << "USAGE" << std::endl;
            std::cout << "  colormatrix -sc/--source-colorspace <str> -dc/--destination-colorspace <str> (-c/--cat <str>) (-v/--verbose) (-h/--help)" << std::endl;
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
            std::cout << "Available CATs (Chromatic Adaptation Transform):" << std::endl;
            std::cout << "  VonKries" << std::endl;
            std::cout << "  Bradford" << std::endl;
            std::cout << "  Sharp" << std::endl;
            std::cout << "  CMC2000" << std::endl;
            std::cout << "  CAT02" << std::endl;
            std::cout << "  XYX" << std::endl;
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
      else if (op == SetCAT)
      {
         catName = arg;
         cat = GetChromaticAdaptationTransform(arg);
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
      if (verbose)
      {
         std::cout << srcCSName << " -> XYZ: " << srcCS->getRGBtoXYZMatrix() << std::endl;
         std::cout << "XYZ -> " << dstCSName << ": " << dstCS->getXYZtoRGBMatrix() << std::endl;
      }

      gmath::Matrix3 CAM;
      if (cat != -1)
      {
         gmath::XYZ srcW = gmath::ChromaticityYtoXYZ(srcCS->getWhitePoint(), 1.0f);
         gmath::XYZ dstW = gmath::ChromaticityYtoXYZ(dstCS->getWhitePoint(), 1.0f);
         CAM = gmath::ChromaticAdaptationMatrix(srcW, dstW, (gmath::ChromaticAdaptationTransform)cat);
         std::cout << "CAT " << catName << ": " << CAM << std::endl;
      }

      std::cout << (dstCS->getXYZtoRGBMatrix() * CAM * srcCS->getRGBtoXYZMatrix()) << std::endl;

      return 0;
   }
}
