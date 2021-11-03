/*
MIT License

Copyright (c) 2015 Gaetan Guidet

This file is part of gmath.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
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
         
         accessor();
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
         
         MapType::iterator mIt;
         MapType::iterator mEnd;
      };
      
      class GMATH_API const_accessor
      {
      public:
         const_accessor();
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
