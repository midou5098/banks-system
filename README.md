# Bank System

A custom desktop bank management system built in C++ with SDL2, SQLite, and a Python computer-vision gesture module. The application renders its own UI, displays a pannable world map, stores bank records in SQLite, and can trigger actions from webcam hand gestures.

## Overview

This project is a full SDL2 desktop application rather than a traditional GUI-framework app. It combines:

- A hand-built SDL interface.
- SQLite persistence for bank records.
- A draggable map with bank placement.
- Animated bank and manager assets.
- Native database file selection.
- Python/OpenCV/MediaPipe gesture recognition connected to the C++ app through a small text-file bridge.

## Features

- Pannable 3840x2160-style world map assembled from image tiles.
- Multiple bank categories with distinct sprites and visual states.
- Add, search, modify, delete, and lock bank records.
- Manager selection flow with cutscene assets.
- Profit/loss visual variants for bank sprites.
- SQLite database loading through Native File Dialog.
- Simple file-based IPC between C++ and Python via `state.txt`.
- Webcam gesture detection for closed hand, open hand, and peace sign states.
- Runtime UI modes for loading, map view, add flow, placement, confirmation, and lock screens.

## Tech Stack

| Layer | Technology |
| --- | --- |
| Main app | C++17 |
| Rendering/UI | SDL2, SDL2_image, SDL2_ttf, SDL2_mixer, SDL2_gfx |
| Persistence | SQLite3 |
| Native file dialog | NFD / Native File Dialog |
| Gesture detection | Python, OpenCV, MediaPipe |
| Build helper | Makefile |

## Project Structure

```text
.
|-- main.cpp              # SDL event loop and mode routing
|-- headers.h             # UI, database, rendering, map, and interaction logic
|-- app.py                # MediaPipe hand gesture detector
|-- Makefile              # Build command for the C++ app
|-- state.txt             # Runtime gesture bridge written by Python and read by C++
|-- sign.txt              # Runtime signature/lock state data
|-- query.sql             # SQL helper/query file
|-- databases/
|   |-- banks.sqlite      # Bank data database
|   `-- clients.sqlite    # Client data database
|-- assets/               # Bank sprites, map tiles, UI textures, cutscenes
|-- output/main           # Existing compiled binary artifact
`-- font.ttf              # UI font
```

## Database Shape

The C++ app expects a `banks` table with fields matching the query in `database::loadbanks()`:

| Field | Meaning |
| --- | --- |
| `name` | Bank name. |
| `type` | Bank category/type id. |
| `interest` | Interest rate value. |
| `funds` | Available funds. |
| `clients` | Client count. |
| `manager` | Selected manager id. |
| `x`, `y` | Map placement coordinates. |
| `lock` | Lock status. |
| `sign` | Lock signature. |

## Build

Install dependencies on Ubuntu/Debian:

```bash
sudo apt install build-essential pkg-config libsdl2-dev libsdl2-image-dev \
  libsdl2-ttf-dev libsdl2-mixer-dev libsdl2-gfx-dev libsqlite3-dev \
  libgtk-3-dev python3-pip
```

Install the Python gesture dependencies:

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

```bash
./output/main
```

On startup, the app opens a native file dialog for selecting a `.db` database file. Run from the repository root so assets, fonts, databases, and `state.txt` resolve correctly.

To test the gesture detector separately:

```bash
python3 app.py
```

## Gesture Bridge

`app.py` samples the webcam for a short interval and writes one of these values to `state.txt`:

| Gesture | Value |
| --- | --- |
| Closed hand | `0` |
| Open hand | `1` |
| Peace sign | `2` |
| Detector finished/reset | `x` |

The SDL application reads that file and maps the value into UI behavior.

## Runtime Modes

The app uses integer modes internally to move through workflows:

| Mode | Screen / behavior |
| --- | --- |
| `-2` | Loading/splash flow. |
| `-1` | Main world map. |
| `1` | Add-bank details form. |
| `11` | Manager selection/cutscene flow. |
| `12` | Bank placement on the map. |
| `13` | Confirm and save. |
| `22` | Bank locking flow. |

## Implementation Notes

Most code currently lives in `headers.h`, including the database layer, SDL wrapper, UI renderer, map logic, and interaction handlers. This keeps the prototype compact and easy to inspect. A future refactor could split it into `database`, `ui`, `map`, `assets`, and `gesture` modules.

## Known Limitations

- The app uses plain-file IPC instead of sockets, pipes, or shared memory.
- Database schema validation is minimal.
- UI layout is fixed for a 1280x720 window.
- Several generated binaries and local `.db` files are committed as project artifacts.
- Camera recognition depends on lighting, webcam availability, and MediaPipe compatibility.

## License

No license file is currently included. Add one before distributing or reusing the project publicly.
