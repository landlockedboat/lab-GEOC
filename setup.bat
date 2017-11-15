@echo off

echo Building the viewer library
qmake -tp vc
devenv geoc.vcxproj /Build Release

echo Building exercises
call:build exercises/exercise1 ex1
call:build exercises/exercise2 ex2
call:build exercises/exercise3 ex3
call:build exercises/exercises4-5 ex4-5

echo Building demos
call:build demos/convex_hull_2 convex_hull_2
call:build demos/example example
call:build demos/polygon polygon

goto eof

:build
set parent=%cd%
cd %~1
echo Building %~1
qmake -tp vc
devenv %~2.vcxproj /Build Release
cd %parent%

:eof
