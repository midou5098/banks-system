# BankSim / SDL Banking Sandbox

> A chaotic SDL2 + SQLite powered banking sandbox/game where you create banks, manage worlds, and interact through a custom GUI system.
> **Currently in active development.**

---

## Preview

---

## Features

* 🏦 Create and manage custom banks
* 🌍 Scrollable world/map system
* 🎮 Fully custom SDL2 interface
* 🗄️ SQLite database integration
* 🖼️ Asset-driven UI and animated sprites
* 📂 Native file dialog database loading
* 👤 Multiple manager archetypes
* 🔄 Interactive viewport + draggable camera
* ✨ Animated windows and transitions

---

## Tech Stack

* **C++**
* SDL
* SQLite
* SDL_image
* SDL_ttf
* SDL2_gfx
* Native File Dialog (NFD)

---

## Current State

⚠️ This project is still heavily under development.

Things currently being worked on:

* Database search system
* Bank modification/removal
* Better UI architecture
* Gameplay balancing
* More world interaction
* Cleaner code structure
* Save/load improvements
* Additional animations and effects

---

## Project Structure

```bash
.
├── main.cpp
├── headers.h
├── assets/
│   ├── map/
│   ├── buttons/
│   ├── ui/
│   └── ...
├── font.ttf
└── database.db
```

---

## Build Requirements

Install:

* SDL2
* SDL2_image
* SDL2_ttf
* SDL2_gfx
* SQLite3
* Native File Dialog Extended (NFD)

### Linux Example

```bash
sudo apt install libsdl2-dev libsdl2-image-dev \
libsdl2-ttf-dev libsdl2-gfx-dev sqlite3 \
libsqlite3-dev
```

---

## Build

```bash
g++ main.cpp -o banksim \
-lSDL2 -lSDL2_image -lSDL2_ttf \
-lSDL2_gfx -lsqlite3
```

---

## Run

```bash
./banksim
```

---

## Gameplay / Concept

The idea is to create a weird sandbox-style banking simulation where players can:

* Create banks
* Place them on a world map
* Assign managers
* Handle reputation/funds/clients
* Expand influence
* Eventually interact with other systems and events

The project mixes strategy, satire, and experimental UI ideas.

---

## Development Notes

Current codebase includes:

* SDL rendering loop
* Event handling system
* Animated textures
* Database wrapper
* UI state machine
* Map viewport system
* Drag camera controls
* Popup animation system

Core loop and rendering are implemented in `main.cpp` and `headers.h`.  

---

## TODO

* [ ] Proper search system
* [ ] Database editor
* [ ] Bank economy simulation
* [ ] AI behavior
* [ ] Sound system
* [ ] Better asset management
* [ ] Multiplayer experiments
* [ ] Improved save handling
* [ ] Code refactor

---

## Contributing

Since the repo is still evolving rapidly, contributions and ideas are welcome.

---

## License

MIT
---

## Author

Made by Mohamed Amdouni.
