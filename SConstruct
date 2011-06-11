import glob
import excons
import excons.tools
from excons.tools import lua, gl, glut

prjs = [
  { "name"    : "gmath",
    "type"    : "sharedlib",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lib/*.cpp"),
    "defs"    : ["GMATH_EXPORTS"]
  },
  { "name"    : "tests",
    "type"    : "testprograms",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/test/*.cpp"),
    "libs"    : ["gmath"],
    "custom"  : [gl.Require, glut.Require]
  },
  { "name"    : "luagmath",
    "type"    : "dynamicmodule",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lua/*.cpp"),
    "libs"    : ["gmath"],
    "ext"     : ".so",
    "prefix"  : "lua",
    "custom"  : [lua.Require]
  }
]

env = excons.MakeBaseEnv()
excons.DeclareTargets(env, prjs)




