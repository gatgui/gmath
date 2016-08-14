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
  { "name"         : "gmath",
    "type"         : ("staticlib" if staticBuild else "sharedlib"),
    "version"      : "0.2.0",
    "soname"       : "libgmath.so.0",
    "install_name" : "libgmath.0.dylib",
    "incdirs"      : ["include"],
    "srcs"         : glob.glob("src/lib/*.cpp"),
    "install"      : {"include": ["include/gmath"]},
    "defs"         : ["GMATH_STATIC" if staticBuild else "GMATH_EXPORTS"]
  },
  { "name"    : "gmath_tests",
    "type"    : "testprograms",
    "srcs"    : glob.glob("src/test/*.cpp"),
    "custom"  : [RequireGmath(), gl.Require, glut.Require, NoDeprecated]
  },
  { "name"    : "luagmath",
    "type"    : "dynamicmodule",
    "srcs"    : glob.glob("src/lua/*.cpp"),
    "ext"     : ".so",
    "prefix"  : "lua",
    "custom"  : [lua.Require, RequireGmath()]
  }
]

env = excons.MakeBaseEnv()
excons.DeclareTargets(env, prjs)

Default(["gmath"])
