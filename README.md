# CPPND: Capstone Snake Game Submission

This repo is a fork for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

<img src="snake_game.gif"/>

## Changes from the example repo:


### Added

This build now asks for number of players and their names. Though at the moment only 1 player is running.

A leaderboard is maintained between runs by writing to and reading from a local hidden file.

The game now doesn't run until a direction is input by the user.

The background now prints a waiting, and game over, text overlay.

### Adding

Timeout controlled loss of size of the snake. With the timer being reset by either eating food, or by losing a size block.

### Ideas

Multiplayer - multiple users all running their own snake on a single keyboard. (Currently at the back due to the size of the work).

More food types - Different colours to represent different food, E.g. big food, gives more size, poison food, slows snake, anti-food, reduce snake size.

Add barriers - walls that have to be navigated around.

Levels - load a level map from file that places walls, and initial spawn/food placement.

Powerups - E.g. magnetic head to attract food.

Enemy AI - another snake attempting to eat the food before you.

Mutex controlled thread for Renderer.

## Rubric completed

* The project reads data from a file and process the data, or the program writes data to a file.	The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
  * Loads and Saves leaderboard
* The project accepts user input and processes the input.	The project accepts input from a user as part of the necessary operation of the program.
  * User numbers and names


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
  >SDL_TFF also required and used
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
