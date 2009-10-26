/*

Copyright (C) 2009  Gaetan Guidet

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

#include <gmath/vector.h>

namespace gmath {

  const Vector2 Vector2::ZERO = Vector2(0,0);
  const Vector2 Vector2::UNIT_X = Vector2(1,0);
  const Vector2 Vector2::UNIT_Y = Vector2(0,1);

  // ---

  const Vector3 Vector3::ZERO = Vector3(0,0,0);
  const Vector3 Vector3::UNIT_X = Vector3(1,0,0);
  const Vector3 Vector3::UNIT_Y = Vector3(0,1,0);
  const Vector3 Vector3::UNIT_Z = Vector3(0,0,1);
  const Vector3 Vector3::NEG_UNIT_X = Vector3(-1,0,0);
  const Vector3 Vector3::NEG_UNIT_Y = Vector3(0,-1,0);
  const Vector3 Vector3::NEG_UNIT_Z = Vector3(0,0,-1);
  const Vector3 Vector3::UNIT_SCALE = Vector3(1,1,1);

  // ---

  const Vector4 Vector4::ZERO = Vector4(0,0,0,0);

}

