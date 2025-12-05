echo Attempting to compile:
SET PATH=C:\winlibs\mingw64\bin
gcc   -D SFML_STATIC -I ../^
    -I C:\winlibs\mingw64\include\SFML\include^
    ./client.c^
    -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w^
    -o client.exe

gcc   -D SFML_STATIC -I ../^
    -I C:\winlibs\mingw64\include\SFML\include^
    ./server.c^
    -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w^
    -o server.exe
