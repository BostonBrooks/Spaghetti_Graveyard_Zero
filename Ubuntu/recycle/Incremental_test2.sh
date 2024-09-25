 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'

#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

 if gcc\
   -I ../ \
  ../test/Incremental_test2.c\
  ../source/bbGame.c\
  ../source/bbMap.c\
  ../source/bbDictionary.c\
  ../source/bbTextures.c\
  ../source/bbSprites.c\
  ../source/bbAnimation.c\
  ../source/bbWidget.c\
  ../source/bbGeometry.c\
  ../source/bbPool.c\
  ../source/bbTree.c\
  ../source/bbDispatch.c\
  ../source/bbMouse.c\
  ../source/bbFonts.c\
  ../source/bbCharacter.c\
  ../source/bbList.c\
  ../source/bbWidgetTimer.c\
  ../source/bbGraphicsSettings.c\
  \
  ../games/game/maps/demo/widgets/widgets.c\
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w;
  then
    echo "Compile Succeeded:"
    ./a.out
  else
    echo "Compile Failed!"
 #   exit
  fi

#done
