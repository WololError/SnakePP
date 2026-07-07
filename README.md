# SnakePP

Object-oriented implementation of the classic Snake game in C++ using Allegro 5.

## Requirements

- Linux
- Allegro 5

```bash
sudo apt install build-essential liballegro5-dev
```

## Build & Run

```bash
make compile   # build the game
make run       # run the game
make clean     # remove build artifacts
```

The executable is generated in `exe/snake`. Run it from the project root (assets are loaded via relative paths).

## Controls

- Arrow keys or ZQSD (WASD on QWERTY layouts): move the snake
- Close the window to quit; the game restarts automatically after a game over