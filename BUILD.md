---

# Build Instructions

This document describes the required dependencies and how to build the project.

---

## Requirements

### Build Tools
- GCC
- Make
- pkg-config (recommended)

### Libraries
- OpenGL
- GLFW
- OpenAL
- libsndfile
- stb_image (header-only)

---

## Ubuntu / Debian

Install build tools and system libraries:

```bash
sudo apt update
sudo apt install \
    build-essential \
    pkg-config \
    libgl1-mesa-dev \
    libglfw3-dev \
    libopenal-dev \
    libsndfile1-dev
```

---

## Building

**To build the project, you have some alternatives:**

to build the project as debug:
```bash
make
```

to build the project as release:
```bash
make release
```

to build the documentation:
```bash
make doc
```

to build the .deb installer:
```bash
make deb
```

to install fireset to the system (Ubuntu/Debian only):
```bash
make install
```

to uninstall fireset from the system (Ubuntu/Debian only):
```bash
make uninstall
```

to clear all build files:
```bash
make clean
```

---
