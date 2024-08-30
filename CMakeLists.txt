cmake_minimum_required(VERSION 2.6.0)

# here we specify that the project is C language only, so the default
# C compiler on the system will be used

project(myprogram C)
include_directories( ./ )
add_executable(myprogram test/bbTerminal_test.c
        engine/logic/bbFastPool.h
        engine/logic/bbFastPool.c
        engine/logic/bbDeque.h
        engine/logic/bbDeque.c
        engine/logic/bbFloorDivision.h
        engine/logic/bbSlowPool.h
        engine/logic/bbSlowPool.c
        engine/logic/bbRoundUp.h)
