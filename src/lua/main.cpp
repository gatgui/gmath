/*
MIT License

Copyright (c) 2009 Gaetan Guidet

This file is part of gmath.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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





