 #!/bin/bash

BGreen='\033[1;32m'
Color_Off='\033[0m'

#while [ 1 == 1 ]
#do

 echo -e "Look, a Tortoise:\n${BGreen}\n       _____     ____\n     /      \  |  o |\n    |        |/ ___\| \n    |_________/     \n    |_|_| |_|_|\n//////////////////////////////////////////////////////////////${Color_Off}\n\nAttempting to compile:\n"

if gcc    -I ../\
       ../test/Incremental_test.c\
       ../engine/viewport/bbViewport.c\
       ../engine/geometry/bbViewportCoords.c\
       ../engine/graphics/bbTextures.c\
       ../engine/graphics/bbSprites.c\
       ../engine/graphics/bbDrawfunctions.c\
       ../engine/graphics/bbAnimation.c\
       ../engine/graphics/bbComposition.c\
       ../engine/graphics/bbColours.c\
       ../engine/logic/bbDictionary.c\
       ../engine/logic/bbTree.c\
       ../engine/logic/bbVPool.c\
       ../engine/logic/bbBloatedPool.c\
       ../engine/logic/bbLeanPool.c\
       ../engine/logic/bbList.c\
       ../engine/logic/bbList_iterate.c\
       ../engine/logic/bbList_map.c\
       ../engine/logic/bbList_sort.c\
       ../engine/logic/bbNestedList.c\
       ../engine/widgets/bbWidget.c\
       ../engine/geometry/bbCoordinates.c\
       ../engine/userinterface/bbInput.c\
       ../engine/widgets/bbWidgetFunctions.c\
       ../games/game0/maps/map0/widgets/widgets.c\
       ../games/game0/maps/map0/mouse/mouse.c\
       ../engine/userinterface/bbMouse.c\
       ../engine/userinterface/bbMouseFunctions.c\
       ../engine/graphics/bbFonts.c\
       ../engine/dummyserver/bbDummySender.c\
       ../engine/dummyserver/bbDummyReceiver.c\
       ../engine/userinterface/bbSpells.c\
       ../engine/userinterface/bbSpell.c\
       ../games/game0/maps/map0/spells/spells.c\
       ../engine/viewport/bbDrawables.c\
       \
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w\
  -o ../games/game0/game.out;
then
    echo "Compile Succeeded:"
    cd ../games/game0/
    ./game.out
else
    echo "Compile Failed!"
    #exit
fi
#done
