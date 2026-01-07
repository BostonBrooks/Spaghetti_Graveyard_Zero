 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'




 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"



if gcc   -fsanitize=address -fno-omit-frame-pointer -g -I ../\
       ../engine/server/bbServer.c\
       ../engine/network/bbNetworkPacket.c\
       ../engine/threadsafe/bbThreadedPool.c\
       ../engine/threadsafe/bbThreadedQueue.c\
       ../engine/logic/bbVPool.c\
       ../engine/logic/bbBloatedPool.c\
       ../engine/logic/bbLeanPool.c\
       \
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -lm -w\
  -o ./server.out;
then
    echo "Compile Succeeded:"
    echo "Opening Port 1701"
    sudo ufw allow 1701
    
    ./server.out
else
    echo "Compile Failed!"
    #exit
fi
#done
