SET PATH=C:\winlibs\mingw64\bin
gcc    -I ../ -g^
       ../test/bbList_testIterate.c^
       ../engine/logic/bbList_iterate.c^
      ../engine/logic/bbList.c^
      ../engine/logic/bbBloatedPool.c^
      ../engine/logic/bbLeanPool.c^
      ../engine/logic/bbVPool.c

gdb    ./a.exe
