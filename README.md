# todoApp-qt-cpp
A minimalist, keyboard-driven to-do app built with C++ and Qt 6. No mouse. No clutter. Just tasks.

## Overview
todoApp is a desktop productivity tool designed around a single principle: your hands never leave the keyboard. Built as a personal project to learn C++ and Qt simultaneously.

## Features
- Full keyboard navigation — zero mouse required
- Tasks persist between sessions via JSON
- Inline editing with live text input
- Strikethrough toggle for completed tasks
- Hide / show completed tasks
- Task reordering via keyboard
- Clean off-white UI with QSS styling
- Custom Roboto font embedded via Qt resources

## Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `N` | Create new task |
| `Enter` | Confirm / save task |
| `Esc` | Cancel input |
| `↑` / `↓` | Navigate tasks (circular) |
| `Cmd+↑` / `Cmd+↓` | Move task up / down |
| `Space` | Toggle complete (strikethrough) |
| `E` | Edit selected task |
| `D` | Delete selected task |
| `H` | Hide / show completed tasks |

## Download
Grab the latest `.dmg` from [Releases](https://github.com/ohiiartem/todoApp-qt-cpp/releases) — no Qt installation required.

## Tech Stack

| | |
|---|---|
| Language | C++17 |
| Framework | Qt 6 |
| Build system | qmake |
| Storage | JSON |
| Styles | QSS (Qt Style Sheets) |

## Building from Source

**Requirements**
- Qt 6.x
- Qt Creator (recommended) or any C++ build environment with qmake

**Steps**
```bash
git clone https://github.com/ohiiartem/todoApp-qt-cpp.git
cd todoApp-qt-cpp
```
Open `todoApp-qt-cpp.pro` in Qt Creator and press `Cmd+B` (macOS) or `Ctrl+B` (Windows/Linux).

## Data Storage
Tasks are saved automatically after every action (create, edit, delete, toggle). No manual save needed.

- **macOS:** `~/.config/todoApp/tasks.json`
- **Windows:** `%APPDATA%/todoApp/tasks.json`

```json
{
  "tasks": [
    { "text": "Buy milk", "completed": false },
    { "text": "Finish homework", "completed": true }
  ]
}
```

## Project Structure
```
todoApp-qt-cpp/
├── main.cpp              # Entry point, loads font & QSS
├── mainwindow.h/.cpp     # UI logic, state machine, keyboard handling
├── taskmanager.h/.cpp    # JSON save/load
├── style.qss             # App-wide styles
├── resources.qrc         # Embedded fonts & styles
└── fonts/
    └── Roboto-Regular.ttf
```

## Status
**v1.5** — keyboard shortcuts complete, standalone `.dmg` available.

Planned for v2.0:
- SQLite storage + MVC architecture
- Task priorities (High / Medium / Low)
- Updated UI / UX

## About
Built by **@ohiiartem** as a learning project — C++ and Qt from scratch.
