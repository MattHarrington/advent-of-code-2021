# advent-of-code-2021

Advent of Code 2021 solutions in C++

1. Install a C++ compiler, **cmake**, and [vcpkg](https://github.com/microsoft/vcpkg)
2. Clone this repo. Change into a day's directory.
3. Run `cmake -B [build directory] -S . -DCMAKE_TOOLCHAIN_FILE="[path to vcpkg]/scripts/buildsystems/vcpkg.cmake"`. Common choices for `[build directory]` are `build` or `out`. **cmake** will create the directory if it doesn't exist.
4. Run `cmake --build [build directory]`
5. Run the executables in `[build directory]`. Make sure the `*.txt` input files can be found.
