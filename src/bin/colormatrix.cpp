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
         srcCS = GetColorspace(arg);
         op = NoOP;
      }
      else if (op == SetDstCS)
      {
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
      std::cout << (srcCS->getRGBtoXYZMatrix() * dstCS->getXYZtoRGBMatrix()) << std::endl;
      return 0;
   }
}
