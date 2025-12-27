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
       ../engine/echo_server/bbServer.c^
      ^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w^
    -o ../games/game0/server.exe
IF %errorlevel% == 0 (    echo Compile Succeeded:
                          cd ../games/game0/
                          gdb ./server.exe)^
 ELSE (echo compile failed!)
