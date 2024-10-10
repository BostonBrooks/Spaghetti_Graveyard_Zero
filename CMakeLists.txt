cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used

project(myprogram C)
include_directories( ./ )
add_executable(myprogram test/bbTerminal_test.c
        engine/logic/bbComplexPool.c
        engine/logic/bbFloorDivision.h
        engine/logic/bbScatter.h
        engine/logic/bbDictionary.h
        engine/logic/bbDictionary.c
        engine/logic/bbPriorityQueue.c
        engine/logic/bbPriorityQueue.h
        engine/includes/csfml.h
        engine/includes/game0.h
        engine/graphics/bbAnimation.h
        engine/graphics/bbComposition.h
        engine/graphics/bbDrawable.h
        engine/graphics/bbSprites.h
        engine/graphics/bbTextures.h
        engine/graphics/bbViewport.h
        engine/geometry/bbCoordinates.c
        engine/geometry/bbCoordinates.h
        engine/geometry/bbMesh.c
        engine/geometry/bbMesh.h)
