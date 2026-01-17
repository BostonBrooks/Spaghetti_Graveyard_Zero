SET PATH=C:\winlibs\mingw64\bin
gcc    -g -I ../^
      ../test/bbList_testRemove.c^
      ../engine/logic/bbList.c^
      ../engine/logic/bbBloatedPool.c^
      ../engine/logic/bbLeanPool.c^
      ../engine/logic/bbVPool.c

gdb    ./a.exe
