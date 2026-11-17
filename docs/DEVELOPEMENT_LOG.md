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
## Milestone 1: Directory Listing Module

**Status:** Completed and tested

### Implementation
- Created DirectoryEntry structure to store entry names and types.
- Implemented list_directory() function.
- Used POSIX APIs:
  - opendir() to open directories.
  - readdir() to read directory entries.
  - stat() to retrieve entry metadata.
  - closedir() to close directory streams.
- Skipped "." and ".." entries.
- Added error handling for directory-opening failures.

### Testing
- Created tests/test_directory.cpp.
- Successfully compiled and executed the test.
- Verified that files and directories are identified correctly.
- Tested against the LYNX project directory.

**Result:** Directory listing functionality works successfully.
## Milestone 2: Directory Navigation

**Status:** Completed and tested

### Implementation
- Created Navigator class.
- Implemented current directory tracking.
- Implemented navigation into subdirectories.
- Added relative and absolute path support.
- Implemented parent directory navigation.
- Added validation for invalid directory paths.
- Used C++17 std::filesystem.

### Testing
- Created tests/test_navigation.cpp.
- Verified current directory retrieval.
- Tested navigation into src.
- Tested parent directory navigation.
- Tested invalid directory handling.

**Result:** All navigation tests passed successfully.
## Milestone 3: File Metadata Management

**Status:** Completed and tested

### Implementation
- Created FileMetadata structure.
- Implemented get_file_metadata().
- Used Linux lstat() to retrieve filesystem metadata.
- Identified regular files, directories, symbolic links and special files.
- Retrieved file sizes in bytes.
- Converted permission bits into readable Linux permission strings.
- Retrieved last modification timestamps.

### Testing
- Created tests/test_metadata.cpp.
- Tested README.md and CMakeLists.txt.
- Tested src and include directories.
- Verified file types, sizes, permissions and timestamps.

**Result:** All four metadata tests passed successfully.
## Milestone 4: File Operations

**Status:** Implemented and tested

### Implementation
- Created FileOperations class.
- Implemented file creation using open().
- Implemented directory creation using mkdir().
- Implemented renaming using rename().
- Implemented file copying using read() and write().
- Implemented moving using rename() with a cross-filesystem
  fallback for regular files.
- Implemented file deletion using unlink().
- Implemented empty directory deletion using rmdir().
- Added error handling using errno and strerror().

### Testing
- Created tests/test_file_operations.cpp.
- Tested all seven file operations.
- Verified renamed file existence.
- Verified original filename removal.
- Verified copied file movement and deletion.
- Verified empty directory deletion.
- Temporary test files cleaned up.

**Result:** All verification checks passed.
## Milestone 5: Normal Mode User Interface

**Status:** Implemented and tested

### Implementation
- Created modular Terminal UI.
- Implemented LYNX welcome banner and menus.
- Created Application controller.
- Integrated Normal Mode with the main application.
- Implemented directory listing and navigation.
- Integrated file metadata retrieval.
- Integrated all seven file operations.
- Added input validation and error handling.

### Testing
- Tested main menu navigation.
- Tested directory listing and nested navigation.
- Tested parent directory navigation.
- Tested file and directory metadata.
- Tested invalid directory handling.
- Tested all file operations using a temporary workspace.

**Result:** All reported Normal Mode tests passed.
## Milestone 6: Command Mode

**Status: Completed and tested**

Implemented an interactive command-line interface for managing files and directories in LYNX.

### Features Implemented
- `help` – Displays available commands.
- `pwd` – Displays the current working directory.
- `ls` – Lists directory contents.
- `cd` – Navigates between directories.
- `mkdir` – Creates directories.
- `touch` – Creates files.
- `rename` – Renames files and directories.
- `copy` – Copies files.
- `move` – Moves files and directories.
- `delete` – Deletes files.
- `rmdir` – Deletes empty directories.
- `du` – Calculates directory size recursively.
- `sysinfo` – Displays Linux system information.
- `exit` – Exits Command Mode.

### Additional Improvements
- Added support for filenames and directory names containing spaces using quotation marks.
- Added basic command argument validation and error messages.
- Integrated Command Mode with the main LYNX application.

### System Interfaces and Concepts
- C++ filesystem library
- Linux `uname()` system call interface
- Directory traversal using `std::filesystem`
- Command parsing and argument handling

### Testing
- Tested basic commands and navigation.
- Tested file and directory creation, renaming, copying, moving and deletion.
- Tested filenames containing spaces.
- Tested disk usage and system information commands.
- Successfully built the complete project using CMake.

**Outcome:** Command Mode is integrated into LYNX and its implemented features have been tested successfully.
