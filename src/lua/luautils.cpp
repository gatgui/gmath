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
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>

namespace lua {

void ClearStack(lua_State *L, int top) {
  int n = lua_gettop(L) - top;
  if (n > 0) {
    lua_pop(L, n);
  }
}

void ReduceStack(lua_State *L, int top) {
  while (lua_gettop(L) > top) {
    lua_remove(L, -2);
  }
}

int GetTable(lua_State *L, const char *name) {
  
  if (!name) {
    return 0;
  }

  int scope = LUA_GLOBALSINDEX;

  int oldtop = lua_gettop(L);

  char buffer[64];

  const char *str = name;
  const char *from = strchr(str, '.');

  size_t len;

  while (from) {
      
    len = from - str;
    strncpy(buffer, str, len);
    buffer[len] = '\0';

    lua_getfield(L, scope, buffer);
    
    if (lua_isnil(L, -1) == 1) {
      ClearStack(L, oldtop);
      return 0;
    }

    scope = lua_gettop(L);

    str = from + 1;
    from = strchr(str, '.');
  }

  len = strlen(name) - (str - name);
  strncpy(buffer, str, len);
  buffer[len] = '\0';

  lua_getfield(L, scope, buffer);

  if (lua_isnil(L, -1) == 1) {
    ClearStack(L, oldtop);
    return 0;
  }

  ReduceStack(L, oldtop+1);

  return 1;
}

void CreateModule(lua_State *L, const char *p, const char *n) {
  // setup new module table
  lua_newtable(L);
  lua_pushstring(L, n);
  lua_setfield(L, -2, "_NAME");
  lua_pushstring(L, p);
  lua_setfield(L, -2, "_PACKAGE");
  lua_pushvalue(L, -1);
  lua_setfield(L, -2, "_M");
  int module = lua_gettop(L);
  // now register module in package.loaded table
  lua_getfield(L, LUA_GLOBALSINDEX, "package"); // get package table
  lua_getfield(L, -1, "loaded"); // get package.loaded table
  lua_pushvalue(L, module); // duplicate module table stack entry on top
  lua_setfield(L, -2, n);   // package.loaded[n] = moduletable
  lua_pop(L, 2);            // pop package and package.loaded tables
}

void GetOrCreateModule(lua_State *L, const char *module) {

  if (!module) {
    return;
  }

  int oldtop = lua_gettop(L);

  // this seems reasonable
  assert(strlen(module) < 512);

  char buffer[64] = "";
  char modulename[512] = "";
  char packagename[512] = "";

  int scope = LUA_GLOBALSINDEX;

  const char *str = module;
  const char *from = strchr(str, '.');

  size_t len;

  while (from) {
    strcat(packagename, buffer);

    len = from - module;
    strncpy(modulename, module, len);
    modulename[len] = '\0';

    len = from - str;
    strncpy(buffer, str, len);
    buffer[len] = '\0';
    
    lua_getfield(L, scope, buffer);
    
    if (lua_isnil(L, -1) == 1) {
      lua_pop(L, 1);
      CreateModule(L, packagename, modulename);
      // add new module to scope
      lua_pushvalue(L, -1);
      lua_setfield(L, scope, buffer);
    }
    
    scope = lua_gettop(L);
    
    str = from + 1;
    from = strchr(str, '.');
  }

  // and the last one !

  strcat(packagename, buffer);

  len = strlen(module) - (str - module);
  strncpy(buffer, str, len);
  buffer[len] = '\0';
  
  lua_getfield(L, scope, buffer);
  if (lua_isnil(L, -1) == 1) {
    lua_pop(L, 1);
    CreateModule(L, packagename, module);
    // add module to scope
    lua_pushvalue(L, -1);
    lua_setfield(L, scope, buffer);
  }

  // Keep only last module on stack
  ReduceStack(L, oldtop+1);
}


}
