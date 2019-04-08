pacman -S make tar mingw-w64-x86_64-gdb
wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-gcc-7.2.0-3-any.pkg.tar.xz
wget http://repo.msys2.org/mingw/x86_64/mingw-w64-x86_64-gcc-libs-7.2.0-3-any.pkg.tar.xz
pacman -U mingw-w64-x86_64-gcc-7.2.0-3-any.pkg.tar.xz mingw-w64-x86_64-gcc-libs-7.2.0-3-any.pkg.tar.xz
pacman -Ss x86_64-sdl2
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_gfx mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_net mingw-w64-x86_64-SDL2_ttf
