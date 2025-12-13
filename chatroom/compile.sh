echo Attempting to compile:
gcc    -I ../\
       ../chatroom/client.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w\
  -o client.out

gcc    -I ../\
       ../chatroom/server.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w\
  -o server.out
