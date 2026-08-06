# tstype (tons type)
tstype is a very simple text editor. It`s a beta version of the program

## Features
* **Hotkeys:**
  * `Ctrl + O`: Open an existing file.
  * `Ctrl + S`: Save the current file.

## Requirements

To build and run this application, you will need:
* A C++17 compatible compiler (e.g., GCC or Clang)
* CMake (version 3.16 or higher)
* Qt6 (Widgets module)

* ## How to Build

If you want to compile the project manually from source, run the following commands in your terminal:

```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build
```
After a successful build, you can find the executable inside the `build` directory:
```bash
./build/tstype
```
