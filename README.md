# LYNX — Linux File Explorer

A modular, terminal-based Linux file explorer developed in **C++17**, designed to provide efficient file-system navigation, file management and system-level operations through an interactive command-line interface.

## Overview

LYNX is an Operating Systems project that aims to simplify file-system interaction through two primary operating modes:

- **Normal Mode:** Interactive navigation through directories and files using keyboard-based controls.
- **Command Mode:** Execute file-system operations through a custom command interface.

The project focuses on understanding Linux file-system operations, POSIX system calls, process-level interactions and terminal-based user interface development.

## Objectives

- Develop an interactive Linux file explorer.
- Implement file and directory navigation.
- Perform essential file-management operations.
- Retrieve and display file metadata and permissions.
- Implement search, sorting and filtering functionality.
- Explore disk usage and system information.
- Apply Linux/POSIX system programming concepts.
- Develop a modular and maintainable C++ application.

## Planned Features

| Module | Planned functionality |
|---|---|
| Normal Mode | Interactive directory navigation and file listing |
| Command Mode | Custom command parser and command execution |
| File Management | Create, copy, move, rename and delete files/directories |
| File Metadata | File size, type, permissions and timestamps |
| Search | Search files and directories |
| Sorting & Filtering | Organize entries based on selected attributes |
| Storage Analysis | Disk usage and storage information |
| System Information | Display relevant system-level information |

*These are planned capabilities and will be marked as implemented only after development and testing.*

## Technology Stack

- **Language:** C++17
- **Operating System:** Ubuntu Linux (ARM64 virtual machine)
- **System Interfaces:** Linux/POSIX APIs
- **Build System:** CMake
- **Compiler:** GCC / G++
- **Debugger:** GDB
- **Terminal Interface:** ncurses (planned)
- **Version Control:** Git and GitHub

## Project Structure

```text
LYNX/
├── src/
│   ├── ui/
│   ├── filesystem/
│   ├── navigation/
│   ├── search/
│   ├── storage/
│   └── utils/
├── include/
├── tests/
├── docs/
│   ├── screenshots/
│   ├── diagrams/
│   └── DEVELOPMENT_LOG.md
├── CMakeLists.txt
├── .gitignore
└── README.md
```

## Getting Started

### Prerequisites

- Ubuntu Linux
- GCC / G++
- CMake
- Make
- Git

### Install development dependencies

```bash
sudo apt update
sudo apt install build-essential cmake git gdb clang-format libncurses-dev
```

### Clone the repository

```bash
git clone https://github.com/parijin0/lynx-linux-file-explorer.git
cd lynx-linux-file-explorer
```

### Build the project

```bash
cmake -S . -B build
cmake --build build
```

### Run the application

```bash
./build/lynx
```

## Development Approach

LYNX is being developed incrementally using a modular architecture.

Each module will undergo implementation, compilation, testing and documentation before integration into the complete application.

Git is used to maintain version history and publish development milestones throughout the implementation process.

## Documentation

Additional project documentation is maintained in the `docs/` directory:

- `DEVELOPMENT_LOG.md` — chronological development history.
- `ARCHITECTURE.md` — application architecture and module interactions.
- `SYSTEM_CALLS.md` — Linux/POSIX APIs used in the project.
- `TESTING.md` — test cases and validation results.

## Project Status

**Current stage:** Initial environment setup and project scaffolding completed. Core file-explorer functionality is under development.

## Repository

GitHub: https://github.com/parijin0/lynx-linux-file-explorer

---

*LYNX — Exploring the Linux file system, one operation at a time.*
