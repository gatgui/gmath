# MIT License
#
# Copyright (c) 2009 Gaetan Guidet
#
# This file is part of gmath.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

import excons
import glob
import excons.tools
from excons.tools import lua
from excons.tools import gl
from excons.tools import glut
import SCons.Script

# pylint: disable=bad-indentation,no-member


env = excons.MakeBaseEnv()

staticBuild = (excons.GetArgument("static", "0", int) == 1)

def NoDeprecated(env): # pylint: disable=redefined-outer-name
   import sys
   if sys.platform == "darwin":
      # On recent OSX (10.9~) GLUT is deprecated
      env.Append(CPPFLAGS=" -Wno-deprecated-declarations")

def RequireGmath(env): # pylint: disable=redefined-outer-name
  # Don't need to set CPPPATH, headers are now installed in output directory
  # Don't need to set LIBPATH, library output directory is automatically added by excons
  env.Append(LIBS=["gmath"])
  if staticBuild:
    env.Append(CPPDEFINES=["GMATH_STATIC"])

SCons.Script.Export("RequireGmath")


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
    "custom"  : [RequireGmath, NoDeprecated]
  },
  { "name"    : "luagmath",
    "type"    : "dynamicmodule",
    "srcs"    : glob.glob("src/lua/*.cpp"),
    "ext"     : ".so",
    "prefix"  : "lua",
    "custom"  : [lua.Require, RequireGmath]
  }
]

excons.DeclareTargets(env, prjs)

SCons.Script.Default(["gmath"])
