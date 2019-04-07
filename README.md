# minesweeper-sdl2

MIT License (c) 2019 

Documentations: [md](documentations.md) | [pdf](documentations.pdf)

## Requirements

- g++

- SDL2

## Installation

### Windows

- Install [MSYS2](http://www.msys2.org/)

- Open MSYS2 shell (Start Menu -> MSYS2 64-bit -> MSYS2 MSYS).

- Type:
```bash
pacman -Syu  # update all packages
```

- Restart MSYS shell, then install `make` and `tar`:
```bash
pacman -S make tar
```

- Install `GCC` and `GDB` 7.2.0 *(lastest version 8.3.0 got [`libbacktrace could not find executable to open`](https://sourceforge.net/p/mingw-w64/bugs/559/))*:
```bash
pacman -U mingw-w64-x86_64-gcc-7.2.0-3-any.pkg.tar.xz mingw-w64-x86_64-gcc-libs-7.2.0-3-any.pkg.tar.xz
```

> **Note**
> 
> - Download `mingw-*-7.2.0-3-any-pkg-tar-xz` from [here](http://repo.msys2.org/mingw/x86_64/).
> - Replace `x86_64` to `i686` if you're using Windows 32-bit.

- Install SDL2:
```bash
pacman -Ss x86_64-sdl2
```

- Install SDL2 libraries:
```bash
pacman -S mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_gfx mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_net mingw-w64-x86_64-SDL2_ttf
```

### Linux

#### Using command line

- Open your distro's Terminal.

- Update your distro.

- Type:
	- For Debian:
		- `apt-cache search libsdl2`
		- `apt-get install libsdl2-dev`

	- For Fedora/CentOS:
		- `yum search SDL2-devel`
		- `yum install SDL2-devel`

#### Install from source

- Get the `.zip`/`.tar.gz` file from [here](https://www.libsdl.org/download-2.0.php#source).

- Extract the archive, then change directory to the extracted folder.

- Compile the source: `make all`

- Install the package: `make install`

## Build

- Open MSYS2 shell.

- Clone repository

```bash
git clone https://github.com/tunc2112/bai-tap-lon
cd bai-tap-lon
```

- Run `test.sh`.

## References

- [Official documentations](https://wiki.libsdl.org/FrontPage)

- [Tutorial](http://lazyfoo.net/tutorials/SDL/)

- [Install SDL2 for Windows (Vietnamese)](https://daynhauhoc.com/t/hoi-cach-cai-sdl/43038/2)

- [Content of SDL2 (Linux)](https://fossies.org/linux/misc/SDL2-2.0.9.tar.gz/)

- `SDL_Quit()`: [old docs](https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlquit.html), [free() sample code](https://ideone.com/S4B9Jq), 

---

## Related links

- http://wiki.ros.org/CppStyleGuide

### event

- https://www.stdio.vn/articles/xu-ly-su-kien-trong-sdl-287

- http://www.cplusplus.com/forum/windows/194692/

- http://lazyfoo.net/tutorials/SDL/35_window_events/index.php

- https://wiki.libsdl.org/SDL_WindowEventID

- `catch event window event of which window sdl` gg

### other

- https://gist.github.com/roxygen/dd266f4b96fdf33537eb

- https://wiki.libsdl.org/SDL_MouseButtonEvent

- https://en.cppreference.com/w/cpp/io/clog


## Nothing

```python
>>> def F(a, b, p, x):
	res = 0
	for n in range(1, x+1):
		if (n * a**n) % p == b:
			print(n)
			res += 1
	return res

>>> F(4, 6, 7, 13)
6
1
>>> F(4, 6, 7, 13)
```