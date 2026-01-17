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
       ../test/bbNetworkTime_test.c^
       ../engine/network/bbNetwork.c^
       ../engine/network/bbNetworkPacket.c^
       ../engine/network/bbNetworkTime.c^
       ../engine/logic/bbLeanPool.c^
       ../engine/logic/bbBloatedPool.c^
       ../engine/logic/bbVPool.c^
       ../engine/threadsafe/bbThreadedPool.c^
       ../engine/threadsafe/bbThreadedQueue.c^
       ../engine/threadsafe/bbThreadedQueue_search.c^
      ^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w^
    -o ./test.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          gdb ./test.exe)^
 ELSE (echo compile failed!)
