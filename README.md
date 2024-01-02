# Raccoon C++ Game Engine

[![License: Apache-2.0](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

## Introduction

Raccoon is a C++ game engine primarily designed for building 2D games. Although it is currently in development without an official release version, you can already utilize it to create games, especially without the editor. Additionally, it serves as a valuable resource for learning game engine development.

## Features

### 2D Renderer  

While the 2D renderer may not be as multifunctional as desired at this point, Raccoon boasts a fast 2D batch renderer. For optimal performance testing, it is recommended to use Raccoon without the editor, as the editor is still under active development.

### ECS (Entity-Component-System)

Raccoon incorporates an Entity-Component-System architecture developed using entt. The ECS functionality is currently utilized in RaccoonEditor.

## Future Plans

### General  

Raccoon is designed with a primary focus on creating 2D games, with ongoing improvements in mind. Although there may be considerations for simple 3D capabilities in the future, it will not be as powerful as its 2D counterpart.

### Current Plans

The current development phase centers around RaccoonEditor and related functionalities. The primary goal is to establish a Minimum Playable Release (MPR) version, which will then serve as a foundation for further expansion and enhancement.

## Getting Started

### Installing
  
1. Clone the repository:

```bash

git clone https://github.com/OlehDvorychanskyi/Raccoon

```
2. Run RaccoonSetup.exe and install Raccoon on your computer. 
3. Now you can open installed .exe file and use Raccoon or you can go to "Building" section in order to build Raccoon.
    
### Building

1. Make sure CMake and Raccoon are installed on your computer.
2. Run one of the bash scripts to build Raccoon:

```bash

.\build_MinGW_minsize_debug.bat

```
3. Now you can go to "build/MinSizeDebug/bin" and run .exe file. 
