@echo off

echo Cleaning viewer library files
call:clean %cd%

echo Cleaning exercises
call:clean exercises/exercise1 ex1
call:clean exercises/exercise2 ex2
call:clean exercises/exercise3 ex3
call:clean exercises/exercises4-5 ex4-5

echo Cleaning demos
call:clean demos/convex_hull_2 convex_hull_2
call:clean demos/example example
call:clean demos/polygon polygon

echo Cleaning binaries
set parent=%cd%
cd bin
del *.exe /Q 2>NUL
del *.dll /Q 2>NUL
del *.lib /Q 2>NUL
del *.txt /Q 2>NUL
del *.pdb /Q 2>NUL
del *.exp /Q 2>NUL
cd %parent%

goto eof


:clean
set parent=%cd%
cd %~1
del *.sln /Q 2>NUL
del *.sdf /Q 2>NUL
del *.vcxproj* /Q 2>NUL
del *.pdb /Q 2>NUL
rmdir debug /S /Q 2>NUL
rmdir release /S /Q 2>NUL
cd %parent%

:eof
