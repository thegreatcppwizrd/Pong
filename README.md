# Pong

A simple two-paddle Pong game built with C++ and [raylib](https://www.raylib.com/).

## How to play

- Use the **Up** and **Down** arrow keys to move the right paddle.
- The left paddle is controlled by the computer.
- Score by getting the ball past the computer paddle.
- Close the game window to quit.

![Pong gameplay](assets/pong-gameplay.gif)


# Requirements

Git

CMake 3.22 or newer

Visual Studio 2022 or newer with the Desktop development with C++ workload, including MSVC and Windows SDK

Ninja (included with Visual Studio's CMake tools, if configured)

Dependencies: raylib 6.2 is included in this repository under thirdParty/raylib-6.2. You do not need vcpkg or a separate raylib installation.

Getting Started

1. Clone the repository

Open a terminal and run:

git clone https://github.com/YOUR-USERNAME/YOUR-REPOSITORY.git
cd YOUR-REPOSITORY

Replace the URL with your repository's actual GitHub URL.

2. Configure the project

From the repository root, run:

cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release

This configures the project and generates the build files in the build directory.

3. Build the game

cmake --build build

4. Run the game

On Windows, run:

.\build\main1.exe

If your CMake executable target has a different name, replace main1.exe with the executable's actual name.

# Getting Updates

If you have already cloned the repository, open a terminal in the project directory and run:

git pull

Then rebuild the game:

cmake --build build

Run the executable again to play the updated version.
