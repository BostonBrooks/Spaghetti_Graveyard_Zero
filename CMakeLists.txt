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
        engine/logic/bbPriorityQueue.c
        engine/logic/bbPriorityQueue.h
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
        test/bbPrime_test.c)
