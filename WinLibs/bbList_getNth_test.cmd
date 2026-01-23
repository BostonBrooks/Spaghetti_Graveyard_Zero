echo off
echo Look, a Tortoise:
echo [32m
echo:
echo   _____     ____
echo  /      \  ^|  o ^|
echo ^|        ^|/ ___\^|
echo ^|_________/
echo ^|_^|_^| ^|_^|_^|
echo /////////////////////////////////////////////////////////////
echo [0m
echo:
echo Attempting to compile:
SET PATH=C:\winlibs\mingw64\bin
gcc   -D SFML_STATIC -I ../^
       ../engine/logic/bbList_getNth.c^
       ../test/old/bbList_getNth_test.c^
       ../engine/logic/bbVPool.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbList.c^
      ^
  -lcsfml-system -lcsfml-graphics -lcsfml-window  -lcsfml-network -g -lm -w^
    -o ./test.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          test.exe)^
 ELSE (echo compile failed!)
