/*
MIT License

Copyright (c) 2009 Gaetan Guidet

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

#include <gmath/curve.h>


namespace gmath {

size_t Curve::InvalidIndex = size_t(-1);

Curve::Curve()
  : mPreInf(Curve::IF_CONSTANT), mPostInf(Curve::IF_CONSTANT) {
}

Curve::Curve(const Curve &rhs)
  : mPreInf(rhs.mPreInf), mPostInf(rhs.mPostInf) {
}

Curve::~Curve() {
}

Curve& Curve::operator=(const Curve &rhs) {
  if (this != &rhs) {
    mPreInf = rhs.mPreInf;
    mPostInf = rhs.mPostInf;
  }
  return *this;
}

void Curve::setPreInfinity(Curve::Infinity it) {
  mPreInf = it;
}

void Curve::setPostInfinity(Curve::Infinity it) {
  mPostInf = it;
}

Curve::Infinity Curve::getPreInfinity() const {
  return mPreInf;
}

Curve::Infinity Curve::getPostInfinity() const {
  return mPostInf;
}

}
