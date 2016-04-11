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

Params::accessor::accessor(Params &p, const char *n)
{
   mIt = p.mParamMap.find(n);
   mEnd = p.mParamMap.end();
}

Params::accessor::accessor(const Params::accessor &rhs)
   : mIt(rhs.mIt), mEnd(rhs.mEnd)
{
}

Params::accessor& Params::accessor::operator=(const Params::accessor &rhs)
{
   mIt = rhs.mIt;
   mEnd = rhs.mEnd;
   return *this;
}

bool Params::accessor::operator==(const Params::accessor &rhs) const
{
   return (mIt == rhs.mIt);
}

bool Params::accessor::operator!=(const Params::accessor &rhs) const
{
   return (mIt != rhs.mIt);
}

bool Params::accessor::valid() const
{
   return (mIt != mEnd);
}

Params::ParamType Params::accessor::type() const
{
   return (mIt != mEnd ? mIt->second.type : Undefined);
}

const char* Params::accessor::name() const
{
   return (mIt != mEnd ? mIt->first : 0);
}

Params::accessor& Params::accessor::operator=(bool v)
{
   if (type() == Bool)
   {
      mIt->second.data.b = v;
   }
   return *this;
}

Params::accessor& Params::accessor::operator=(long v)
{
   if (type() == Int)
   {
      mIt->second.data.i = v;
   }
   return *this;
}

Params::accessor& Params::accessor::operator=(float v)
{
   if (type() == Float)
   {
      mIt->second.data.f = v;
   }
   return *this;
}

Params::accessor& Params::accessor::operator=(const char *v)
{
   if (type() == String)
   {
      mIt->second.data.s = v;
   }
   return *this;
}

Params::accessor::operator bool () const
{
   return (mIt != mEnd && mIt->second.type == Bool ? mIt->second.data.b : false);
}

Params::accessor::operator long () const
{
   return (mIt != mEnd && mIt->second.type == Int ? mIt->second.data.i : 0);
}

Params::accessor::operator float () const
{
   return (mIt != mEnd && mIt->second.type == Float ? mIt->second.data.f : 0.0f);
}

Params::accessor::operator const char* () const
{
   return (mIt != mEnd && mIt->second.type == String ? mIt->second.data.s : 0);
}

// ---

Params::const_accessor::const_accessor(const Params &p, const char *n)
{
   mIt = p.mParamMap.find(n);
   mEnd = p.mParamMap.end();
}

Params::const_accessor::const_accessor(const Params::accessor &rhs)
   : mIt(rhs.mIt), mEnd(rhs.mEnd)
{
}

Params::const_accessor::const_accessor(const Params::const_accessor &rhs)
   : mIt(rhs.mIt), mEnd(rhs.mEnd)
{
}

Params::const_accessor& Params::const_accessor::operator=(const Params::accessor &rhs)
{
   mIt = rhs.mIt;
   mEnd = rhs.mEnd;
   return *this;
}

Params::const_accessor& Params::const_accessor::operator=(const Params::const_accessor &rhs)
{
   mIt = rhs.mIt;
   mEnd = rhs.mEnd;
   return *this;
}

bool Params::const_accessor::operator==(const Params::accessor &rhs) const
{
   return (mIt == rhs.mIt);
}

bool Params::const_accessor::operator!=(const Params::accessor &rhs) const
{
   return (mIt != rhs.mIt);
}

bool Params::const_accessor::operator==(const Params::const_accessor &rhs) const
{
   return (mIt == rhs.mIt);
}

bool Params::const_accessor::operator!=(const Params::const_accessor &rhs) const
{
   return (mIt != rhs.mIt);
}

bool Params::const_accessor::valid() const
{
   return (mIt != mEnd);
}

Params::ParamType Params::const_accessor::type() const
{
   return (mIt != mEnd ? mIt->second.type : Undefined);
}

const char* Params::const_accessor::name() const
{
   return (mIt != mEnd ? mIt->first : 0);
}

Params::const_accessor::operator bool () const
{
   return (mIt != mEnd && mIt->second.type == Bool ? mIt->second.data.b : false);
}

Params::const_accessor::operator long () const
{
   return (mIt != mEnd && mIt->second.type == Int ? mIt->second.data.i : 0);
}

Params::const_accessor::operator float () const
{
   return (mIt != mEnd && mIt->second.type == Float ? mIt->second.data.f : 0.0f);
}

Params::const_accessor::operator const char* () const
{
   return (mIt != mEnd && mIt->second.type == String ? mIt->second.data.s : 0);
}

// ---

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
