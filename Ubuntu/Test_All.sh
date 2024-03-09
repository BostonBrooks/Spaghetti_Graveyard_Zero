 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'

#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

 if gcc\
   -I ../ \
  ../test/main.c\
  ../source/bbGame.c\
  ../source/bbGraphicsSettings.c\
  ../source/bbMap.c\
  ../source/bbTextures.c\
  ../source/bbSprites.c\
  ../source/bbAnimation.c\
  ../source/bbSkins.c\
  ../source/bbElevations.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w;
  then
    echo "Compile Succeeded:"
    ./a.out
  else
    echo "Compile Failed!"
 #   exit
  fi

#done