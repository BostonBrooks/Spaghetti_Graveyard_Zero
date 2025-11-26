 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'

#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

if gcc    -I ../\
       ../test/bbOverlay_test.c\
       ../engine/viewport/bbOverlay.c\
       ../engine/logic/bbVPool.c\
       ../engine/logic/bbLeanPool.c\
       ../engine/logic/bbBloatedPool.c\
       ../engine/logic/bbListList.c\
      ../engine/logic/bbList.c\
      ../engine/logic/bbList_sort.c\
      ../engine/logic/bbList_iterate.c\
      ../engine/logic/bbList_map.c\
      ../engine/geometry/bbCoordinates.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w;
then
    echo "Compile Succeeded:"
    ./a.out
else
    echo "Compile Failed!"
    #exit
fi
#done