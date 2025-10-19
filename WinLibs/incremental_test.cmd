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
       ../test/Incremental_test.c^
       ../engine/2point5D/bbViewport.c^
       ../engine/2point5D/bbOverlays.c^
       ../engine/2point5D/bbViewportCoords.c^
       ../engine/graphics/bbTextures.c^
       ../engine/graphics/bbSprites.c^
       ../engine/graphics/bbDrawfunctions.c^
       ../engine/graphics/bbAnimation.c^
       ../engine/graphics/bbComposition.c^
       ../engine/graphics/bbColours.c^
       ../engine/logic/bbDictionary.c^
       ../engine/logic/bbTree.c^
       ../engine/logic/bbVPool.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbLeanPool.c^
       ../engine/logic/bbList.c^
       ../engine/logic/bbList_iterate.c^
       ../engine/logic/bbList_map.c^
       ../engine/logic/bbList_sort.c^
       ../engine/logic/bbNestedList.c^
       ../engine/widgets/bbWidget.c^
       ../engine/geometry/bbCoordinates.c^
       ../engine/user_input/bbInput.c^
       ../engine/widgets/bbWidgetFunctions.c^
       ../games/game0/maps/map0/widgets/widgets.c^
       ../games/game0/maps/map0/mouse/mouse.c^
       ../engine/user_input/bbMouse.c^
       ../engine/user_input/bbMouseFunctions.c^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w^
    -o ../games/game0/game.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          cd ../games/game0/
                          gdb -ex=r ./game.exe)^
 ELSE (echo compile failed!)
