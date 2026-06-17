# cub3D 🏰

A pseudo-3D rendering engine inspired by Wolfenstein 3D, built in C as part of the 42 school curriculum. The project implements a **raycasting** algorithm to display a 3D-looking environment from a 2D map, complete with textures, colors, and player movement.

> 🏆 Final score: **125/100** — graded project, 42 School

## 🎥 Demo

![cub3D gameplay demo](assets/demo/preview.gif)

A full-length recording of the gameplay is also available: [`assets/demo/gameplay.mp4`](assets/demo/gameplay.mp4)

## 📋 Table of Contents

- [Overview](#-overview)
- [Features](#-features)
- [Requirements](#-requirements)
- [Installation](#-installation)
- [Usage](#-usage)
- [Controls](#-controls)
- [Map file format (.cub)](#-map-file-format-cub)
- [Project structure](#-project-structure)
- [Makefile commands](#-makefile-commands)
- [Result](#-result)
- [Authors](#-authors)

## 🧭 Overview

cub3D renders a first-person view of a maze defined in a `.cub` configuration file. The rendering relies on a raycasting algorithm that casts rays from the player's position to compute the distance to walls and determine the height of the walls drawn on screen, creating the illusion of a 3D environment from a purely 2D map.

## ✨ Features

- Real-time rendering via raycasting
- Different wall textures depending on orientation (north, south, east, west)
- Customizable floor and ceiling colors
- Smooth player movement and rotation
- Mouse look support (bonus)
- Full parsing and validation of `.cub` map files
- Map closure check (flood fill)
- Clean program exit (memory freeing, window closing)

## 🔧 Requirements

The project was developed and tested on **Linux**. The following dependencies are needed:

- A C compiler (`cc` / `gcc`)
- `make`
- `git` (to automatically clone MiniLibX)
- X11 development libraries:

```bash
sudo apt-get update
sudo apt-get install libxext-dev libx11-dev libbsd-dev
```

> MiniLibX is automatically cloned and compiled by the Makefile — no manual setup required.

## 📦 Installation

Clone the repository and build the project:

```bash
git clone <your-repo-url> cub3D
cd cub3D
make
```

The Makefile will automatically:
1. Clone MiniLibX if it isn't already present
2. Compile MiniLibX
3. Compile libft
4. Compile the project and generate the `cub3D` executable

## 🚀 Usage

Run the program with a `.cub` map file as argument:

```bash
./cub3D assets/maps/map.cub
```

If the file is invalid (unclosed map, missing textures, wrong characters, etc.), a clear error message is printed to the terminal.

## 🕹️ Controls

| Key | Action |
|---|---|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` (left arrow) | Rotate camera left |
| `→` (right arrow) | Rotate camera right |
| Mouse movement | Look around (bonus) |
| `ESC` | Quit the program |
| Window close button | Quit the program |

## 🗺️ Map file format (.cub)

A `.cub` file must contain, in any order, before the map itself:

```
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm
F 220,100,0
C 225,30,0
```

- `NO`, `SO`, `WE`, `EA`: paths to the wall textures (north, south, west, east)
- `F`: floor color in R,G,B format
- `C`: ceiling color in R,G,B format

Followed by the map itself, made up of:
- `1`: wall
- `0`: empty space
- `N`, `S`, `E`, `W`: player's starting position and orientation
- ` ` (space): allowed only inside the map (not as a border, unless the map is otherwise enclosed by walls)

**Full example:**

```
NO ./assets/textures/north.xpm
SO ./assets/textures/south.xpm
WE ./assets/textures/west.xpm
EA ./assets/textures/east.xpm
F 220,100,0
C 225,30,0

111111
100001
1001N1
100001
111111
```

> ⚠️ The map must be fully enclosed by walls, otherwise the program will refuse to launch.

## 📁 Project structure

```
.
├── Makefile
├── main.c
├── cub3d.h
├── assets/
│   ├── demo/                  # gameplay video & GIF preview
│   ├── screenshots/            # screenshots (e.g. final score)
│   ├── libs/
│   │   ├── gnl/                # get_next_line
│   │   ├── libft/              # 42's standard library
│   │   └── minilibx-linux/     # MiniLibX (cloned automatically)
│   ├── maps/                   # sample .cub files
│   └── textures/               # .xpm files
├── game/
│   ├── camera.c
│   ├── events.c
│   ├── keys.c
│   ├── player.c
│   ├── raycasting.c
│   ├── raycasting_helper.c
│   ├── render.c
│   ├── textures.c
│   └── window.c
├── parsing/
│   ├── checker.c
│   ├── file_parsing.c
│   ├── flood_fill.c
│   ├── map_parsing.c
│   ├── parsing_utils.c
│   ├── parsing_utils2.c
│   └── storage.c
└── utils/
    ├── exit.c
    ├── free.c
    └── print_utils.c
```

## ⚙️ Makefile commands

| Command | Description |
|---|---|
| `make` | Builds the project (MiniLibX, libft, then cub3D) |
| `make clean` | Removes object files |
| `make fclean` | Removes object files, the executable, libft, and MiniLibX |
| `make re` | Full rebuild (fclean + all) |
| `make leak` | Builds and runs the program under Valgrind to detect memory leaks |

## 🏆 Result

![Final evaluation score](assets/screenshots/score.png)

This project was evaluated and graded **125/100** at 42 School (group project, ~280 hours, 5775 XP).

## 👥 Authors

Built as part of the 42 School curriculum.

- hmimouni
- pacda-si

---

Feel free to open an issue if you run into any build or runtime problems.
