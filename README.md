# 🏦 Bank Manager

> A desktop bank management application built with C++ and SDL2, featuring an interactive map interface, SQLite persistence, and a Python-powered recognition system.

> ⚠️ **This project is currently under active development and is not yet feature-complete.**

---

## Overview

Bank Manager is a graphical desktop application that lets you manage a network of banks laid out on an interactive world map. Banks can be added, searched, deleted, and locked — all through a custom-built SDL2 UI with animated windows, sprite-based icons, and a drag-to-pan map system.

---

## Features

### ✅ Implemented
- **Interactive world map** — pan across a large tiled map using arrow keys or click-and-drag
- **Bank placement** — place new banks at precise map coordinates by clicking
- **Bank types** — support for multiple bank categories (merchant, commercial, central), each with its own sprite
- **SQLite database** — all bank data is persisted to a `.db` file selected at startup via a native file dialog
- **Add banks** — multi-step form to enter bank name, interest rate, funds, clients, manager, type, and map position
- **Search banks** — floating panel to look up a bank by name
- **Delete banks** — remove a bank from the database
- **Lock banks** — lock a bank record with a signature (admin action)
- **Manager selection** — choose from multiple manager characters during bank creation
- **Animated pop-up windows** — smooth slide-in/out panel animations
- **Sprite animations** — frame-based sprite sheet animation system
- **Python recognition module** — launches a background `app.py` script for external processing

### 🚧 In Progress / Planned
- News feed panel
- Client management system (data model exists, UI pending)
- Full CRUD for clients
- Improved error handling and validation
- UI polish and layout refinements

---

## Tech Stack

| Component | Library/Tool |
|---|---|
| Graphics & Window | SDL2 |
| Text rendering | SDL2_ttf |
| Image loading | SDL2_image |
| Shapes/primitives | SDL2_gfx |
| Database | SQLite3 |
| File dialogs | Native File Dialog (nfd) |
| Recognition module | Python (`app.py`) |

---

## Project Structure

```
.
├── main.cpp          # Entry point — event loop, mode management
├── headers.h         # All classes and logic (SDLinit, database, uinter)
├── font.ttf          # UI font
├── app.py            # Python recognition module (background process)
└── assets/
    ├── map/          # Tiled world map (3x3 grid of PNG tiles)
    ├── buttons/      # UI button sprites (add, search, delete, lock, news)
    ├── ui/           # UI panels (window, manager frame, scan overlay, etc.)
    ├── bbank.png     # Big/central bank sprite
    ├── mbank.png     # Merchant bank sprite
    ├── cbank.png     # Commercial bank sprite
    ├── tip1-5.png    # Tip/hint images
    └── ...           # Manager character sprites
```

---

## Building

### Dependencies

Make sure the following are installed on your system:

- `SDL2`
- `SDL2_ttf`
- `SDL2_image`
- `SDL2_gfx`
- `sqlite3`
- `nfd` (Native File Dialog)

On Debian/Ubuntu:
```bash
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev libsqlite3-dev
```

`nfd` may need to be built from source: https://github.com/btzy/nativefiledialog-extended

### Compile

```bash
g++ main.cpp -o bankmanager \
  -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx \
  -lsqlite3 -lnfd \
  -std=c++17
```

### Run

```bash
./bankmanager
```

On launch, a file dialog will prompt you to open an existing `.db` database file.

---

## Database Schema

The application expects a SQLite database with a `banks` table:

```sql
CREATE TABLE banks (
    name     TEXT,
    type     INTEGER,
    interest INTEGER,
    funds    INTEGER,
    clients  INTEGER,
    manager  INTEGER,
    x        REAL,
    y        REAL,
    lock     INTEGER,
    sign     TEXT
);
```

---

## Controls

| Input | Action |
|---|---|
| Arrow keys | Pan the map |
| Click and drag | Pan the map |
| Click on map (in placement mode) | Set bank position |
| Click UI buttons | Navigate between modes |

---

## Notes

- The project window title and some internal strings are placeholder/debug text — these will be cleaned up before release.
- The codebase is intentionally monolithic for now (single header file with all logic). Refactoring into separate modules is planned.
- The Python `app.py` script is launched as a background process via `system()` — integration is still being finalized.

---

## License

Not yet decided. All rights reserved for now.
