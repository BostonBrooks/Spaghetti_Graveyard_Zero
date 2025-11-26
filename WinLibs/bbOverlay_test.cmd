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
       ../test/bbOverlay_test.c^
       ../engine/viewport/bbOverlays.c^
       ../engine/logic/bbVPool.c^
       ../engine/logic/bbLeanPool.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbNestedList.c^
      ../engine/logic/bbList.c^
      ../engine/logic/bbList_sort.c^
      ../engine/logic/bbList_iterate.c^
      ../engine/logic/bbList_map.c^
      ../engine/geometry/bbCoordinates.c^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w

gdb    ./a.exe
