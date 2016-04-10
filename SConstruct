import excons
import glob
import excons.tools
from excons.tools import lua, gl, glut

staticBuild = (excons.GetArgument("static", "0", int) == 1)

def NoDeprecated(env):
   import sys
   if sys.platform == "darwin":
      # On recent OSX (10.9~) GLUT is deprecated
      env.Append(CPPFLAGS=" -Wno-deprecated-declarations")

def RequireGmath(subdir=None):
  if subdir and type(subdir) in (str, unicode):
    if not (subdir.endswith("/") or subdir.endswith("\\")):
      subdir += "/"
  else:
    subdir = ""

  def _Require(env):
    env.Append(CPPPATH=[subdir+"include"])
    # Don't need to set LIBPATH, library output directory is automatically added by excons
    env.Append(LIBS=["gmath"])
    if staticBuild:
      env.Append(CPPDEFINES=["GMATH_STATIC"])

  return _Require

Export("RequireGmath")

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

Default(["gmath"])
