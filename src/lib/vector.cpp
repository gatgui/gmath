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

