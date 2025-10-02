# fictional-octo-journey
A basic ping pong game implementation in C

## Description
This is a simple console-based ping pong game written in C using the ncurses library. Two players can play against each other on the same keyboard.

## Features
- Two-player gameplay
- Real-time score tracking
- Simple keyboard controls
- Console-based graphics using ncurses

## Requirements
- GCC compiler
- ncurses library

To install ncurses on Ubuntu/Debian:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

## Building
To compile the game, simply run:
```bash
make
```

To clean compiled files:
```bash
make clean
```

## How to Play
Run the game with:
```bash
./pingpong
```

Or use:
```bash
make run
```

### Controls
- **Left Player (Left Paddle):**
  - `W` - Move paddle up
  - `S` - Move paddle down

- **Right Player (Right Paddle):**
  - `Up Arrow` - Move paddle up
  - `Down Arrow` - Move paddle down

- **Q** - Quit the game

### Gameplay
- The ball bounces between the paddles
- Score a point when your opponent misses the ball
- The game continues until you press 'Q' to quit
- Final score is displayed when exiting

## Game Structure
- `pingpong.c` - Main game source code
- `Makefile` - Build configuration
- `.gitignore` - Excludes compiled binaries from git

Enjoy the game!
