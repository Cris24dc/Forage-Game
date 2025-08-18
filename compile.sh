#!/bin/bash

set -e
mkdir -p bin build

# Compile files inside src/
for file in src/*.cpp; do
    g++ -c "$file" -o "build/$(basename "${file%.cpp}").o" $(sdl2-config --cflags) -Iinclude
done

# Compile main.cpp
g++ -c main.cpp -o build/main.o $(sdl2-config --cflags) -Iinclude

# Link
g++ build/*.o -o bin/main.exe $(sdl2-config --libs)

# Run
./bin/main.exe
