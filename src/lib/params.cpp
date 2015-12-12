/*

Copyright (C) 2015  Gaetan Guidet

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

#include <gmath/params.h>

namespace gmath
{

Params::Params()
{
}

Params::Params(const Params &rhs)
   : mParamMap(rhs.mParamMap)
{
}

Params& Params::operator=(const Params &rhs)
{
   if (this != &rhs)
   {
      mParamMap = rhs.mParamMap;
   }
   return *this;
}

void Params::set(const char *name, bool val)
{
   Param &param = mParamMap[name];
   param.type = Bool;
   param.data.b = val;
}

void Params::set(const char *name, long val)
{
   Param &param = mParamMap[name];
   param.type = Int;
   param.data.i = val;
}

void Params::set(const char *name, float val)
{
   Param &param = mParamMap[name];
   param.type = Float;
   param.data.f = val;
}

void Params::set(const char *name, const char *val)
{
   Param &param = mParamMap[name];
   param.type = String;
   param.data.s = val;
}

bool Params::get(const char *name, bool &val) const
{
   MapType::const_iterator it = mParamMap.find(name);
   if (it == mParamMap.end() || it->second.type != Bool)
   {
      return false;
   }
   else
   {
      val = it->second.data.b;
      return true;
   }
}

bool Params::get(const char *name, long &val) const
{
   MapType::const_iterator it = mParamMap.find(name);
   if (it == mParamMap.end() || it->second.type != Int)
   {
      return false;
   }
   else
   {
      val = it->second.data.i;
      return true;
   }
}

bool Params::get(const char *name, float &val) const
{
   MapType::const_iterator it = mParamMap.find(name);
   if (it == mParamMap.end() || it->second.type != Float)
   {
      return false;
   }
   else
   {
      val = it->second.data.f;
      return true;
   }
}

bool Params::get(const char *name, const char* &val) const
{
   MapType::const_iterator it = mParamMap.find(name);
   if (it == mParamMap.end() || it->second.type != String)
   {
      return false;
   }
   else
   {
      val = it->second.data.s;
      return true;
   }
}

bool Params::has(const char *name, Params::ParamType type) const
{
   MapType::const_iterator it = mParamMap.find(name);
   return (it != mParamMap.end() && (type == Undefined || it->second.type == type));
}

bool Params::remove(const char *name)
{
   MapType::iterator it = mParamMap.find(name);
   if (it != mParamMap.end())
   {
      mParamMap.erase(it);
      return true;
   }
   else
   {
      return false;
   }
}

void Params::clear()
{
   return mParamMap.clear();
}

size_t Params::size() const
{
   return mParamMap.size();
}

const char* Params::name(size_t i) const
{
   MapType::const_iterator it = mParamMap.begin();
   for (size_t j=0; j<i; ++j, ++it);
   return (it != mParamMap.end() ? it->first : "");
}

Params::ParamType Params::type(size_t i) const
{
   MapType::const_iterator it = mParamMap.begin();
   for (size_t j=0; j<i; ++j, ++it);
   return (it != mParamMap.end() ? it->second.type : Undefined);
}

}
