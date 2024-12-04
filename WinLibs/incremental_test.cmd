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
gcc    -I ../^
       ../test/Incremental_test.c^
       ../engine/graphics/bbTextures.c^
       ../engine/graphics/bbSprites.c^
       ../engine/graphics/bbDrawfunctions.c^
       ../engine/graphics/bbAnimation.c^
       ../engine/logic/bbDictionary.c^
       ../engine/logic/bbTree.c^
       ../engine/logic/bbVPool.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbLeanPool.c^
       ../engine/widgets/bbWidget.c^
       ../engine/geometry/bbCoordinates.c^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w^
    -o ../games/game0/game.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          cd ../games/game0/
                          gdb ./game.exe)^
 ELSE (echo compile failed!)
