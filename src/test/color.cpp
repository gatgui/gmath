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
      &ColorSpace::AlexaWide
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
      c = GetChromaticity(rv);
      std::cout << r << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(g);
      rv2 = cs.XYZtoRGB(rv);
      c = GetChromaticity(rv);
      std::cout << g << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(b);
      rv2 = cs.XYZtoRGB(rv);
      c = GetChromaticity(rv);
      std::cout << b << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

      rv = cs.RGBtoXYZ(w);
      rv2 = cs.XYZtoRGB(rv);
      c = GetChromaticity(rv);
      std::cout << w << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;
   }

   for (float temp=1000.0f; temp<=5000.0f; temp+=1000.0f)
   {
      std::cout << "Color temperature " << temp << " = xyz=" << Blackbody::GetXYZ(temp) << ", rgb=" << Blackbody::GetRGB(temp, ColorSpace::Rec709) << ", chromaticity=" << Blackbody::GetChromaticity(temp) << std::endl;
   }

   return 0;
}
