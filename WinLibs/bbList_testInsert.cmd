SET PATH=C:\winlibs\mingw64\bin
gcc    -I ../ -g^
       ../test/bbList_testInsert.c^
       ../engine/logic/bbList_insert.c^
      ../engine/logic/bbList.c^
      ../engine/logic/bbBloatedPool.c^
      ../engine/logic/bbLeanPool.c^
      ../engine/logic/bbVPool.c

gdb    ./a.exe
