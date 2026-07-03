<div align="center">

  <h1>Bank System</h1>

  <p>
    <b>A custom C++/SDL2 desktop bank management simulator with a pannable world map, SQLite-backed bank records, animated UI states, native database loading, manager selection, record locking, and Python gesture input.</b>
  </p>

  <p>
    <img alt="C++17" src="https://img.shields.io/badge/C++17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
    <img alt="SDL2" src="https://img.shields.io/badge/SDL2-173B6B?style=for-the-badge&logo=libsdl&logoColor=white" />
    <img alt="SQLite" src="https://img.shields.io/badge/SQLite-003B57?style=for-the-badge&logo=sqlite&logoColor=white" />
    <img alt="Native File Dialog" src="https://img.shields.io/badge/Native_File_Dialog-7C3AED?style=for-the-badge" />
    <img alt="OpenCV MediaPipe" src="https://img.shields.io/badge/OpenCV_+_MediaPipe-FF6F00?style=for-the-badge" />
  </p>

  <p>
    <a href="#features">
      <img alt="Features" src="https://img.shields.io/badge/Features-00C2A8?style=for-the-badge" />
    </a>
    <a href="#architecture">
      <img alt="Architecture" src="https://img.shields.io/badge/Architecture-7C3AED?style=for-the-badge" />
    </a>
    <a href="#database-model">
      <img alt="Database model" src="https://img.shields.io/badge/Database_Model-2563EB?style=for-the-badge" />
    </a>
    <a href="#why-i-built-this">
      <img alt="Why I built this" src="https://img.shields.io/badge/Why_I_Built_This-FF3864?style=for-the-badge" />
    </a>
  </p>

</div>

---

## Overview

**Bank System** is a full custom desktop application built directly on SDL2 instead of a traditional GUI framework. It renders its own interface, loads bank data from SQLite, shows banks on a large pannable map, and lets the user create, inspect, delete, and lock bank records.

The project combines several systems that usually live in separate layers:

| System | What it does |
| --- | --- |
| SDL2 shell | Owns the window, renderer, font loading, textures, event loop, and frame presentation. |
| Database layer | Opens a user-selected `.db` file and runs SQLite operations for bank records. |
| Map renderer | Builds a large world map from tiles and maps normalized bank coordinates into screen positions. |
| UI flow | Switches between loading, map, add-bank, manager selection, placement, confirmation, search/delete/news, and lock flows. |
| Asset pipeline | Loads bank sprites, map tiles, UI panels, buttons, tips, manager art, and cutscene frame sequences. |
| Gesture bridge | Uses a Python OpenCV/MediaPipe process to write hand-state values into `state.txt`. |

## Features

<table>
  <tr>
    <td><b>Custom SDL2 interface</b></td>
    <td>No GUI framework: buttons, text areas, panels, map, banks, and animations are rendered manually.</td>
  </tr>
  <tr>
    <td><b>Pannable world map</b></td>
    <td>Renders a large map from 9 image tiles and supports viewport movement.</td>
  </tr>
  <tr>
    <td><b>Bank records</b></td>
    <td>Stores name, type, interest, funds, clients, manager, coordinates, lock state, and signature.</td>
  </tr>
  <tr>
    <td><b>Bank creation flow</b></td>
    <td>Collects bank details, chooses a type, selects a manager, places the bank on the map, then saves it.</td>
  </tr>
  <tr>
    <td><b>Search and delete workflows</b></td>
    <td>Find banks by name, show details, and remove records from SQLite.</td>
  </tr>
  <tr>
    <td><b>Locking flow</b></td>
    <td>Locks a bank record with a signature field and persists the lock state.</td>
  </tr>
  <tr>
    <td><b>Animated state variants</b></td>
    <td>Uses normal, profit, and loss variants for bank sprites.</td>
  </tr>
  <tr>
    <td><b>Manager selection</b></td>
    <td>Includes a manager-pick screen with profiles, visual selection, and cutscene frame assets.</td>
  </tr>
  <tr>
    <td><b>Native database picker</b></td>
    <td>Uses Native File Dialog to select the SQLite database at startup.</td>
  </tr>
  <tr>
    <td><b>Gesture input prototype</b></td>
    <td>Python hand tracking writes simple gesture states into <code>state.txt</code> for the SDL app.</td>
  </tr>
</table>

## Tech Stack

<p>
  <img alt="C++17" src="https://img.shields.io/badge/C++17-0B5FFF?style=flat-square&logo=cplusplus&logoColor=white" />
  <img alt="SDL2" src="https://img.shields.io/badge/SDL2-1F6FEB?style=flat-square&logo=libsdl&logoColor=white" />
  <img alt="SDL2 image" src="https://img.shields.io/badge/SDL2_image-F97316?style=flat-square&logo=image&logoColor=white" />
  <img alt="SDL2 ttf" src="https://img.shields.io/badge/SDL2_ttf-9333EA?style=flat-square" />
  <img alt="SDL2 mixer" src="https://img.shields.io/badge/SDL2_mixer-06B6D4?style=flat-square" />
  <img alt="SDL2 gfx" src="https://img.shields.io/badge/SDL2_gfx-111827?style=flat-square" />
  <img alt="SQLite3" src="https://img.shields.io/badge/SQLite3-003B57?style=flat-square&logo=sqlite&logoColor=white" />
  <img alt="NFD" src="https://img.shields.io/badge/NFD-7C3AED?style=flat-square" />
  <img alt="Python" src="https://img.shields.io/badge/Python-2563EB?style=flat-square&logo=python&logoColor=white" />
  <img alt="OpenCV" src="https://img.shields.io/badge/OpenCV-22C55E?style=flat-square&logo=opencv&logoColor=white" />
  <img alt="MediaPipe" src="https://img.shields.io/badge/MediaPipe-F97316?style=flat-square" />
</p>

| Layer | Technology | Role |
| --- | --- | --- |
| Main app | `C++17` | Application state, data structures, database calls, UI modes, and SDL orchestration. |
| Rendering/UI | `SDL2`, `SDL2_image`, `SDL2_ttf`, `SDL2_mixer`, `SDL2_gfx` | Window, textures, fonts, sprites, map tiles, and animated assets. |
| Persistence | `SQLite3` | Bank records and lock/signature state. |
| File picker | `Native File Dialog` | Startup database selection. |
| Gesture detector | `Python`, `OpenCV`, `MediaPipe` | Webcam hand-state recognition. |
| Build | `Makefile`, `pkg-config`, GTK flags | Native build command and NFD/GTK linking. |

## Project Structure

```text
.
|-- main.cpp              # SDL app entry point and event-loop orchestration
|-- headers.h             # Database layer, SDL wrapper, UI state, map logic, asset loading
|-- app.py                # OpenCV/MediaPipe gesture detector
|-- Makefile              # Native C++ build target
|-- state.txt             # Runtime gesture bridge
|-- sign.txt              # Runtime signature/lock helper artifact
|-- query.sql             # SQL scratch/helper file
|-- nfd.h / nfd_sdl2.h    # Native File Dialog headers
|-- tinyfiledialogs.*     # Earlier file dialog helper kept as an artifact
|-- libnfd.a              # Native File Dialog static library
|-- databases/
|   |-- banks.sqlite      # Database artifact
|   `-- clients.sqlite    # Client database artifact
|-- assets/
|   |-- map/              # 9 map tiles
|   |-- ui/               # Panels and UI icons
|   |-- buttons/          # Main action buttons
|   |-- cutscenes/        # Manager cutscene frame folders and videos
|   `-- *.png             # Bank sprites, manager art, tips, icons
|-- output/main           # Existing compiled binary artifact
`-- README.md
```

## Architecture

```text
main.cpp
|-- creates SDLinit
|-- creates database
|-- creates uinter
|-- owns the event loop
|-- forwards events into uinter::handle()
|-- clears, lays out, and presents each frame
`-- exits on SDL_QUIT

database
|-- opening()       -> native file dialog + sqlite3_open
|-- loadbanks()     -> load all bank records for map rendering
|-- search()        -> find a bank by name
|-- add()           -> insert a new bank record
|-- remove()        -> delete a bank record
|-- lock()          -> set lock/sign fields
`-- modify()        -> declared for record update flow

SDLinit
|-- initializes SDL, SDL_image, SDL_ttf, and NFD
|-- owns SDL_Window, SDL_Renderer, and font
|-- wraps text drawing, buttons, text areas, clear, and present
`-- shuts down native subsystems

uinter
|-- loads every visual asset
|-- owns the mode/state machine
|-- renders map tiles and bank sprites
|-- handles bank creation, manager selection, placement, search, delete, and lock UI
|-- maps bank coordinates to viewport positions
|-- animates bank state variants and panel transitions
`-- reads gesture bridge state when gesture recognition is used

app.py
|-- opens webcam
|-- runs MediaPipe Hands
|-- classifies closed/open/peace gestures
`-- writes 0/1/2/x into state.txt
```

The prototype currently keeps most implementation inside `headers.h`. That makes the project easy to inspect in one file, but the natural future split would be `database`, `ui`, `map`, `assets`, `gesture`, and `workflow` modules.

## Runtime Modes

The C++ app uses integer modes to move through workflows:

| Mode | Screen / behavior |
| --- | --- |
| `-2` | Loading/splash flow. |
| `-1` | Main world map. |
| `1` | Add-bank details form. |
| `11` | Manager selection and cutscene flow. |
| `12` | Bank placement on the map. |
| `13` | Confirm and save. |
| `22` | Bank locking flow. |

The map screen also owns board submodes for workflows like search, delete, and news/action panels.

## Database Model

The app logic expects a `banks` table shaped like:

```sql
CREATE TABLE "banks" (
    "name" TEXT NOT NULL,
    "type" INTEGER,
    "interest" INTEGER,
    "funds" INTEGER,
    "clients" INTEGER,
    "manager" INTEGER,
    "x" REAL,
    "y" REAL,
    "lock" INTEGER,
    "sign" TEXT,
    PRIMARY KEY("name")
);
```

| Field | Meaning |
| --- | --- |
| `name` | Bank name and primary identifier. |
| `type` | Bank visual/category id. |
| `interest` | Interest rate value. |
| `funds` | Stored capital/funds value. |
| `clients` | Client count. |
| `manager` | Selected manager/profile id. |
| `x`, `y` | Normalized map coordinates. |
| `lock` | Lock state flag. |
| `sign` | Signature attached to the lock workflow. |

## Gesture Bridge

`app.py` runs for a short webcam recognition window and writes one value to `state.txt`:

| Gesture | Value |
| --- | --- |
| Closed hand | `0` |
| Open hand | `1` |
| Peace sign | `2` |
| Finished/reset | `x` |

This is a simple file-based bridge:

```text
Python camera process -> state.txt -> C++ SDL app
```

It is intentionally lightweight for a prototype. A production version would use a socket, pipe, or in-process integration instead.

## Build

Install dependencies on Ubuntu/Debian:

```bash
sudo apt install build-essential pkg-config libsdl2-dev libsdl2-image-dev \
  libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev libsqlite3-dev \
  libgtk-3-dev python3-pip
```

Install gesture dependencies:

```bash
python3 -m pip install opencv-python mediapipe
```

Build the C++ app:

```bash
make GCC
```

The Makefile outputs:

```text
output/main
```

## Run

Run from the repository root:

```bash
./output/main
```

At startup, the app opens a native file dialog for selecting a `.db` database file. Choose a database with the expected `banks` table shape.

To run gesture recognition directly:

```bash
python3 app.py
```

## Why I Built This

> i had this question of how bank managers manage thier own banks , then i started imagining a system with locks and accounts and customers through a big map,
>this project reinforced my c++ skills and it was quit a fun one to make , it obviously has some missing ui features so i may come back later for some fixes 

## Current Status

| Area | Status |
| --- | --- |
| SDL2 app shell | Working |
| Native DB file picker | Working |
| Map tile rendering | Working |
| Bank sprite rendering | Working |
| Bank loading from SQLite | Working |
| Add-bank workflow | Implemented |
| Manager selection | Implemented |
| Bank placement | Implemented |
| Search/delete/lock flows | Implemented |
| Gesture recognition bridge | Prototype |
| Module separation | Needs refactor |

## Known Limitations

| Limitation | Current state |
| --- | --- |
| Large god header | Most implementation lives inside `headers.h`. |
| Schema validation | The selected database is not strongly validated before use. |
| UI layout | Fixed around a `1280x720` window. |
| Asset volume | Many generated cutscene frames and local database artifacts are committed. |
| File IPC | `state.txt` works for a prototype but is not robust. |
| Camera input | Gesture recognition depends on lighting, webcam quality, and MediaPipe compatibility. |
| Database artifacts | Multiple `.db`/`.sqlite` files exist with different schemas. |

## Roadmap Ideas

| Idea | Why it would help |
| --- | --- |
| Split `headers.h` | Separate database, UI, map, assets, gesture, and workflow code. |
| Add schema validation | Warn when the selected database does not match expected columns. |
| Centralize mode enum | Replace magic integers like `-2`, `-1`, `11`, `22`. |
| Project-relative asset manager | Make texture loading easier to maintain. |
| Replace `state.txt` bridge | Use sockets, pipes, or a direct integration. |
| Reduce committed generated assets | Keep repo lighter and easier to clone. |
| Add migrations | Manage database evolution safely. |
| Add error UI | Surface database and asset-loading failures in the app. |

---

<div align="center">
  <sub>Built with C++17, SDL2, SQLite, Native File Dialog, Python hand tracking, and a lot of custom UI state.</sub>
</div>
