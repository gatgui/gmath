/*

Copyright (C) 2009, 2010  Gaetan Guidet

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
