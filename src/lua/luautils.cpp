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
