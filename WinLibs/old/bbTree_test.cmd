SET PATH=C:\winlibs\mingw64\bin
gcc    -I ../^
       ../test/bbTree_test.c^
      ../engine/logic/bbTree.c^
      ../engine/logic/bbBloatedPool.c^
      ../engine/logic/bbLeanPool.c^
      ../engine/logic/bbVPool.c
gdb ./a.exe