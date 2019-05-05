# minesweeper-sdl2

Documentation: [md](documentation.md) | [pdf](documentation.pdf)

## Rules

- http://minesweeperonline.com/

- Click chuột trái vào 1 ô:
	- nếu ô đó trắng -> loang
	- nếu ô đó có số -> không loang

- Click chuột giữa vào 1 ô:
	- highlight 8 ô xung quanh
	- nếu 8 ô xung quanh đã đánh đầy đủ bom -> loang (có thể chết)
	- nếu không đủ -> không có phản ứng gì

- Click chuột phải vào 1 ô:
	- nếu không có cờ -> đặt cờ
	- nếu có cờ -> bỏ cờ

- Trạng thái cuối cùng:
	- sống: hiện hết bom
	- chết: fill đỏ các ô có bom nổ, dấu x các chỗ đặt sai vị trí

## Requirements

- g++

- SDL2

### Installation

#### Windows

- Install [MSYS2](http://www.msys2.org/)

- Open MSYS2 shell (Start Menu -> MSYS2 64-bit -> MSYS2 MSYS).

- Type:
```bash
pacman -Syu  # update all packages
```

> **Note:** Run `install.sh` for quick install.

- Restart MSYS shell, then install `make`, `tar`, `gdb`:
```bash
pacman -S make tar mingw-w64-x86_64-gdb
```

- Install `GCC` and `GCC libs` 7.2.0 *(lastest version 8.3.0 got [`libbacktrace could not find executable to open`](https://sourceforge.net/p/mingw-w64/bugs/559/))*:
```bash
pacman -U mingw-w64-x86_64-gcc-7.2.0-3-any.pkg.tar.xz mingw-w64-x86_64-gcc-libs-7.2.0-3-any.pkg.tar.xz
```

> **Note:**
> 
> - Download `mingw-gcc*-7.2.0-3-any.pkg.tar.gz` from [here](http://repo.msys2.org/mingw/x86_64/).
> - Replace `x86_64` to `i686` if you're using Windows 32-bit.

- Install SDL2:
```bash
pacman -Ss x86_64-sdl2
```

- Install SDL2 libraries:
```bash
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_gfx mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_net mingw-w64-x86_64-SDL2_ttf
```

#### Linux

##### Using command line

- Open your distro's Terminal.

- Update your distro.

- Type:
	- For Debian: `apt-get install libsdl2-dev`

	- For Fedora/CentOS: `yum install SDL2-devel`

##### Install from source

- Get the `.zip`/`.tar.gz` file from [here](https://www.libsdl.org/download-2.0.php#source).

- Extract the archive, then change directory to the extracted folder.

- Compile the source: `make all`

- Install the package: `make install`

## Compilation

- Open MSYS2 shell/Terminal.

- Clone repository.

```bash
git clone https://github.com/tunc2112/bai-tap-lon
cd bai-tap-lon
```

- Run.
```
./test.sh
```

## Contributing

## License

MIT License (c) 2019

## References

### Image

- https://www.pngfly.com/png-uo3b9t

- https://www.pngfly.com/png-43u2w8/

- https://www.pngfly.com/png-2w2b1q/

- https://www.kisspng.com/png-minesweeper-free-mine-sweeper-mono-android-game-4000862/download-png.html

- https://www.pinterest.com/pin/249949848040501818

### Links

- https://2.bp.blogspot.com/-_oU3s1iadRw/XAkw2Q6DEMI/AAAAAAAABNQ/22kYI4c804ooQ7uCJhK5Epo4subN8AsaQCPcBGAYYCw/s1600/minesweeper_tiles.jpg

- http://guides.lib.berkeley.edu/how-to-write-good-documentation

- [Official documentations](https://wiki.libsdl.org/FrontPage)

- [Tutorial](http://lazyfoo.net/tutorials/SDL/)

- [Install SDL2 for Windows (Vietnamese)](https://daynhauhoc.com/t/hoi-cach-cai-sdl/43038/2)

- [Content of SDL2 (Linux)](https://fossies.org/linux/misc/SDL2-2.0.9.tar.gz/)

- https://github.com/AlfonsoJLuna/minesweeper

- http://gigi.nullneuron.net/gigilabs/displaying-text-in-sdl2-with-sdl_ttf/

- https://jsfiddle.net/HK_boy/q3heu7m4/60/

- https://forums.libsdl.org/viewtopic.php?p=48249

---

- `SDL_Quit()`: [old docs](https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlquit.html), [free() sample code](https://ideone.com/S4B9Jq), 

- http://members.chello.nl/w.boeke/SDL-widgets/

- http://forums.libsdl.org/viewtopic.php?p=41075

- [load image to renderer](https://gist.github.com/armornick/3434362)

- https://stackoverflow.com/questions/21890627/drawing-a-rectangle-with-sdl2

- http://sdl.beuc.net/sdl.wiki/FAQ_Console

- https://wiki.libsdl.org/SDL_RenderPresent

- https://gist.github.com/armornick/3434362

- https://www.stdio.vn/articles/load-texture-trong-sdl-288

- http://gigi.nullneuron.net/gigilabs/displaying-an-image-in-an-sdl2-window/

- http://headerphile.com/sdl2/sdl-2-part-7-using-png-files/

- https://gamedev.stackexchange.com/questions/72613/how-can-i-render-a-texture-to-the-screen-in-sdl2

- https://www.stdio.vn/articles/draw-text-trong-sdl-308

- https://stackoverflow.com/questions/22886500/how-to-render-text-in-sdl2/22889483

---

## Related links

- http://wiki.ros.org/CppStyleGuide

- https://blog.vietanhdev.com/posts/thuat-toan-loang-trong-do-min/

### event

- https://www.stdio.vn/articles/xu-ly-su-kien-trong-sdl-287

- http://www.cplusplus.com/forum/windows/194692/

- http://lazyfoo.net/tutorials/SDL/35_window_events/index.php

- https://wiki.libsdl.org/SDL_WindowEventID

- `catch event window event of which window sdl` gg

- https://wiki.libsdl.org/SDL_MouseButtonEvent

- https://gamedev.stackexchange.com/questions/56349/how-to-implement-sdl-button-menu-gui-with-callbacks

### other

- https://gist.github.com/roxygen/dd266f4b96fdf33537eb

- https://en.cppreference.com/w/cpp/io/clog
