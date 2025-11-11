#!/bin/bash

# Comanda de compilare completă
g++ ./source/main.cpp \
    ./source/Core/Game.cpp \
    ./source/Core/Window.cpp \
    ./source/Core/RenderSystem.cpp \
    ./source/Core/MovementSystem.cpp \
    ./source/Core/AnimationSystem.cpp \
    ./source/Core/MapLoader.cpp \
    ./source/Core/Shader.cpp \
    ./source/Core/Mesh.cpp \
    ./source/Core/Texture.cpp \
    ./source/Core/Timer.cpp \
    ./vendor/glad.c \
    -Iinclude -lglfw -ldl -lGL -lX11 -lpthread -o main && ./main