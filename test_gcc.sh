CPP="try_with_new_homescreen"
LINKED_CPP="gui.h gui.cpp label.h label.cpp stopwatch.h stopwatch.cpp core.h core.cpp"
FLAGS="-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf"
g++ $CPP.cpp $LINKED_CPP $FLAGS -o $CPP.exe && ./$CPP.exe