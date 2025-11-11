#!/bin/bash

# Comanda de compilare completă
g++ ./source/main.cpp \
    ./source/Core/Game.cpp \
    ./source/Graphics/Window.cpp \
    ./source/Systems/RenderSystem.cpp \
    ./source/Systems/MovementSystem.cpp \
    ./source/Systems/AnimationSystem.cpp \
    ./source/Core/MapLoader.cpp \
    ./source/Graphics/Shader.cpp \
    ./source/Graphics/Mesh.cpp \
    ./source/Graphics/Texture.cpp \
    ./source/Core/Timer.cpp \
    ./vendor/glad.c \
    -Iinclude -lglfw -ldl -lGL -lX11 -lpthread -o main && ./main