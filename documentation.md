# minesweeper-sdl2 Documentation

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

#### Constructor & Destructor Documentation

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

#### Public Member Functions Documentation

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

#### Constructor & Destructor Documentation

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

#### Public Member Functions Documentation

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


### `BombFieldGUI`

### `MinesweeperCore`
