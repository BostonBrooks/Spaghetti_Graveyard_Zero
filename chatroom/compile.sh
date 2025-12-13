echo Attempting to compile:
gcc    -I ../\
       ../chatroom/client.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w\
  -o client.out

gcc    -I ../\
       ../chatroom/server.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w\
  -o server.out
  
  gcc    -I ../\
       ../chatroom/get_IPAddress_test.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -g -lm -w\
  -o test.out

echo Opening port 1701

sudo ufw allow 1701