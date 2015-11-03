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

int main(int, char**)
{
   std::cout << ColorSpace::Rec709 << std::endl;

   RGB r = RGBCreate(1.0f, 0.0f, 0.0f);
   RGB g = RGBCreate(0.0f, 1.0f, 0.0f);
   RGB b = RGBCreate(0.0f, 0.0f, 1.0f);
   RGB w = RGBCreate(1.0f, 1.0f, 1.0f);

   XYZ rv;
   RGB rv2;
   Chromaticity c;

   rv = ColorSpace::Rec709.RGBtoXYZ(r);
   rv2 = ColorSpace::Rec709.XYZtoRGB(rv);
   c = GetChromaticity(rv);
   std::cout << r << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

   rv = ColorSpace::Rec709.RGBtoXYZ(g);
   rv2 = ColorSpace::Rec709.XYZtoRGB(rv);
   c = GetChromaticity(rv);
   std::cout << g << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

   rv = ColorSpace::Rec709.RGBtoXYZ(b);
   rv2 = ColorSpace::Rec709.XYZtoRGB(rv);
   c = GetChromaticity(rv);
   std::cout << b << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

   rv = ColorSpace::Rec709.RGBtoXYZ(w);
   rv2 = ColorSpace::Rec709.XYZtoRGB(rv);
   c = GetChromaticity(rv);
   std::cout << w << " -> " << rv << " (chromaticity: " << c.x << ", " << c.y << ") -> " << rv2 << std::endl;

   return 0;
}
