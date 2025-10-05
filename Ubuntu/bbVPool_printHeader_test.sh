 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'

#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

if gcc    -I ../\
       ../test/bbVPool_printHeader_test.c\
       ../engine/logic/bbLeanPool.c\
       ../engine/logic/bbBloatedPool.c\
       ../engine/logic/bbVPool.c\
       \
  -o ./test.out;
then
    echo "Compile Succeeded:"
    ./test.out
else
    echo "Compile Failed!"
    #exit
fi
#done
