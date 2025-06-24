# NBody2D
Interactive 2D N-body simulation built using C++ and SFML

## Demo
![demo](https://github.com/user-attachments/assets/4f4e8fec-2629-4c4c-adc3-06545ae2ecf2)

## Features
- Barnes-Hut algorithm for efficient gravitational force computation
- Velocity Verlet integration for stable and accurate motion
- Collisions
- Interactive body spawning

## Requirements
- C++20 (or C++17)
- SFML 2.6.x (fetched via CMake)
- CMake 3.28 or later

## Installation

1. Clone repo

    ```
    git clone https://github.com/hzyfaa/NBody2D.git
    cd Nbody2D
    ```
2. Create build directory

    ```
    cmake -B build -S .
    ```
    
3. Build project

    ```
    cmake --build build
    ```
    
4. Run

    ```
    ./build/bin/NBody
    ```

## Usage
- Hold left click + drag: spawn body and draw vector
- Release mouse: launch body
