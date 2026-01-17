cmake_minimum_required(VERSION 4.1)

# This file is not used to compile the source, only used for reference in CLion

project(myprogram C)
include_directories( ./ )


add_executable(myprogram
        ./games/game0/maps/map0/spells/spells.c
        ./games/game0/maps/map0/widgets/widgets.c
        ./games/game0/maps/map0/drawfunctions/drawfunctions.c
        ./games/game0/maps/map0/mouse/mouse.c
        ./test/sizes_test.c
        ./test/hello_world.c
        ./test/bbStr_toI32_test.c
        ./test/old/bbList_testIterate.c
        ./test/old/bbList_test.c
        ./test/old/bbList_testInsert.c
        ./test/old/bbList_testSort.c
        ./test/old/automorphicNumbers.c
        ./test/old/bbConstants_test.c
        ./test/old/bbListList_map_test.c
        ./test/old/bbListList_test.c
        ./test/old/bbVPool_test.c
        ./test/old/bbList_testSortedInsert.c
        ./test/old/bbDumbServer_test.c
        ./test/old/bbVPool_printHeader_test.c
        ./test/old/dowhile_test.c
        ./test/old/bbList_testSplit.c
        ./test/old/bbTree_test.c
        ./test/old/bbRoundUp_test.c
        ./test/old/bbPrime_test.c
        ./test/old/bbDictionary_test.c
        ./test/old/bbList_pushpop.c
        ./test/old/bbList_testSortElement.c
        ./test/old/bbFloorDivision_test.c
        ./test/old/bbList_testRemove.c
        ./test/old/bbTerminal_test.c
        ./test/old/bbList_testMerge.c
        ./test/old/bbListList.c
        ./test/Incremental_test.c
        ./test/get_line_test.c
        ./engine/graphics/bbFonts.c
        ./engine/graphics/bbAnimation.c
        ./engine/graphics/bbComposition.c
        ./engine/graphics/bbSprites.c
        ./engine/graphics/bbTextures.c
        ./engine/graphics/bbColours.c
        ./engine/graphics/bbDrawfunctions.c
        "engine/core(old)/bbCore.c"
        "engine/core(old)/bbMessages.c"
        ./engine/geometry/bbCoordinates.c
        ./engine/geometry/bbViewportCoords.c
        ./engine/geometry/bbMesh.c
        ./engine/viewport/bbDrawables.c
        ./engine/viewport/bbMapIcons.c
        ./engine/viewport/bbUnits.c
        ./engine/viewport/bbViewport.c
        ./engine/dummyserver/bbDummyReceiver.c
        ./engine/dummyserver/bbDummySender.c
        ./engine/logic/bbDictionary.c
        ./engine/logic/bbTree.c
        ./engine/logic/bbLeanPool.c
        ./engine/logic/bbList_map.c
        ./engine/logic/bbBloatedPool.c
        ./engine/logic/bbVPool.c
        ./engine/logic/bbNestedList.c
        ./engine/logic/bbList_sort.c
        ./engine/logic/bbCircularBuffer.c
        ./engine/logic/bbList.c
        ./engine/logic/bbList_iterate.c
        ./engine/userinterface/bbInput.c
        ./engine/userinterface/bbSpells.c
        ./engine/userinterface/bbMouseFunctions.c
        ./engine/userinterface/bbSpell.c
        ./engine/userinterface/bbWidgetFunctions.c
        ./engine/userinterface/bbWidget.c
        ./engine/userinterface/bbMouse.c
        ./engine/avoidance/bbAvoidables.c
        engine/threadsafe/bbThreadedPool.c
        test/bbThreadedPool_test.c
        engine/threadsafe/bbThreadedQueue.c
        test/bbThreadedQueue_test.c
        test/bbServer_test.c
        engine/echo_server/bbServer.c
        test/pool_speed_test.c
        engine/network/bbNetwork.c
        engine/network/bbNetworkPacket.h
        test/bbNetwork_test.c
        test/old/bbNetwork_test2.c
        engine/network/bbNetworkTime.h
        engine/network/bbNetworkPacket.c
        test/bbNetworkPacket_test.c
        engine/network/bbNetworkTime.c
        engine/network/bbNetwork.h
        test/bbThreadedQueue_test2.c

)

