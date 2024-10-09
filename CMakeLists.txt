cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used

project(myprogram C)
include_directories( ./ )
add_executable(myprogram test/bbTerminal_test.c
        engine/logic/bbComplexPool.c
        engine/logic/bbFloorDivision.h
        engine/logic/bbPool.h
        engine/logic/bbPriorityQueue.h
        engine/logic/bbPriorityQueue.c
        engine/logic/bbArith.h
        engine/geometry/bbMesh.h
        engine/geometry/bbCoordinates.h
        engine/geometry/bbMesh.c
        engine/geometry/bbCoordinates.c)
