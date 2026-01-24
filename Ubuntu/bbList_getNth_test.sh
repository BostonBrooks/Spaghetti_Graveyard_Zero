 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'




 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"


if gcc   -fsanitize=address -fno-omit-frame-pointer -g -I ../\
         ../engine/logic/bbList_getNth.c\
         ../test/bbList_getNth_test.c\
         ../engine/logic/bbVPool.c\
         ../engine/logic/bbBloatedPool.c\
         ../engine/logic/bbLeanPool.c\
         ../engine/logic/bbList.c\
         ../engine/logic/bbList_sort.c\
         \
  -lcsfml-system -lcsfml-graphics -lcsfml-window -lcsfml-network -lm -w\
  -o ./test.out;
then
    echo "Compile Succeeded:"
    gdb ./test.out
else
    echo "Compile Failed!"
    #exit
fi
#done
