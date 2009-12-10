import glob
import excons
import excons.tools
from excons.tools import lua

prjs = [
  { "name"    : "gmath",
    "type"    : "sharedlib",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lib/*.cpp"),
    "defs"    : ["GMATH_EXPORTS"]
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




