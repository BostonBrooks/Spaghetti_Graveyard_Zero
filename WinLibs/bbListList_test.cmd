SET PATH=C:\winlibs\mingw64\bin
gcc    -I ../^
       ../test/bbListList.c^
      ../engine/logic/bbList.c^
      ../engine/logic/bbList_sort.c^
      ../engine/logic/bbList_iterate.c^
      ../engine/logic/bbBloatedPool.c^
      ../engine/logic/bbLeanPool.c^
      ../engine/logic/bbVPool.c^
  -lcsfml-system -lcsfml-graphics -lcsfml-window -g -lm -w

gdb    ./a.exe