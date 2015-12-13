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
#include <iostream>

using namespace gmath;

std::ostream& operator<<(std::ostream &os, const Chromaticity &c)
{
   os << "(" << c.x << ", " << c.y << ")";
   return os;
}

int main(int, char**)
{
   const ColorSpace* csl[] =
   {
      &ColorSpace::Rec709,
      &ColorSpace::NTSC,
      &ColorSpace::SMPTE,
      &ColorSpace::CIE,
      &ColorSpace::UHDTV,
      &ColorSpace::DCIP3,
      &ColorSpace::AdobeWide,
      &ColorSpace::AlexaWide,
      &ColorSpace::AdobeRGB
   };

   size_t ncs = sizeof(csl) / sizeof(const ColorSpace*);

   for (size_t i=0; i<ncs; ++i)
   {
      const ColorSpace &cs = *(csl[i]);

      std::cout << cs << std::endl;

      RGB r = RGB(1.0f, 0.0f, 0.0f);
      RGB g = RGB(0.0f, 1.0f, 0.0f);
      RGB b = RGB(0.0f, 0.0f, 1.0f);
      RGB w = RGB(1.0f, 1.0f, 1.0f);

      XYZ rv;
      RGB rv2;
      Chromaticity c;

      rv = cs.RGBtoXYZ(r);
      rv2 = cs.XYZtoRGB(rv);
      c = XYZtoChromaticity(rv);
      std::cout << r << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(g);
      rv2 = cs.XYZtoRGB(rv);
      c = XYZtoChromaticity(rv);
      std::cout << g << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(b);
      rv2 = cs.XYZtoRGB(rv);
      c = XYZtoChromaticity(rv);
      std::cout << b << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(w);
      rv2 = cs.XYZtoRGB(rv);
      c = XYZtoChromaticity(rv);
      std::cout << w << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;
   }

   for (float temp=1000.0f; temp<=10000.0f; temp+=500.0f)
   {
      XYZ xyz = Blackbody::GetXYZ(temp);

      std::cout << "Color temperature " << temp << std::endl;
      std::cout << "  xyz: " << xyz << std::endl;
      std::cout << "  rgb: " << Blackbody::GetRGB(temp, ColorSpace::Rec709, false) << std::endl;
      std::cout << "  rgb (normalized): " << Blackbody::GetRGB(temp, ColorSpace::Rec709, true) << std::endl;
      std::cout << "  chromaticity: " << XYZtoChromaticity(temp) << std::endl;
   }

   XYZ D50 = ChromaticityYtoXYZ(Chromaticity::IllumD50, 1.0f);
   XYZ D65 = ChromaticityYtoXYZ(Chromaticity::IllumD65, 1.0f);
   std::cout << "Chromatic adaptation matrices from D50 " << D50 << " to D65 " << D65 << std::endl;
   std::cout << "  VonKries: " << ChromaticAdaptationMatrix(D50, D65, CAT_VonKries) << std::endl;
   std::cout << "  Bradford: " << ChromaticAdaptationMatrix(D50, D65, CAT_Bradford) << std::endl;
   std::cout << "  XYZ: " << ChromaticAdaptationMatrix(D50, D65, CAT_XYZ) << std::endl;

   std::cout << "CIE L*a*b*" << std::endl;
   RGB c0 = RGB(0.2f, 0.6f, 1.0f);
   RGB c1 = RGB(0.7f, 0.3f, 0.8f);
   RGB c2 = RGB(0.9f, 0.1f, 0.2f);
   RGB c3 = RGB(1.0f, 1.0f, 1.0f);
   
   const ColorSpace &cs = ColorSpace::Rec709;
   
   XYZ xyz0 = cs.RGBtoXYZ(c0);
   XYZ xyz1 = cs.RGBtoXYZ(c1);
   XYZ xyz2 = cs.RGBtoXYZ(c2);
   XYZ xyz3 = cs.RGBtoXYZ(c3);
   
   LAB lab0 = cs.XYZtoLAB(xyz0);
   LAB lab1 = cs.XYZtoLAB(xyz1);
   LAB lab2 = cs.XYZtoLAB(xyz2);
   LAB lab3 = cs.XYZtoLAB(xyz3);
   
   LUV luv0 = cs.XYZtoLUV(xyz0);
   LUV luv1 = cs.XYZtoLUV(xyz1);
   LUV luv2 = cs.XYZtoLUV(xyz2);
   LUV luv3 = cs.XYZtoLUV(xyz3);
   
   std::cout << "  RGB -> XYZ -> LAB -> XYZ -> RGB" << std::endl;
   std::cout << "  " << c0 << " -> " << xyz0 << " -> " << lab0 << " -> " << cs.LABtoXYZ(lab0) << " -> " << cs.XYZtoRGB(cs.LABtoXYZ(lab0)) << std::endl;
   std::cout << "  " << c1 << " -> " << xyz1 << " -> " << lab1 << " -> " << cs.LABtoXYZ(lab1) << " -> " << cs.XYZtoRGB(cs.LABtoXYZ(lab1)) << std::endl;
   std::cout << "  " << c2 << " -> " << xyz2 << " -> " << lab2 << " -> " << cs.LABtoXYZ(lab2) << " -> " << cs.XYZtoRGB(cs.LABtoXYZ(lab2)) << std::endl;
   std::cout << "  " << c3 << " -> " << xyz3 << " -> " << lab3 << " -> " << cs.LABtoXYZ(lab3) << " -> " << cs.XYZtoRGB(cs.LABtoXYZ(lab3)) << std::endl;
   
   std::cout << "  RGB -> XYZ -> LUV -> XYZ -> RGB" << std::endl;
   std::cout << "  " << c0 << " -> " << xyz0 << " -> " << luv0 << " -> " << cs.LUVtoXYZ(luv0) << " -> " << cs.XYZtoRGB(cs.LUVtoXYZ(luv0)) << std::endl;
   std::cout << "  " << c1 << " -> " << xyz1 << " -> " << luv1 << " -> " << cs.LUVtoXYZ(luv1) << " -> " << cs.XYZtoRGB(cs.LUVtoXYZ(luv1)) << std::endl;
   std::cout << "  " << c2 << " -> " << xyz2 << " -> " << luv2 << " -> " << cs.LUVtoXYZ(luv2) << " -> " << cs.XYZtoRGB(cs.LUVtoXYZ(luv2)) << std::endl;
   std::cout << "  " << c3 << " -> " << xyz3 << " -> " << luv3 << " -> " << cs.LUVtoXYZ(luv3) << " -> " << cs.XYZtoRGB(cs.LUVtoXYZ(luv3)) << std::endl;
   
   return 0;
}
