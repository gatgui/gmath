/*

Copyright (C) 2016  Gaetan Guidet

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
#include <gmath/params.h>

int main(int, char **)
{
   gmath::Params params;
   
   params.set("key", 0.0f);
   
   gmath::Params::accessor tmp0;
   gmath::Params::accessor tmp1(params, "dummy");
   
   if (tmp0.valid())
   {
      std::cerr << "Accessor validity failed (default)" << std::endl;
      return 1;
   }
   
   if (tmp1.valid())
   {
      std::cerr << "Accessor validity failed (unknown key)" << std::endl;
      return 1;
   }
   
   gmath::Params::accessor a0(params, "key");
   gmath::Params::accessor a1(params, "key");
   gmath::Params::accessor a2(a0);
   
   if (a0 != a1 || a1 != a2)
   {
      std::cerr << "Accessor equality failed" << std::endl;
      return 1;
   }
   
   a0 = 1.0f;
   
   if (float(a1) != 1.0f)
   {
      std::cerr << "Accessor assignment failed" << std::endl;
      return 1;
   }
   
   float v;
   if (!params.get("key", v) || v != float(a0))
   {
      std::cerr << "Accessor assignment failed" << std::endl;
      return 1;
   }
   
   std::cout << "Success: v=" << float(a2) << std::endl;
   
   return 0;
}
