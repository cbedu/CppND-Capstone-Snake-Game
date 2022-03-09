# CPPND: Capstone Snake Game Submission

This repo is a fork for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

<img src="snake_game.gif"/>

## Changes from the example repo:


### Added

This build now asks for the "player 1" name. Full on dynamic addition of players was not added.

A leaderboard is maintained between runs by writing to and reading from a local hidden file.

The game now doesn't run until a direction is input by the user.

The background now prints a waiting, and game over, text overlay.

A rectangular CSV map file can be loaded. It must consist of rows with newlines E.g. "0,0,0,1,0,0,0" where each number is a type of tile.

0 = default floor tile, 1 = food tile. See "testMap.smap" for example map.

### Further Ideas

Multiplayer - multiple users all running their own snake on a single keyboard. (Currently at the back due to the size of the work).

More food types - Different colours to represent different food, E.g. big food, gives more size, poison food, slows snake, anti-food, reduce snake size. (a list of types rather than just single food check entry)

Add barriers - walls that have to be navigated around. (just treat them as stationary bits of snake)

Powerups - E.g. magnetic head to attract food. (An extension of same work that "more food types" would require)

Enemy AI - another snake attempting to eat the food before you. (similar to multiplayer)

Mutex controlled thread for Renderer. (potentially a lot of quirks to make it safe)

## Target Rubric

* A variety of control structures are used in the project. The project code is clearly organized into functions.
  * MapLoader and MapTiles cpp and hpp files added.
  * Iterator for loop search of vector of custom objects along with selective deletion.
  * User options affect system startup
* The project reads data from a file and process the data, or the program writes data to a file.	The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
  * Loads and Saves leaderboard
* The project accepts user input and processes the input.	The project accepts input from a user as part of the necessary operation of the program.
  * User numbers and names
* The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  * Added MapLoader and MapTile
  * MapLoader contains a static class method as a factory to generate MapTiles and append to a vector
  * MapTile contains all priv data for a single tile object along with getter/setter functions for access
* All class data members are explicitly specified as public, protected, or private.
  * MapTile hides data members behind private, with public facing getter/setter functions
* All class members that are set to argument values are initialized through member initialization lists.
  * MapTile uses numerous initilization lists.
* All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
  * Both MapLoader and MapTile have descriptions for all functions, along with comments on each member variable.
  * Hpp and Cpp files of the added classes have matching comments. Duplication isn't ideal, but my work guidelines have this requirement.
* Appropriate data and functions are grouped into classes. Member data that is subject to an invariant is hidden from the user. State is accessed via member functions.
  * MapTile is isolated to a per tile dataset.
  * MapLoader is a static factory function class that generates MapTile objects and has no other responsibility.
* One function is overloaded with different signatures for the same function name.
  * MapTile has numerous constructors depending on desired function of tiles.
    * TTL and Perm are optional additions that will be defaulted if not included in the object initialization.
    * Though setters are available to modify after creation.
* At least two variables are defined as references, or two functions use pass-by-reference in the project code.
  * MapLoader uses pass by ref to access
    * the std::vector of MapTiles
    * const read only of map filepath
    * modify the grid height and width of the renderer based off the dimensions detected from the loaded map
  * Game is given the vector via an rvalue through std::move

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
5. `./SnakeGame -h` Gives help text


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
