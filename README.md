# NBody2D
Interactive 2D N-body simulation built using C++ and SFML featuring velocity Verlet algorithm for stable and accurate motion.

## Requirements
- C++20 compiler (or C++17)
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
- Bodies off-screen are cleaned up
