/*

Copyright (C) 2009  Gaetan Guidet

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

#include <lua/luautils.h>

#ifdef _WIN32
# define EXPORT extern "C" __declspec(dllexport)
#else
# define EXPORT extern "C"
#endif

EXPORT int luaopen_gmath_vector(lua_State*);

EXPORT int luaopen_luagmath(lua_State *L) {
  // create a new table in globals named gmath

  int oldtop = lua_gettop(L);
  
  luaopen_gmath_vector(L);

  // clear stack
  int n = lua_gettop(L) - oldtop;
  if (n > 0) {
    lua_pop(L, n);
  }
  
  // also pop input module name (came as argument)
  lua_pop(L, 1);

  // module on top
  lua_getfield(L, LUA_GLOBALSINDEX, "gmath");

  return 1;
}





