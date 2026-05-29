# 🏦 bank system

A fully interactive desktop banking simulation built with **C++**, **SDL2**, and **SQLite3**.

This project combines:

* real-time rendering,
* database management,
* custom UI systems,
* texture animation,
* event-driven architecture,
* and interactive world navigation

into a complete banking management experience.

---

# 📸 Preview

> Interactive banking interface with:

* draggable world map
* animated bank entities
* database-backed persistence
* dynamic UI windows
* cutscenes and sprite animations
* gesture-based security systems

---

# ✨ Features

## 🌍 Interactive World Map

* Smooth draggable navigation
* Keyboard movement controls
* Dynamic viewport rendering
* Overview mode
* Real-time animated bank rendering
* Coordinate-based placement system

Banks are positioned dynamically using normalized world coordinates.

---

## 🏦 Bank Management

Create and manage banks with:

* Name
* Interest rates
* Funds
* Client count
* Manager assignment
* Bank category
* World coordinates
* Lock state
* Signature state

All data is persisted using SQLite.

---

## 👤 Manager System

Interactive manager selection system with:

* unique visuals
* animated assets
* presentation interfaces
* manager-specific displays

---

## 🎞️ Animation Engine

Custom SDL2 animation system featuring:

* sprite-sheet animations
* frame-based playback
* animated UI elements
* dynamic texture rendering
* animated bank indicators
* fullscreen cutscenes

---

## 🖱️ Advanced Input System

Custom-built interaction systems including:

* drag detection
* click handling
* viewport movement
* modal UI windows
* interactive forms
* dynamic focus handling

---

## 🔐 Gesture-Based Security

Experimental bank locking system using:

* external recognition scripts
* gesture state detection
* signature validation
* lock persistence

---

## 🗄️ SQLite Integration

Persistent storage system supporting:

* bank creation
* deletion
* searching
* updates
* lock management
* dynamic loading

---

# 🧱 Tech Stack

| Technology         | Purpose             |
| ------------------ | ------------------- |
| C++                | Core application    |
| SDL2               | Rendering & input   |
| SDL_ttf            | Font rendering      |
| SDL_image          | Texture loading     |
| SQLite3            | Database system     |
| Native File Dialog | File importing      |
| SDL2_gfx           | Graphics primitives |

---

# 📂 Project Structure

```bash
.
├── assets/              # Textures, sprites, maps, cutscenes
├── main.cpp             # Application entry point
├── headers.h            # Core systems and implementation
├── font.ttf             # UI font
├── app.py               # Gesture recognition script
├── state.txt            # Recognition output state
└── database.db          # SQLite database
```

---

# 🚀 Getting Started

## Requirements

Install:

* SDL2
* SDL2_image
* SDL2_ttf
* SDL2_gfx
* SQLite3
* Native File Dialog (NFD)

---

## Build

```bash
g++ main.cpp -o banksim \
-lSDL2 \
-lSDL2_ttf \
-lSDL2_image \
-lSDL2_gfx \
-lsqlite3
```

---

# ▶️ Running

```bash
./banksim
```

After launching:

1. Import an SQLite database
2. Navigate the world map
3. Create and manage banks
4. Explore animations and interactions

---

# 🧠 Architecture Highlights

## Custom UI Framework

The project implements a fully custom UI system including:

* buttons
* text fields
* animated panels
* modal windows
* focus management
* rendering layers

without relying on external GUI frameworks.

---

## Rendering Pipeline

The rendering system handles:

* texture batching
* viewport calculations
* animated sprites
* fullscreen overlays
* transparency effects
* dynamic texture switching

---

## Database Layer

SQLite is integrated directly through prepared statements for:

* efficient queries
* persistence
* runtime loading
* bank synchronization

---

# 📌 Notable Challenges

### Real-Time Drag System

Implementing smooth drag-based navigation while maintaining viewport constraints and interactive elements.

### Animation Management

Handling hundreds of animation frames efficiently using SDL textures.

### UI State Management

Managing multiple interaction states, windows, overlays, and gameplay modes simultaneously.

### Persistent World Rendering

Synchronizing world-space coordinates with viewport transformations and database persistence.

---

# 🛠️ Development Notes

This project was built as a large-scale experimentation in:

* graphics programming,
* low-level UI systems,
* database integration,
* and interactive application architecture.

A major focus of development was learning through implementation rather than relying on prebuilt frameworks.

---

# 📄 License

This project is available under the MIT License.

---

# ⭐ Repository Goals

This repository showcases:

* low-level C++ application development
* custom rendering systems
* real-time interaction design
* SDL2-based architecture
* database-driven desktop applications
* experimental UI engineering

---

### Main Entry Point

`main.cpp` initializes SDL, database systems, and the UI event loop. 
