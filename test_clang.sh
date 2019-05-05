CPP="main"
LINKED_CPP="gui.cpp label.cpp stopwatch.cpp core.cpp"
FLAGS="-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf"
clang++ $CPP.cpp $LINKED_CPP $FLAGS -o $CPP.exe && ./$CPP.exe