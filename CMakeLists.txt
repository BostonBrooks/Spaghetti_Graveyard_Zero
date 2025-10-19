cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used

project(myprogram C)
include_directories( ./ )
add_executable(myprogram
        test/bbList_testSortElement.c
        engine/logic/bbArith.h
        engine/logic/bbBloatedPool.c
        engine/logic/bbBloatedPool.h
        engine/logic/bbDictionary.c
        engine/logic/bbDictionary.h
        engine/logic/bbLeanPool.c
        engine/logic/bbLeanPool.h
        engine/logic/bbList.c
        engine/logic/bbScatter.h
        engine/logic/bbTree.c
        engine/logic/bbTree.h
        engine/logic/bbVPool.c
        test/bbConstants_test.c
        test/bbFloorDivision_test.c
        test/bbList_test.c
        test/bbList_testInsert.c
        test/bbList_testMerge.c
        test/bbList_testSort.c
        test/bbList_testSortedInsert.c
        test/bbList_testSplit.c
        test/bbRoundUp_test.c
        test/bbTerminal_test.c
        test/bbTree_test.c
        test/bbVPool_test.c
        test/dowhile_test.c
        engine/logic/bbList_iterate.c
        test/bbList_testIterate.c
        engine/graphics/bbTextures.h
        engine/graphics/bbTextures.c
        engine/logic/bbPrime.h
        test/bbPrime_test.c
        engine/graphics/bbSprites.c
        engine/graphics/bbAnimation.h
        engine/graphics/bbAnimation.c
        engine/graphics/bbDrawfunctions.h
        engine/graphics/bbComposition.h
        engine/graphics/bbComposition.c
        engine/widgets/bbWidget.h
        engine/graphics/bbGraphics.h
        engine/graphics/bbDrawfunctions.c
        engine/geometry/bbCoordinates.h
        engine/geometry/bbCoordinates.c
        test/Incremental_test.c
        engine/logic/bbTree.c
        engine/logic/bbList_map.c
        engine/widgets/bbWidget.c
        engine/user_input/bbInput.h
        engine/user_input/bbInput.c
        engine/2point5D/bbViewport.h
        engine/2point5D/bbViewport.c
        engine/2point5D/bbOverlays.h
        engine/2point5D/bbOverlays.c
        engine/graphics/bbColours.c
        test/bbListList.c
        test/bbList_pushpop.c
        engine/logic/bbNestedList.h
        engine/logic/bbNestedList.c
        test/bbListList_test.c
        test/bbListList_map_test.c
        engine/2point5D/bbViewportCoords.h
        test/bbOverlay_test.c
        test/automorphicNumbers.c
        games/game0/maps/map0/widgets/nullfunctions.h
        engine/widgets/bbWidgetFunctions.c
        games/game0/maps/map0/widgets/sphere.h
        engine/user_input/bbMouse.c
        games/game0/maps/map0/widgets/button.h
        engine/user_input/bbMouseFunctions.c
        engine/2point5D/bbViewportCoords.c)
