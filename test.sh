LINKED_CPP="gui.h gui.cpp label.h label.cpp stopwatch.h stopwatch.cpp core.h core.cpp"
FLAGS="-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf"
g++ try.cpp $LINKED_CPP $FLAGS -o try.exe && ./try.exe