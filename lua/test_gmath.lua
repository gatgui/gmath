-- Copyright (C) 2009  Gaetan Guidet
-- 
-- This file is part of gmath.
-- 
-- gmath is free software; you can redistribute it and/or modify it
-- under the terms of the GNU Lesser General Public License as published by
-- the Free Software Foundation; either version 2.1 of the License, or (at
-- your option) any later version.
-- 
-- gmath is distributed in the hope that it will be useful, but
-- WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
-- Lesser General Public License for more details.
-- 
-- You should have received a copy of the GNU Lesser General Public
-- License along with this library; if not, write to the Free Software
-- Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301,
-- USA.

--package.path = package.path..";./lua/?.lua;./lua/?/init.lua"
--package.cpath = package.cpath..";./?.so;./lua/?.so;"

require "luagmath"

v0 = gmath.Vector2.new(2, 2)
v1 = gmath.Vector2.new(2, 2);

if (v0 == v1) then
  print("Vector are equal")
else
  print("Vector are different")
end

v0.x = 0.33
v0.y = -1.7564
v0[1] = 10.4
v0[2] = 4.5
print("v0.x = "..tostring(v0[1]))
print("v0.y = "..tostring(v0[2]))
v0[1] = -9.9
print("v0.x = "..tostring(v0[1]))

 
if (v0 == v1) then
  print("Vector are equal")
else
  print("Vector are different")
end

print("#v0 = "..tostring(#v0))
print("v0 = "..tostring(v0))
print("v1 = "..tostring(v1))
print("len(v0) = "..tostring(v0.length))
print("ortho(v0) = "..tostring(v0:ortho()))
print("dot(v0, v1) = "..tostring(v0:dot(v1)))
print("len(v0)^2 = "..tostring(v0.squaredLength))
print("floor(v0, v1) = "..tostring(v0:floor(v1)))
print("ceil(v0, v1) = "..tostring(v0:ceil(v1)))


v0.x = 0.5
v0.y = -1.5
v1.x = 0.25
v1.y = 0.75
print("=== test operators")
print(v0)
print(v1)
print("v0 + v1 = "..tostring(v0+v1)); collectgarbage();
print("v0 - v1 = "..tostring(v0-v1)); collectgarbage();
print("v0 * v1 = "..tostring(v0*v1)); collectgarbage();
print("v0 / v1 = "..tostring(v0/v1)); collectgarbage();
print("v0 * 2 = "..tostring(v0*2)); collectgarbage();
print("2 * v0 = "..tostring(2*v0)); collectgarbage();
print("v0 / 2 = "..tostring(v0/2)); collectgarbage();
print("v0 > v1 ? "..tostring(v0>v1))
print("v0 >= v1 ? "..tostring(v0>=v1))
print("v0 < v1 ? "..tostring(v0<v1))
print("v0 <= v1 ? "..tostring(v0<=v1))

v2 = gmath.Vector2.new({0, -1})
print("v2 = Vector2({0, -1}) = "..tostring(v2))

v2 = gmath.Vector2.new(v0)
print("v2 = Vector2({v0) = "..tostring(v2))

print("ZERO = "..tostring(gmath.Vector2.ZERO))
print("UNIT_X = "..tostring(gmath.Vector2.UNIT_X))
print("UNIT_Y = "..tostring(gmath.Vector2.UNIT_Y))

-- This does not work anymore
--gmath.Vector2.ZERO = v0

tmp = gmath.Vector2.ZERO

-- This doesn't work any more
--tmp2 = gmath.Vector2.new(-1, -1)
--tmp:floor(tmp2)
--print("ZERO = "..tostring(gmath.Vector2.ZERO))

-- And this also
--tmp.x = -4
--print("ZERO = "..tostring(gmath.Vector2.ZERO))



