# CPP="try2"
# CPP="try_with_new_homescreen"
CPP="try"
LINKED_CPP="gui.h gui.cpp core.h core.cpp label.h label.cpp stopwatch.h stopwatch.cpp"
FLAGS="-Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf"
# CPP="22_timing/22_timing"
g++ $CPP.cpp $LINKED_CPP $FLAGS -o $CPP.exe && ./$CPP.exe
# g++ $CPP.cpp gui.h gui.cpp core.h core.cpp -Wall -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -o $CPP.exe && ./$CPP.exe