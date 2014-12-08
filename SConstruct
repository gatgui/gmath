try:
  import excons
except:
  import subprocess
  subprocess.Popen("git submodule init", shell=True).communicate()
  subprocess.Popen("git submodule update", shell=True).communicate()
  import excons

import glob
import excons.tools
from excons.tools import lua, gl, glut

staticBuild = (int(ARGUMENTS.get("static", "0")) == 1)

def NoDeprecated(env):
   import sys
   if sys.platform == "darwin":
      # On recent OSX (10.9~) GLUT is deprecated
      env.Append(CPPFLAGS=" -Wno-deprecated-declarations")

prjs = [
  { "name"    : "gmath",
    "type"    : ("staticlib" if staticBuild else "sharedlib"),
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lib/*.cpp"),
    "defs"    : ["GMATH_STATIC" if staticBuild else "GMATH_EXPORTS"]
  },
  { "name"    : "gmath_tests",
    "type"    : "testprograms",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/test/*.cpp"),
    "libs"    : ["gmath"],
    "custom"  : [gl.Require, glut.Require, NoDeprecated],
    "defs"    : (["GMATH_STATIC"] if staticBuild else [])
  },
  { "name"    : "luagmath",
    "type"    : "dynamicmodule",
    "incdirs" : ["include"],
    "srcs"    : glob.glob("src/lua/*.cpp"),
    "libs"    : ["gmath"],
    "ext"     : ".so",
    "prefix"  : "lua",
    "custom"  : [lua.Require],
    "defs"    : (["GMATH_STATIC"] if staticBuild else [])
  }
]

env = excons.MakeBaseEnv()
excons.DeclareTargets(env, prjs)




