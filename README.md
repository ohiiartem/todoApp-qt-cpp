# todoApp-qt-cpp

A minimalist keyboard-driven to-do application built with C++ and Qt.

## Features

- Full keyboard control, no mouse required
- Tasks persist between sessions via JSON
- Strikethrough toggle for completed tasks
- Inline task editing

## Keyboard Shortcuts

| Key | Action |
|-----|--------|
| `N` | Create new task |
| `Enter` | Confirm task |
| `Esc` | Cancel input |
| `↑` / `↓` | Navigate tasks |
| `Space` | Toggle task complete |
| `E` | Edit selected task |
| `D` | Delete selected task |

## Tech Stack

- **Language:** C++17
- **Framework:** Qt 6
- **Build system:** qmake
- **Storage:** JSON (`tasks.json`)
- **Styles:** QSS

## Building

Open `todoApp-qt-cpp.pro` in Qt Creator and press `Cmd+B`.

## Data

Tasks are saved automatically to `tasks.json` in the app's working directory after every action.
