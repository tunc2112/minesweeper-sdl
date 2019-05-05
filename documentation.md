# minesweeper-sdl2

## Installation

## Tutorial

> sample:
> - https://openpyxl.readthedocs.io/en/latest/api/openpyxl.writer.excel.html
> - http://transit.iut2.upmf-grenoble.fr/doc/gtkmm-3.0/reference/html/classGtk_1_1AboutDialog.html

## Classes

### `MainWindow`

#### Include 

```cpp
#include "gui.h"
```

#### Public member attributes

> ```cpp
> SDL_Window* root
> ```

> ```cpp
> SDL_Renderer* renderer
> ```

> ```cpp
> void (*main_activity)(SDL_Event& e);
> ```

#### Constructor & Destructor

> ```cpp
> MainWindow::MainWindow(const char* window_title="", int width=400, int height=300)
> ```

**Parameters**
<table style="border:0 !important;">
	<tr>
		<td>window_title</td>
		<td>window_title of window</td>
	</tr>
	<tr>
		<td>width</td>
		<td>width of window</td>
	</tr>
	<tr>
		<td>height</td>
		<td>height of window</td>
	</tr>
</table>

> ```cpp
> MainWindow::~MainWindow()
> ```

#### Public Member Functions

> ```cpp
> void MainWindow::mainloop()
> ```

**Description**

**Parameters**

---

> ```cpp
> void MainWindow::close()
> ```

**Description**

**Parameters**

### `Button`

#### Include 

```cpp
#include "gui.h"
```

#### Constructor & Destructor

> ```cpp
> Button();
> ```

> ```cpp
> Button(MainWindow* win, int w, int h, const RGBA& c, int x=0, int y=0);
> ```

**Parameters**

> ```cpp
> ~Button();
> ```

#### Public Member Functions

> ```cpp
> int getMouseState();
> ```

**Description**

Get the state of button.

**Return value**

An integer.

---

> ```cpp
> void setChangingStateColor(int state, const RGBA& c);
> ```

**Description**

What background color to use when the button is in `state` state.

**Parameters**

`state`: state of button.

---

> ```cpp
> void setColorByMouseState(int state);
> ```

**Description**

Change the color when the button is in `state` state.

**Parameters**

`state`: state of button.

---

> ```cpp
> void drawButton();
> ```

**Description**

Draw button to the screen.

---

> ```cpp
> void bindCommand(command f, std::string clicked_mouse="left");
> ```

**Description**

Bind a function that is called when the button is pressed by mouse `clicked_mouse` button.

**Parameters**

---

> ```cpp
> void runCommand(SDL_MouseButtonEvent& b, std::string clicked_mouse="left");
> ```

**Description**

Call the bound function when the button is pressed by mouse `clicked_mouse` button.

**Parameters**

---

> ```cpp
> void handleEvent(SDL_Event &event);
> ```

**Description**

Catch event 

**Parameters**

### `_Button`

General type of button.

### `Button`

Button which its background is a RGBA color.

Inherited from class `_Button`.

Using for testing only.

### `ButtonImage`

Button which its background is an image.

Inherited from class `_Button`.

#### Include 

```cpp
#include "gui.h"
```

#### Public member attributes

> ```cpp
> SDL_Window* root
> ```

> ```cpp
> SDL_Renderer* renderer
> ```

> ```cpp
> void (*main_activity)(SDL_Event& e);
> ```

#### Constructor & Destructor

> ```cpp
> ButtonImage();
> ```

> ```cpp
> ButtonImage(MainWindow* win, std::string img_dỉr, int w, int h, int x=0, int y=0);
> ```

> ```cpp
> ButtonImage(MainWindow* win, SDL_Texture* img, int w, int h, int x=0, int y=0);
> ```

> ```cpp
> ~ButtonImage();
> ```

#### Added Public Member Functions

---

### `MinesweeperGUI`

#### Constructor & Destructor

> ```cpp
> MinesweeperGUI();
> ```

> ```cpp
> MinesweeperGUI(MainWindow* win, int px, int py, std::string level="beginner");
> ```

> ```cpp
> MinesweeperGUI(MainWindow* win, int px, int py, int _w, int _h, int _bombs);
> ```

> ```cpp
> ~MinesweeperGUI();
> ```

#### Added Public Member Functions

> ```cpp
> void setup();
> ```

**Description**

**Parameters**

> ```cpp
> void toggleFlag(int r, int c);
> ```

**Description**

**Parameters**

> ```cpp
> void openCell(int r, int c);
> ```

**Description**

**Parameters**

> ```cpp
> void openABomb(int r, int c);
> ```

**Description**

**Parameters**

> ```cpp
> void view(bool open_all=false);
> ```

**Description**

**Parameters**

> ```cpp
> void openCellsFrom(int r, int c);
> ```

**Description**

**Parameters**

> ```cpp
> void captureEvent(SDL_Event& event);
> ```

**Description**

**Parameters**
