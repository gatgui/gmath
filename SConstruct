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

def RequireGmath(env):
  # Don't need to set CPPPATH, headers are now installed in output directory
  # Don't need to set LIBPATH, library output directory is automatically added by excons
  env.Append(LIBS=["gmath"])
  if staticBuild:
    env.Append(CPPDEFINES=["GMATH_STATIC"])

Export("RequireGmath")


prjs = [
  { "name"         : "gmath",
    "type"         : ("staticlib" if staticBuild else "sharedlib"),
    "version"      : "0.2.1",
    "soname"       : "libgmath.so.0",
    "install_name" : "libgmath.0.dylib",
    "srcs"         : glob.glob("src/lib/*.cpp"),
    "install"      : {"include": ["include/gmath"]},
    "defs"         : ["GMATH_STATIC" if staticBuild else "GMATH_EXPORTS"]
  },
  { "name"    : "gmath_tests",
    "type"    : "testprograms",
    "srcs"    : glob.glob("src/test/*.cpp"),
    "custom"  : [RequireGmath, gl.Require, glut.Require, NoDeprecated]
  },
  { "name"    : "gmath_tools",
    "type"    : "testprograms",
    "srcs"    : glob.glob("src/bin/*.cpp"),
    "custom"  : [RequireGmath, gl.Require, glut.Require, NoDeprecated]
  },
  { "name"    : "luagmath",
    "type"    : "dynamicmodule",
    "srcs"    : glob.glob("src/lua/*.cpp"),
    "ext"     : ".so",
    "prefix"  : "lua",
    "custom"  : [lua.Require, RequireGmath]
  }
]

env = excons.MakeBaseEnv()
excons.DeclareTargets(env, prjs)

Default(["gmath"])
