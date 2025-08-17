#!/bin/bash

set -e
mkdir -p bin build

# Compile each .cpp file in src/ into build/*.o
for file in src/*.cpp; do
    g++ -c "$file" -o "build/$(basename "${file%.cpp}").o" $(sdl2-config --cflags) -Iinclude
done

# Link all object files into the final executable
g++ build/*.o -o bin/main.exe $(sdl2-config --libs)

# Run the program
./bin/main.exe
