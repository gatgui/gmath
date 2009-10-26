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
#include <gmath/gmath>
#include <cassert>
#include <string>
#include <sstream>

#ifdef _WIN32
# define EXPORT extern "C" __declspec(dllexport)
#else
# define EXPORT extern "C"
#endif

// ---

#define ToLuaVector2(state, arg) \
  lua::Wrapper<LuaVector2>::Check(state, arg)

#define ToVector2(var, state, arg) \
  gmath::Vector2 *var = ToLuaVector2(state, arg)->ptr()

#define ToVector2_NoConst(var, state, arg) \
  LuaVector2 *__tmp_lv2 = ToLuaVector2(state, arg);\
  if (__tmp_lv2->isConstant()) {\
    lua_pushstring(L, "Trying to modify a constant gmath.Vector2");\
    lua_error(L);\
  }\
  gmath::Vector2 *var = __tmp_lv2->ptr()

class LuaVector2 {
  public:
    
    static const char ClassName[];
    static const char *Constants[];
    static lua::Wrapper<LuaVector2>::Entry Methods[];
    static lua::Wrapper<LuaVector2>::Entry ClassMethods[];

    LuaVector2(bool constant = false)
      : mConstant(constant) {
      //std::cout << "### LuaVector()" << std::endl;
    }

    ~LuaVector2() {
      //std::cout << "### ~LuaVector2()" << std::endl;
    }
    
    inline bool isConstant() const {
      return mConstant;
    }

    inline gmath::Vector2* ptr() {
      return &mVector;
    }

    // LuaVector2 is the created object

    static int initialize(lua_State *L) {
      int narg = lua_gettop(L);
      
      ToVector2(v2, L, 1);

      if (narg == 1) {
        // Nothing to do
      } else if (narg == 2) {
        // One float, table or vector
        if (lua_isnumber(L, 2) == 0) {
          //luaL_argerror(L, 2, "Expected number");
          
          if (lua_type(L, 2) == LUA_TTABLE) {
            lua_Number n;

            lua_pushnumber(L, 1);
            lua_gettable(L, 2);
            n = lua_tonumber(L, -1);
            v2->x = float(n);
            lua_pop(L, 1);

            lua_pushnumber(L, 2);
            lua_gettable(L, 2);
            n = lua_tonumber(L, -1);
            v2->y = float(n);
            lua_pop(L, 1);

          } else {
            ToVector2(rhs, L, 2);
            *v2 = *rhs;
          }

        } else {
          lua_Number n = lua_tonumber(L, 2);
          v2->x = float(n);
          v2->y = float(n);        
        }

      } else if (narg == 3) {
        // Two float
        if (lua_isnumber(L, 2) == 0) {
          luaL_argerror(L, 2, "Expected number");
        }
        if (lua_isnumber(L, 3) == 0) {
          luaL_argerror(L, 3, "Expected number");
        }
        v2->x = float(lua_tonumber(L, 2));
        v2->y = float(lua_tonumber(L, 3));
 
      } else {
        lua_pushstring(L, "gmath.Vector2.initialize: invalid arguments");
        lua_error(L);
      }

      lua_pop(L, narg);

      return 0;
    }
    
    static int setproperty(lua_State *L) {
      
      ToVector2_NoConst(v2, L, 1);
      
      lua_Number n = lua_tonumber(L, 2);
      if (n == 0) {
      
        std::string pname = lua_tostring(L, 2);
        
        // index 0 is invalid in lua, but it has been used here !
        if (pname == "0") {
          lua_pushstring(L, "Invalid index for gmath.Vector2 [0]");
          lua_error(L);
        }
      
        if (lua_isnumber(L, 3)) {
          if (pname == "x") {
            v2->x = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (pname == "y") {
            v2->y = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          }
        } 
      
      } else {
        
        if (lua_isnumber(L, 3)) {
          if (n == 1) {
            v2->x = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (n == 2) {
            v2->y = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else {
            lua_pushfstring(L, "Invalid index for gmath.Vector2 [%d]", n);
            lua_error(L);
          }
        }
      }
      
      lua_getmetatable(L, 1);
      lua_pushvalue(L, 2);
      lua_pushvalue(L, 3);
      lua_settable(L, -3); // this leave "userdata | key | val | mt" on the stack
      lua_pop(L, 4);
      
      return 0;
    }
    
    static int getproperty(lua_State *L) {
      ToVector2(v2, L, 1);
      
      lua_Number n = lua_tonumber(L, 2);
      if (n == 0) {
        
        std::string pname = lua_tostring(L, 2);
        
        // index 0 is invalid in lua, but it has been used here !
        if (pname == "0") {
          lua_pushstring(L, "Invalid index for gmath.Vector2 [0]");
          lua_error(L);
        }
        
        if (pname == "x") {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->x);
          return 1;
          
        } else if (pname == "y") {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->y);
          return 1;

        } else if (pname == "length") {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->getLength());
          return 1;
  
        } else if (pname == "squaredLength") {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->getSquaredLength());
          return 1;
        
        }
      
      } else {
        if (n == 1) {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->x);
          return 1;
          
        } else if (n == 2) {
          lua_pop(L, 2);
          lua_pushnumber(L, v2->y);
          return 1;
          
        } else {
          lua_pushfstring(L, "Invalid index for gmath.Vector2 [%d]", n);
          lua_error(L);
        }
      }

      lua_getmetatable(L, 1);             // userdata | key | mt
      lua_pushvalue(L, 2);                // userdata | key | mt | key
      lua_gettable(L, -2);                // userdata | key | mt | field
      lua_remove(L, 1);                   // pop userdata
      lua_remove(L, 1);                   // pop key
      lua_remove(L, 1);                   // pop mt
      return 1;
    }
    
    static int tostring(lua_State *L) {
      ToVector2(v2, L, 1);
      std::ostringstream oss;
      oss << *v2;
      lua_pop(L, 1);
      lua_pushstring(L, oss.str().c_str());
      return 1;
    }

    static int equals(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 2);
      if (v0->equals(*v1)) {
        lua_pushboolean(L, 1);
      } else {
        lua_pushboolean(L, 0);
      }
      return 1;
    }

    static int ortho(lua_State *L) {
      ToVector2(v0, L, 1);
      lua_pop(L, 1);
      gmath::Vector2 v1 = v0->getOrtho();
      lua_pushnumber(L, v1.x);
      lua_pushnumber(L, v1.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int dot(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 1);
      lua_pop(L, 2);
      float dp = v0->dot(*v1);
      lua_pushnumber(L, dp);
      return 1;
    }

    static int normalize(lua_State *L) {
      ToVector2_NoConst(v, L, 1);
      v->normalize();
      return 1;
    }

    static int floor(lua_State *L) {
      ToVector2_NoConst(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 1);
      v0->floor(*v1);
      return 1;
    }

    static int ceil(lua_State *L) {
      ToVector2_NoConst(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 1);
      v0->ceil(*v1);
      return 1;
    }
    
    static int len(lua_State *L) {
      lua_pop(L, 1);
      lua_pushinteger(L, 2);
      return 1;
    }

    static int add(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 2);
      gmath::Vector2 tmp = *v0 + *v1;
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int sub(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 2);
      gmath::Vector2 tmp = *v0 - *v1;
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int mul(lua_State *L) {
      gmath::Vector2 tmp;
      if (lua_isnumber(L, 1)) {
        lua_Number n = lua_tonumber(L, 1);
        ToVector2(v1, L, 2);
        tmp = float(n) * *v1;
      } else if (lua_isnumber(L, 2)) {
        ToVector2(v0, L, 1);
        lua_Number n = lua_tonumber(L, 2);
        tmp = float(n) * *v0;
      } else {
        ToVector2(v0, L, 1);
        ToVector2(v1, L, 2);
        tmp = *v0 * *v1;
      }
      lua_pop(L, 2);
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int div(lua_State *L) {
      gmath::Vector2 tmp;
      if (lua_isnumber(L, 2)) {
        ToVector2(v0, L, 1);
        lua_Number n = lua_tonumber(L, 2);
        tmp = *v0 / float(n);
      } else {
        ToVector2(v0, L, 1);
        ToVector2(v1, L, 2);
        tmp = *v0 / *v1;
      }
      lua_pop(L, 2);
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int neg(lua_State *L) {
      ToVector2(v, L, 1);
      lua_pop(L, 1);
      gmath::Vector2 n = -(*v);
      lua_pushnumber(L, n.x);
      lua_pushnumber(L, n.y);
      return lua::Wrapper<LuaVector2>::New(L);
    }

    static int lessthan(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 2);
      int n = (*v0 < *v1 ? 1 : 0);
      lua_pushboolean(L, n);
      return 1;
    }

    static int lessequal(lua_State *L) {
      ToVector2(v0, L, 1);
      ToVector2(v1, L, 2);
      lua_pop(L, 2);
      int n = (*v0 <= *v1 ? 1 : 0);
      lua_pushboolean(L, n);
      return 1;
    }
    
    // use NO_CONSTANT macro if class doesn't have any constant

    REGISTER_CONSTANTS {
    
      void *ud = 0;
      gmath::Vector2 *v = 0;

      // do not call lua::Wrapper<LuaVector2>::New(L)
      // as the stack contains more thing than just self and initialize arguments
      // -> call of initialize will fail
      //    if initialize had fixed argument count, this would work

#define VECTOR2_CONSTANT(name, xv, yv)\
  ud = lua_newuserdata(L, sizeof(LuaVector2));\
  new (ud) LuaVector2(true);\
  v = ((LuaVector2*)ud)->ptr();\
  v->x = xv;\
  v->y = yv;\
  lua_pushvalue(L, klass);\
  lua_setmetatable(L, -2);\
  lua_setfield(L, table, #name)

      VECTOR2_CONSTANT(ZERO, 0, 0);
      VECTOR2_CONSTANT(UNIT_X, 1, 0);
      VECTOR2_CONSTANT(UNIT_Y, 0, 1);

#undef VECTOR2_CONSTANT

    }

  private:

    gmath::Vector2 mVector;
    bool mConstant;
};

const char LuaVector2::ClassName[] = "Vector2";

const char * LuaVector2::Constants[] = {
  "ZERO",
  "UNIT_X",
  "UNIT_Y",
  0
};

lua::Wrapper<LuaVector2>::Entry LuaVector2::ClassMethods[] = {
  {0, 0}
};

lua::Wrapper<LuaVector2>::Entry LuaVector2::Methods[] = {
  {"__tostring", &LuaVector2::tostring},
  {"__index", &LuaVector2::getproperty},
  {"__newindex", &LuaVector2::setproperty},
  {"__eq", &LuaVector2::equals},
  {"__len", &LuaVector2::len},
  {"__unm", &LuaVector2::neg},
  {"__add", &LuaVector2::add},
  {"__sub", &LuaVector2::sub},
  {"__mul", &LuaVector2::mul},
  {"__div", &LuaVector2::div},
  {"__lt", &LuaVector2::lessthan},
  {"__le", &LuaVector2::lessequal},
  Method(LuaVector2, initialize),
  Method(LuaVector2, dot),
  Method(LuaVector2, normalize),
  Method(LuaVector2, floor),
  Method(LuaVector2, ceil),
  Method(LuaVector2, ortho),
  {0, 0}
};

// ---

#define ToLuaVector3(state, arg) \
  lua::Wrapper<LuaVector3>::Check(state, arg)

#define ToVector3(var, state, arg) \
  gmath::Vector3 *var = ToLuaVector3(state, arg)->ptr()

#define ToVector3_NoConst(var, state, arg) \
  LuaVector3 *__tmp_lv3 = ToLuaVector3(state, arg);\
  if (__tmp_lv3->isConstant()) {\
    lua_pushstring(L, "Trying to modify a constant gmath.Vector3");\
    lua_error(L);\
  }\
  gmath::Vector3 *var = __tmp_lv3->ptr()

class LuaVector3 {
  public:
    
    static const char ClassName[];
    static const char *Constants[];
    static lua::Wrapper<LuaVector3>::Entry Methods[];
    static lua::Wrapper<LuaVector3>::Entry ClassMethods[];

    LuaVector3(bool constant = false)
      : mConstant(constant) {
      //std::cout << "### LuaVector3()" << std::endl;
    }

    ~LuaVector3() {
      //std::cout << "### ~LuaVector3()" << std::endl;
    }
    
    inline bool isConstant() const {
      return mConstant;
    }

    inline gmath::Vector3* ptr() {
      return &mVector;
    }

    // LuaVector3 is the created object

    static int initialize(lua_State *L) {

      int narg = lua_gettop(L);
      
      ToVector3(v, L, 1);

      if (narg == 1) {
        // self: NOOP

      } else if (narg == 2) {
        // self + 1 arg        

        if (lua_isnumber(L, 2) == 0) {
          
          if (lua_type(L, 2) == LUA_TTABLE) {
            lua_Number n;

            lua_pushnumber(L, 1);
            lua_gettable(L, 2);
            n = lua_tonumber(L, -1);
            v->x = float(n);
            lua_pop(L, 1);

            lua_pushnumber(L, 2);
            lua_gettable(L, 2);
            n = lua_tonumber(L, -1);
            v->y = float(n);
            lua_pop(L, 1);

            lua_pushnumber(L, 3);
            lua_gettable(L, 2);
            n = lua_tonumber(L, -1);
            v->z = float(n);
            lua_pop(L, 1);

          } else {
            ToVector3(rhs, L, 2);
            *v = *rhs;
          }

        } else {
          lua_Number n = lua_tonumber(L, 2);
          v->x = float(n);
          v->y = float(n);
          v->z = float(n);        
        }

      } else if (narg == 4) {
        // self + 3 args

        if (lua_isnumber(L, 2) == 0) {
          luaL_argerror(L, 2, "Expected number");
        }

        if (lua_isnumber(L, 3) == 0) {
          luaL_argerror(L, 3, "Expected number");
        }

        if (lua_isnumber(L, 4) == 0) {
          luaL_argerror(L, 3, "Expected number");
        }

        v->x = float(lua_tonumber(L, 2));
        v->y = float(lua_tonumber(L, 3));
        v->z = float(lua_tonumber(L, 4)); 

      } else {
        lua_pushstring(L, "gmath.Vector3.initialize: invalid arguments");
        lua_error(L);
      }

      lua_pop(L, narg);

      return 0;
    }
    
    static int setproperty(lua_State *L) {
      
      ToVector3_NoConst(v, L, 1);
      
      lua_Number n = lua_tonumber(L, 2);
      
      if (n == 0) {
      
        std::string pname = lua_tostring(L, 2);
        
        // index 0 is invalid in lua
        if (pname == "0") {
          lua_pushstring(L, "Invalid index for gmath.Vector3 [0]");
          lua_error(L);
        }
      
        if (lua_isnumber(L, 3)) {
          if (pname == "x") {
            v->x = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (pname == "y") {
            v->y = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (pname == "z") {
            v->z = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          }
        }
      } else {
        
        if (lua_isnumber(L, 3)) {

          if (n == 1) {
            v->x = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (n == 2) {
            v->y = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;
          
          } else if (n == 3) {
            v->z = float(lua_tonumber(L, 3));
            lua_pop(L, 3);
            return 0;

          } else {
            lua_pushfstring(L, "Invalid index for gmath.Vector3 [%d]", n);
            lua_error(L);
          }
        }
      }
      
      lua_getmetatable(L, 1); // +1
      lua_pushvalue(L, 2); // +1
      lua_pushvalue(L, 3); // +1
      lua_settable(L, -3); // -2
      lua_pop(L, 4); // 3 original args + 1
      
      return 0;
    }
    
    static int getproperty(lua_State *L) {
      ToVector3(v, L, 1);
      
      lua_Number n = lua_tonumber(L, 2);

      if (n == 0) {
        
        std::string pname = lua_tostring(L, 2);
        
        if (pname == "0") {
          lua_pushstring(L, "Invalid index for gmath.Vector3 [0]");
          lua_error(L);
        }
        
        if (pname == "x") {
          lua_pop(L, 2);
          lua_pushnumber(L, v->x);
          return 1;
          
        } else if (pname == "y") {
          lua_pop(L, 2);
          lua_pushnumber(L, v->y);
          return 1;

        } else if (pname == "z") {
          lua_pop(L, 2);
          lua_pushnumber(L, v->z);
          return 1;

        } else if (pname == "length") {
          lua_pop(L, 2);
          lua_pushnumber(L, v->getLength());
          return 1;
  
        } else if (pname == "squaredLength") {
          lua_pop(L, 2);
          lua_pushnumber(L, v->getSquaredLength());
          return 1;
        
        }
      
      } else {
        if (n == 1) {
          lua_pop(L, 2);
          lua_pushnumber(L, v->x);
          return 1;
          
        } else if (n == 2) {
          lua_pop(L, 2);
          lua_pushnumber(L, v->y);
          return 1;
        
        } else if (n == 3) {
          lua_pop(L, 2);
          lua_pushnumber(L, v->z);
          return 1;

        } else {
          lua_pushfstring(L, "Invalid index for gmath.Vector3 [%d]", n);
          lua_error(L);
        }
      }

      lua_getmetatable(L, 1); // +1
      lua_pushvalue(L, 2); // +1 [key]
      lua_gettable(L, -2); // -2
      lua_remove(L, 1);
      lua_remove(L, 1);
      lua_remove(L, 1);
      return 1;
    }
    
    static int tostring(lua_State *L) {
      ToVector3(v, L, 1);
      std::ostringstream oss;
      oss << *v;
      lua_pop(L, 1);
      lua_pushstring(L, oss.str().c_str());
      return 1;
    }

    static int equals(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      if (v0->equals(*v1)) {
        lua_pushboolean(L, 1);
      } else {
        lua_pushboolean(L, 0);
      }
      return 1;
    }

    static int dirEquals(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      float atol = float(lua_tonumber(L, 3));
      lua_pop(L, 3);
      if (v0->dirEquals(*v1, atol)) {
        lua_pushboolean(L, 1);
      } else {
        lua_pushboolean(L, 0);
      }
      return 1;
    }

    static int cross(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      gmath::Vector3 v2 = v0->cross(*v1);
      lua_pushnumber(L, v2.x);
      lua_pushnumber(L, v2.y);
      lua_pushnumber(L, v2.z);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int dot(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 1);
      lua_pop(L, 2);
      float dp = v0->dot(*v1);
      lua_pushnumber(L, dp);
      return 1;
    }

    static int normalize(lua_State *L) {
      ToVector3_NoConst(v, L, 1);
      v->normalize();
      return 1;
    }

    static int floor(lua_State *L) {
      ToVector3_NoConst(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 1);
      v0->floor(*v1);
      return 1;
    }

    static int ceil(lua_State *L) {
      ToVector3_NoConst(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 1);
      v0->ceil(*v1);
      return 1;
    }
    
    static int len(lua_State *L) {
      lua_pop(L, 1);
      lua_pushinteger(L, 3);
      return 1;
    }

    static int add(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      gmath::Vector3 tmp = *v0 + *v1;
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      lua_pushnumber(L, tmp.z);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int sub(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      gmath::Vector3 tmp = *v0 - *v1;
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int mul(lua_State *L) {
      gmath::Vector3 tmp;
      if (lua_isnumber(L, 1)) {
        lua_Number n = lua_tonumber(L, 1);
        ToVector3(v1, L, 2);
        tmp = float(n) * *v1;
      } else if (lua_isnumber(L, 2)) {
        ToVector3(v0, L, 1);
        lua_Number n = lua_tonumber(L, 2);
        tmp = float(n) * *v0;
      } else {
        ToVector3(v0, L, 1);
        ToVector3(v1, L, 2);
        tmp = *v0 * *v1;
      }
      lua_pop(L, 2);
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      lua_pushnumber(L, tmp.y);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int div(lua_State *L) {
      gmath::Vector3 tmp;
      if (lua_isnumber(L, 2)) {
        ToVector3(v0, L, 1);
        lua_Number n = lua_tonumber(L, 2);
        tmp = *v0 / float(n);
      } else {
        ToVector3(v0, L, 1);
        ToVector3(v1, L, 2);
        tmp = *v0 / *v1;
      }
      lua_pop(L, 2);
      lua_pushnumber(L, tmp.x);
      lua_pushnumber(L, tmp.y);
      lua_pushnumber(L, tmp.z);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int neg(lua_State *L) {
      ToVector3(v, L, 1);
      lua_pop(L, 1);
      lua_pushnumber(L, - v->x);
      lua_pushnumber(L, - v->y);
      lua_pushnumber(L, - v->z);
      return lua::Wrapper<LuaVector3>::New(L);
    }

    static int lessthan(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      int n = (*v0 < *v1 ? 1 : 0);
      lua_pushboolean(L, n);
      return 1;
    }

    static int lessequal(lua_State *L) {
      ToVector3(v0, L, 1);
      ToVector3(v1, L, 2);
      lua_pop(L, 2);
      int n = (*v0 <= *v1 ? 1 : 0);
      lua_pushboolean(L, n);
      return 1;
    }
    
    // use NO_CONSTANT macro if class doesn't have any constant

    REGISTER_CONSTANTS {
    
      void *ud = 0;
      gmath::Vector3 *v = 0;

#define VECTOR3_CONSTANT(name, xv, yv, zv)\
  ud = lua_newuserdata(L, sizeof(LuaVector3));\
  new (ud) LuaVector3(true);\
  v = ((LuaVector3*)ud)->ptr();\
  v->x = xv;\
  v->y = yv;\
  v->z = zv;\
  lua_pushvalue(L, klass);\
  lua_setmetatable(L, -2);\
  lua_setfield(L, table, #name)

      VECTOR3_CONSTANT(ZERO, 0, 0, 0);
      VECTOR3_CONSTANT(UNIT_X, 1, 0, 0);
      VECTOR3_CONSTANT(UNIT_Y, 0, 1, 0);
      VECTOR3_CONSTANT(UNIT_Z, 0, 0, 1);
      VECTOR3_CONSTANT(NEG_UNIT_X, -1, 0, 0);
      VECTOR3_CONSTANT(NEG_UNIT_Y, 0, -1, 0);
      VECTOR3_CONSTANT(NEG_UNIT_Z, 0, 0, -1);
      VECTOR3_CONSTANT(UNIT_SCALE, 1, 1, 1);

#undef VECTOR3_CONSTANT

    }

  private:

    gmath::Vector3 mVector;
    bool mConstant;
};

const char LuaVector3::ClassName[] = "Vector3";

const char * LuaVector3::Constants[] = {
  "ZERO",
  "UNIT_X",
  "UNIT_Y",
  "UNIT_Z",
  "NEG_UNIT_X",
  "NEG_UNIT_Y",
  "NEG_UNIT_Z",
  "UNIT_SCALE",
  0
};

lua::Wrapper<LuaVector3>::Entry LuaVector3::ClassMethods[] = {
  {0, 0}
};

lua::Wrapper<LuaVector3>::Entry LuaVector3::Methods[] = {
  Method(LuaVector3, initialize),
  {"__tostring", &LuaVector3::tostring},
  {"__index", &LuaVector3::getproperty},
  {"__newindex", &LuaVector3::setproperty},
  {"__eq", &LuaVector3::equals},
  {"__len", &LuaVector3::len},
  {"__unm", &LuaVector3::neg},
  {"__add", &LuaVector3::add},
  {"__sub", &LuaVector3::sub},
  {"__mul", &LuaVector3::mul},
  {"__div", &LuaVector3::div},
  {"__lt", &LuaVector3::lessthan},
  {"__le", &LuaVector3::lessequal},
  Method(LuaVector3, dot),
  Method(LuaVector3, normalize),
  Method(LuaVector3, floor),
  Method(LuaVector3, ceil),
  Method(LuaVector3, cross),
  Method(LuaVector3, dirEquals),
  {0, 0}
};


// ---

EXPORT int luaopen_gmath_vector(lua_State *L) {
  //return lua::Wrapper<LuaVector2>::Register(L, 0, "gmath");
  int top = lua_gettop(L);
  lua::Wrapper<LuaVector2>::Register(L, 0, "gmath");
  lua::Wrapper<LuaVector3>::Register(L, 0, "gmath");
  std::cout << "luaopen_gmath_vector: added on stack: " << (lua_gettop(L) - top)
            << std::endl;
  return (lua_gettop(L) - top);
}
