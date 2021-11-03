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

#ifndef __luautils_h_
#define __luautils_h_

#include <lua.hpp>

#define Method(class, name) {#name, &class::name}

#define NO_CONSTANT \
  static bool __lua_HasConstants() {return false;}

#define REGISTER_CONSTANTS\
  static bool __lua_HasConstants() {return true;}\
  static int __lua_NoConstantAssign(lua_State *L) {\
    if (lua_isstring(L, 2)) {\
      const char *pname = lua_tostring(L, 2);\
      const char **name = &Constants[0];\
      while (name) {\
        if (!strcmp(pname, *name)) {\
          lua_pushstring(L, "Cannot assign constant");\
          lua_error(L);\
        }\
        ++name;\
      }\
    }\
    lua_getmetatable(L, 1);\
    lua_pushvalue(L, 2);\
    lua_pushvalue(L, 3);\
    lua_settable(L, -3);\
    lua_pop(L, 4);\
    return 0;\
  }\
  static void __lua_RegisterConstants(lua_State *L, int table, int klass)

namespace lua {

  extern void ClearStack(lua_State *L, int top);

  extern void ReduceStack(lua_State *L, int top);

  extern int GetTable(lua_State *L, const char *name);

  extern void CreateModule(lua_State *L, const char *package, const char *name);

  extern void GetOrCreateModule(lua_State *L, const char *module);

  template <typename T>
  class Wrapper {
    public:
      
      typedef int (*luafunc)(lua_State*);
      
      struct Entry {
        const char *fname;
        luafunc fptr;
      };
  
    public:

      static T* Check(lua_State *L, int narg) {
        // could be a subclass
        void *p = lua_touserdata(L, narg);
        
        if (!p) {
          luaL_typerror(L, narg, "gmath.Vector2");
        }
        
        lua_pushlightuserdata(L, (void*)(&T::Methods[0]));
        lua_gettable(L, LUA_REGISTRYINDEX);
        
        if (!lua_getmetatable(L, narg) || !lua_rawequal(L, -1, -2)) {
          luaL_typerror(L, narg, "gmath.Vector2");
        }
  
        lua_pop(L, 2);
  
        return ((T*) p);
      }
  
      static int Register(lua_State *L,
                          const char *superclass=0,
                          const char *modulename=0) {
        
        int oldtop = lua_gettop(L);
  
        GetOrCreateModule(L, modulename);
        int module = lua_gettop(L);
        if (module == oldtop) {
          module = LUA_GLOBALSINDEX;
        }
  
        lua_newtable(L);
        int klass = lua_gettop(L);
        
        lua_pushvalue(L, klass);
        
        lua_setfield(L, module, T::ClassName);
        
        lua_pushvalue(L, klass);
        lua_setfield(L, klass, "__index");
        
        lua_pushcfunction(L, ToString);
        lua_setfield(L, klass, "__tostring");
  
        lua_pushcfunction(L, Delete);
        lua_setfield(L, klass, "__gc");
  
        lua_pushcfunction(L, New);
        lua_setfield(L, klass, "new");
  
        const Entry *e;
        e = &T::ClassMethods[0];
        while (e->fname) {
          lua_pushcfunction(L, e->fptr);
          lua_setfield(L, klass, e->fname);
          ++e;
        }

        e = &T::Methods[0];
        while (e->fname) {
          lua_pushcfunction(L, e->fptr);
          lua_setfield(L, klass, e->fname);
          ++e;
        }
        
        bool hasmeta = false;
  
        if (GetTable(L, superclass) == 1) { // +1
          
          int superklass = lua_gettop(L);
  
          lua_pushvalue(L, superklass); // +1
          lua_setfield(L, klass, "super"); // -1

          lua_newtable(L); // +1
          int metaklass = lua_gettop(L);
          
          lua_pushvalue(L, superklass); // +1
          lua_setfield(L, metaklass, "__index"); // -1
  
          lua_setmetatable(L, klass); // -1
          
          hasmeta = true;
  
          lua_pop(L, 1); // -1
        }
  
        lua_pushlightuserdata(L, (void*)(&T::Methods[0]));
        lua_pushvalue(L, klass);
        lua_settable(L, LUA_REGISTRYINDEX);
  
        //ReduceStack(L, oldtop+1);
        
        if (T::__lua_HasConstants()) {
          
          if (!hasmeta) {
            
            lua_newtable(L); // +1
            int metaklass = lua_gettop(L);
            lua_pushvalue(L, metaklass); // +1
            lua_setfield(L, metaklass, "__index"); // -1
            
            lua_pushcfunction(L, &T::__lua_NoConstantAssign); // +1
            lua_setfield(L, metaklass, "__newindex"); // -1
            
            T::__lua_RegisterConstants(L, metaklass, klass); // +/- 0
            
            lua_setmetatable(L, klass); // -1
            
          } else {
            
            // -> create an intermediate metatable with metatable set to original metatable
          }
        }
        
        ReduceStack(L, oldtop+1);

        return 1;
      }

    public:

      static int New(lua_State *L) {
        
        int oldtop = lua_gettop(L);
        int narg = oldtop;
        
        void *ud = lua_newuserdata(L, sizeof(T));
        new (ud) T();        

        lua_pushlightuserdata(L, (void*)(&T::Methods[0]));
        lua_gettable(L, LUA_REGISTRYINDEX);
        
        lua_setmetatable(L, -2);
        lua_insert(L, 1);
        
        lua_pushlightuserdata(L, (void*)(&T::Methods[0]));
        lua_gettable(L, LUA_REGISTRYINDEX);
        lua_getfield(L, -1, "initialize");
        lua_remove(L, -2);
        lua_insert(L, 1);
  
        lua_pushvalue(L, 2);  // 2: class instance table
        lua_insert(L, 1);
  
        lua_call(L, narg+1, 0);
  
        return 1;
      }
  
      static int Delete(lua_State *L) {
        T *v = (T*) lua_touserdata(L, 1);
        v->~T();
        lua_pop(L, 1);
        return 0;  
      }
  
      static int ToString(lua_State *L) {
        char buffer[32];
        T *obj = (T*) lua_touserdata(L, 1);
        sprintf(buffer, "%p", obj);
        lua_pushfstring(L, "%s (%s)", T::ClassName, buffer);
        return 1;
      }
  };

}


#endif
