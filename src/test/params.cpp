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
#include <gmath/color.h>

using namespace gmath;

int main(int, char **)
{
   Params params;
   
   params.set("key", 0.0f);
   
   Params::accessor tmp0;
   Params::accessor tmp1(params, "dummy");
   
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
   
   Params::accessor a0(params, "key");
   Params::accessor a1(params, "key");
   Params::accessor a2(a0);
   
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
   
   ToneMappingOperator tmo;
   ToneMappingOperator::ReinhardParams tmp;
   ToneMappingOperator::ReinhardConstParams tmpc;
   
   tmo.setMethod(ToneMappingOperator::Reinhard);
   if (!tmo.getParams(tmp))
   {
      std::cerr << "Failed to get tone mapping operator params" << std::endl;
      return 1;
   }
   tmp.key = 0.2f;
   tmp.Lavg = 1.5f;
   tmp.Lwht = 9.2f;
   tmo.validate();
   
   if (!tmo.isValid())
   {
      std::cerr << "Invalid tone mapping operator params" << std::endl;
      return 1;
   }
   
   tmo.copyParams(params);
   float key = 0.0f;
   float Lavg = 0.0f;
   float Lwht = 0.0f;
   if (params.get("key", key) && params.get("Lavg", Lavg) && params.get("Lwht", Lwht))
   {
      std::cout << "key=" << key << ", Lavg=" << Lavg << ", Lwht=" << Lwht << std::endl;
      
      tmo.getParams(tmpc);
      if (float(tmpc.key) != key || float(tmpc.Lavg) != Lavg || float(tmpc.Lwht) != Lwht)
      {
         std::cerr << "Const params values are invalid" << std::endl;
         return 1;
      }
      
      const ToneMappingOperator &tmoc = tmo;
      if (tmoc.getParams(tmp))
      {
         std::cerr << "Should failed to get tone mapping operator non-const params from const object" << std::endl;
         return 1;
      }
   }
   else
   {
      std::cerr << "Failed to get tone mapping operator params" << std::endl;
      return 1;
   }
   
   return 0;
}
