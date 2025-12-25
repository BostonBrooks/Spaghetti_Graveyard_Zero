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
       ../engine/viewport/bbViewport.c^
       ../engine/geometry/bbViewportCoords.c^
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
       ../engine/userinterface/bbWidget.c^
       ../engine/geometry/bbCoordinates.c^
       ../engine/userinterface/bbInput.c^
       ../engine/userinterface/bbWidgetFunctions.c^
       ../games/game0/maps/map0/widgets/widgets.c^
       ../games/game0/maps/map0/mouse/mouse.c^
       ../engine/userinterface/bbMouse.c^
       ../engine/userinterface/bbMouseFunctions.c^
       ../engine/graphics/bbFonts.c^
       ../engine/dummyserver/bbDummySender.c^
       ../engine/dummyserver/bbDummyReceiver.c^
       ../engine/userinterface/bbSpells.c^
       ../engine/userinterface/bbSpell.c^
       ../games/game0/maps/map0/spells/spells.c^
       ../engine/viewport/bbDrawables.c^
       ../engine/viewport/bbMapIcons.c^
       ../engine/avoidance/bbAvoidables.c^
       ../engine/viewport/bbUnits.c^
       ../engine/threadsafe/bbThreadedPool.c^
       ../engine/threadsafe/bbThreadedQueue.c^
       ../games/game0/maps/map0/drawfunctions/drawfunctions.c^
       ^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w^
    -o ../games/game0/game.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          cd ../games/game0/
                          gdb ./game.exe)^
 ELSE (echo compile failed!)
