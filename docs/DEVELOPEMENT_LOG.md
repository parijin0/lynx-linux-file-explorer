# LYNX — Development Log

This document records the development process of LYNX, including environment configuration, project initialization, implementation milestones, technical decisions and testing activities.

---

## Project Information

| Attribute | Details |
|---|---|
| Project Name | LYNX — Linux File Explorer |
| Programming Language | C++17 |
| Development Environment | Ubuntu Linux ARM64 |
| Virtualization Platform | UTM |
| Build System | CMake |
| Version Control | Git and GitHub |
| Repository | https://github.com/parijin0/lynx-linux-file-explorer |

---

## Milestone 1: Development Environment Setup

**Status:** Completed

### 1.1 Ubuntu Environment

A Linux development environment was configured on an Apple Silicon MacBook using UTM virtualization software.

The following configuration was selected:

- Virtualization platform: UTM
- Guest operating system: Ubuntu Desktop ARM64
- Processor allocation: 4 virtual CPU cores
- Memory allocation: 6 GB
- Virtual disk capacity: 40 GB

Ubuntu was installed successfully inside the virtual machine. The installation ISO was detached after installation to ensure subsequent boots used the installed virtual disk.

### 1.2 Development Tools

The following development tools and libraries were installed:

| Tool | Purpose |
|---|---|
| GCC / G++ | C and C++ compilation |
| Make | Build automation |
| CMake | Project configuration and build management |
| Git | Version control |
| GDB | Debugging |
| clang-format | Code formatting |
| ncurses development library | Terminal interface development |

### 1.3 Environment Verification

The Linux environment was checked using commands including:

```bash
uname -m
lsb_release -a
free -h
df -h
```

The environment was configured for ARM64 Linux development.

---

## Milestone 2: Initial Project Initialization

**Status:** Completed

### 2.1 Project Directory Structure

The initial modular directory structure was created to separate different application responsibilities.

The following directories were established:

- `src/` — application source code.
- `src/ui/` — user interface components.
- `src/filesystem/` — file-system functionality.
- `src/navigation/` — directory navigation.
- `src/search/` — search and filtering functionality.
- `src/storage/` — storage-related functionality.
- `src/utils/` — utility components.
- `include/` — header files.
- `tests/` — test cases.
- `docs/` — project documentation.

### 2.2 CMake Configuration

An initial `CMakeLists.txt` file was created with:

- C++17 language standard.
- C++ extensions disabled.
- Executable target configuration.
- Include directory configuration.
- Compiler warning flags.

### 2.3 Initial Application

An initial `main.cpp` file was created to verify the project structure and build configuration.

The application displays a basic LYNX welcome message.

### 2.4 Initial Build Verification

The project was configured, compiled and executed using:

```bash
cmake -S . -B build
cmake --build build
./build/lynx
```

This established the initial build workflow.

---

## Milestone 3: Git and GitHub Integration

**Status:** Completed

### 3.1 Git Configuration

Git was configured with the developer's identity.

A `.gitignore` file was created to exclude build directories, compiled binaries, temporary files and editor-specific files.

### 3.2 Repository Initialization

The local project was initialized as a Git repository.

The following commands were executed:

```bash
git init
git add .
git commit -m "chore: initialize LYNX project structure"
```

### 3.3 GitHub Integration

A remote GitHub repository was created:

https://github.com/parijin0/lynx-linux-file-explorer

The local repository was connected to GitHub using HTTPS authentication.

The initial branch was renamed to `main`, and the initial commit was successfully pushed.

Commands used:

```bash
git remote add origin https://github.com/parijin0/lynx-linux-file-explorer.git
git branch -M main
git push -u origin main
```

The local `main` branch was configured to track `origin/main`.

---

## Upcoming Development Milestones

The following activities are planned for subsequent development stages.

| Milestone | Planned work | Status |
|---|---|---|
| 4 | README and technical documentation | In progress |
| 5 | Normal Mode implementation | Planned |
| 6 | Directory traversal and navigation | Planned |
| 7 | File metadata and permissions | Planned |
| 8 | Command Mode and command parsing | Planned |
| 9 | File and directory operations | Planned |
| 10 | Search, sorting and filtering | Planned |
| 11 | Storage analysis and system information | Planned |
| 12 | Testing, optimization and final documentation | Planned |

---

## Development Notes

This log will be updated after each significant implementation milestone.

Each entry will record the objective, implementation approach, relevant system interfaces, testing performed, issues encountered and their resolutions.

Only completed and verified functionality will be marked as implemented.

---

*LYNX Development Log — Version 1.0*
