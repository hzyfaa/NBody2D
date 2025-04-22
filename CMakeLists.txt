cmake_minimum_required(VERSION 3.28)
project(NBody LANGUAGES CXX)

# Set output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Use C++20 (you can drop to 17 if you prefer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch SFML 2.6.x
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Grab all source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Create executable
add_executable(NBody ${SOURCES})

# Include the header files
target_include_directories(NBody PRIVATE include)

# Link SFML
target_link_libraries(NBody PRIVATE sfml-graphics sfml-window sfml-system)
