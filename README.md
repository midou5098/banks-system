# 🏦 Bank system
 
> A desktop bank management system with a gesture-controlled UI, built from scratch in C++ with SDL2 and powered by a Python hand-tracking module using MediaPipe.
 
---
 
## 🧠 What is this?
 
This is a fully custom desktop application for managing banks and their data — built without any GUI framework, just raw SDL2 rendering on a 1280×720 window. It features an interactive world map you can drag around, animated bank sprites, a SQLite-backed database, and a hand gesture recognition module that lets you control the app using your webcam.
 
Built as a personal challenge. Messy, chaotic, and beautiful.
 
---
 
## ✨ Features
 
- 🗺️ **Pannable world map** — drag a 3840×2160 virtual world to explore bank locations, or toggle a full-screen minimap view
- 🏛️ **Three bank types** — Central, Mid-tier, and Branch banks, each with unique sprites and animated profit/loss states
- 🖱️ **Custom UI engine** — buttons, text areas, floating popup windows, and animated panel slide-ins, all hand-rolled in SDL2
- 🎬 **Manager cutscenes** — animated cutscene sequences play when assigning a manager to a new bank
- ✋ **Hand gesture control** — a Python subprocess uses your webcam + MediaPipe to detect hand states (open, closed, peace) and write them to a shared file for the C++ app to read
- 🗄️ **SQLite persistence** — all bank data (name, type, interest rate, funds, client count, manager, coordinates, lock status) is stored in a `.db` file you select at runtime via a native file dialog
- 🔒 **Bank locking** — banks can be locked with a signature, restricting modifications
- 🔍 **Search, add, edit & delete** — full CRUD operations on bank records through the in-app UI
- 📁 **Native file dialog** — uses NFD (Native File Dialog) for opening `.db` files cleanly without blocking SDL
---
 
## 🛠️ Tech Stack
 
| Layer | Technology |
|---|---|
| UI & Rendering | SDL2, SDL2_ttf, SDL2_image, SDL2_gfx |
| Database | SQLite3 |
| File Dialog | Native File Dialog (NFD) |
| Hand Tracking | Python, MediaPipe, OpenCV |
| Language | C++17, Python 3 |
 
---
 
## 📁 Project Structure
 
```
.
├── main.cpp          # Entry point — SDL event loop, mode routing
├── headers.h         # Everything else — SDLinit, database, uinter classes
├── app.py            # Python hand gesture recognition (runs as subprocess)
├── font.ttf          # Font used for all UI text rendering
├── state.txt         # Shared IPC file written by app.py, read by C++
└── assets/           # Sprites: bank types, managers, map tiles, animations
```
 
---
 
## 🚀 Getting Started
 
### Prerequisites
 
**C++ side:**
```bash
# Ubuntu / Debian
sudo apt install libsdl2-dev libsdl2-ttf-dev libsdl2-image-dev libsdl2-gfx-dev libsqlite3-dev
 
# NFD (Native File Dialog Extended)
# https://github.com/btzy/nativefiledialog-extended
```
 
**Python side:**
```bash
pip install mediapipe opencv-python
```
 
### Build
 
```bash
g++ main.cpp -o bankapp \
  -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_gfx \
  -lsqlite3 -lnfd \
  -std=c++17
```
 
### Run
 
```bash
./bankapp
```
 
On launch, a native file dialog will prompt you to open a `.db` file. The app will then initialize the world map with all banks loaded from that database.
 
The hand gesture module is spawned automatically as a background subprocess when triggered from the UI.
 
---
 
## ✋ Gesture Controls
 
The Python module (`app.py`) runs for ~3 seconds, samples your webcam, and writes a gesture state to `state.txt`:
 
| Gesture | Value | Meaning |
|---|---|---|
| ✊ Closed fist | `0` | Closed |
| 🖐️ Open hand | `1` | Opened |
| ✌️ Peace sign | `2` | Peace |
 
The C++ app reads this file to determine which action to perform.
 
---
 
## 🗺️ UI Modes
 
The app uses an integer `mode` variable to route between screens:
 
| Mode | Screen |
|---|---|
| `-2` | Loading / splash |
| `-1` | Main world map |
| `1` | Add new bank (details form) |
| `11` | Select manager (cutscene) |
| `12` | Place bank on map |
| `13` | Confirm & save |
| `22` | Lock bank screen |
 
Floating popup windows (search, delete, news) animate in and out over the map without leaving it.
 
---
 
## 🎨 Art & Animation
 
- Bank sprites have **green (profit)** and **red (loss)** animated variants using a 6×6 spritesheet sampler
- Manager selection triggers a **142-frame cutscene** per manager character
- Popup windows **slide in from the bottom** with a smooth animation system driven by SDL ticks
---
 
## ⚠️ Known Quirks
 
- `tinyfiledialogs` was dropped mid-development — it caused SDL freezes during blocking file dialogs. NFD replaced it.
- `app.py` uses a hardcoded 3-second timeout per invocation — it's not a persistent service.
- `state.txt` is plain-file IPC. Works, not pretty.
- God classes. One header file. No regrets.
---
 
## 📄 License
 
not yet
 
---
 

