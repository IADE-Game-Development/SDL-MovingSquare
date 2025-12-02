# SDL-MovingSquare

# 🧪 SDL3 Installation
1. Install **SDL3** and the necessary build tools.  
2. Verify installation with a small test program.  
3. Compile your existing game using **Make** or **CMake**.

No manual downloads — everything comes from trusted package managers.

---

## 🧰 1. Prerequisites

You’ll need:
- A **C compiler** (`clang` on macOS, `gcc` on Windows via MSYS2)
- **Make** (to build with `make`)
- **CMake** (for cross-platform builds)
- **SDL3** (for graphics, input, and window management)

---

## 🍎 macOS Setup

#### 1.1 Install Xcode Command Line Tools
```bash
xcode-select --install
```
This installs the **clang** compiler and essential developer tools.

#### 1.2 Install Homebrew (package manager)
If you don’t have it yet:
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

Restart the terminal, then verify:
```bash
brew --version
```

#### 1.3 Install Make, CMake, pkg-config and SDL3
```bash
brew update
brew install make cmake pkg-config sdl3 sdl3_image
```

> You can now run both `make` and `cmake` from the terminal.


Verify SDL installation:
```bash
pkg-config --modversion sdl3
```

---

## 🪟 Windows Setup (MSYS2 MinGW64)

> ⚠️ Always use the **MSYS2 MinGW64 terminal**, not “MSYS” or “UCRT”.

#### 2.1 Update MSYS2
```bash
pacman -Syu
```
If asked to close the terminal, do so, reopen **MSYS2 MinGW64**, and run again.


#### 2.2 Install GCC, Make, CMake, pkg-config and SDL3
```bash
pacman -S make cmake mingw-w64-x86_64-pkg-config mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-ninja mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-sdl3 mingw-w64-ucrt-x86_64-sdl3-image
```

---

## 🧱 3. Compile and run the test

use `make run`