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
       ../games/game0/maps/map0/spawner.c^
       ../test/incremental_test.c^
       ../engine/core/bbMoveable.c^
       ../engine/userinterface/bbUIApp.c^
       ../engine/viewport/bbViewportApp.c^
       ../engine/core/bbCore.c^
       ../engine/core/bbCoreInputs.c^
       ../engine/core/bbInstruction.c^
       ../engine/core/bbAgent.c^
       ../engine/avoidance/bbAvoidables.c^
       ../engine/geometry/bbCoordinates.c^
       ../engine/geometry/bbViewportCoords.c^
       ../engine/graphics/bbAnimation.c^
       ../engine/graphics/bbColours.c^
       ../engine/graphics/bbComposition.c^
       ../engine/graphics/bbDrawfunctions.c^
       ../engine/graphics/bbFonts.c^
       ../engine/graphics/bbSprites.c^
       ../engine/graphics/bbTextures.c^
       ../engine/graphics/bbGraphicsApp.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbDictionary.c^
       ../engine/logic/bbLeanPool.c^
       ../engine/logic/bbList_iterate.c^
       ../engine/logic/bbList_map.c^
       ../engine/logic/bbList_sort.c^
       ../engine/logic/bbList.c^
       ../engine/logic/bbNestedList.c^
       ../engine/logic/bbTree.c^
       ../engine/logic/bbVPool.c^
       ../engine/network/bbNetworkPacket.c^
       ../engine/network/bbNetwork.c^
       ../engine/network/bbNetworkTime.c^
       ../engine/network/bbNetworkApp.c^
       ../engine/threadsafe/bbThreadedPool.c^
       ../engine/threadsafe/bbThreadedQueue_search.c^
       ../engine/threadsafe/bbThreadedQueue.c^
       ../engine/userinterface/bbInput.c^
       ../engine/userinterface/bbMouse.c^
       ../engine/userinterface/bbMouseFunctions.c^
       ../engine/userinterface/bbSpell.c^
       ../engine/userinterface/bbSpells.c^
       ../engine/userinterface/bbWidget.c^
       ../engine/userinterface/bbWidgetFunctions.c^
       ../engine/viewport/bbDrawables.c^
       ../engine/viewport/bbMapIcons.c^
       ../engine/viewport/bbUnits.c^
       ../engine/viewport/bbViewport.c^
       ../games/game0/maps/map0/drawfunctions/drawfunctions.c^
       ../games/game0/maps/map0/mouse/mouse.c^
       ../games/game0/maps/map0/spells/spells.c^
       ../games/game0/maps/map0/widgets/widgets.c^
       ../games/game0/maps/map0/agents/agents.c^
       ../engine/logic/bbList_getNth.c^
       ^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w^
    -o ../games/game0/game.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          cd ../games/game0/
                          gdb ./game.exe)^
 ELSE (echo compile failed!)
