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

#ifndef __gmath_params_h__
#define __gmath_params_h__

#include <gmath/config.h>
#include <map>

namespace gmath
{
   class GMATH_API Params
   {
   public:
      enum ParamType
      {
         Undefined = -1,
         Bool,
         Int,
         Float,
         String
      };
      
      struct Param
      {
         ParamType type;
         union
         {
            bool b;
            long i;
            float f;
            const char *s;
         } data;
      };
      
      struct LessThanStr
      {
         inline bool operator()(const char *s0, const char *s1) const
         {
            return (strcmp(s0, s1) < 0);
         }
      };
      
      typedef std::map<const char*, Param, LessThanStr> MapType;
      
      class const_accessor;
      
      class GMATH_API accessor
      {
      public:
         friend class const_accessor;
         
         accessor(Params &p, const char *n);
         accessor(const accessor &rhs);
         
         accessor& operator=(const accessor &rhs);
         bool operator==(const accessor &rhs) const;
         bool operator!=(const accessor &rhs) const;
         
         bool valid() const;
         ParamType type() const;
         const char* name() const;
         
         accessor& operator=(bool v);
         accessor& operator=(long v);
         accessor& operator=(float v);
         accessor& operator=(const char *v);
         
         operator bool () const;
         operator long () const;
         operator float () const;
         operator const char* () const;
      
      private:
         accessor();
         
         MapType::iterator mIt;
         MapType::iterator mEnd;
      };
      
      class GMATH_API const_accessor
      {
      public:
         const_accessor(const Params &p, const char *n);
         const_accessor(const accessor &rhs);
         const_accessor(const const_accessor &rhs);
         
         const_accessor& operator=(const accessor &rhs);
         const_accessor& operator=(const const_accessor &rhs);
         bool operator==(const accessor &rhs) const;
         bool operator==(const const_accessor &rhs) const;
         bool operator!=(const accessor &rhs) const;
         bool operator!=(const const_accessor &rhs) const;
         
         bool valid() const;
         ParamType type() const;
         const char* name() const;
         
         operator bool () const;
         operator long () const;
         operator float () const;
         operator const char* () const;
      
      private:
         const_accessor();
         
         MapType::const_iterator mIt;
         MapType::const_iterator mEnd;
      };
      
      friend class accessor;
      friend class const_accessor;
      
   public:
      Params();
      Params(const Params &rhs);
      
      Params& operator=(const Params &rhs);
      
      void set(const char *name, bool val);
      void set(const char *name, long val);
      void set(const char *name, float val);
      void set(const char *name, const char *val);
      
      bool get(const char *name, bool &val) const;
      bool get(const char *name, long &val) const;
      bool get(const char *name, float &val) const;
      bool get(const char *name, const char* &val) const;
      
      bool has(const char *name, ParamType type=Undefined) const;
      bool remove(const char *name);
      void clear();
      size_t size() const;
      const char* name(size_t i) const;
      ParamType type(size_t i) const;
      
   private:
      
      MapType mParamMap;
   };
}

#endif
