# CPPND: Capstone Snake Game Submission

This repo is a fork for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

<img src="snake_game.gif"/>

## Changes from the example repo:

This build now asks for the "player 1" name. Full on dynamic addition of players was not added.

A leaderboard is maintained between runs by writing to and reading from a local hidden file.

The game now doesn't run until a direction is input by the user.

The background now prints a waiting, and game over, text overlay.

A rectangular CSV map file can be loaded. It must consist of rows with newlines E.g. "0,0,0,1,0,0,0" where each number is a type of tile.

0 = default floor tile, 1 = food tile. See "testMap.smap" for example map.

## File and Class structure

### File tree

* .vscode           (added as part of visual studio code ide)
  * tasks.json
  * c_cpp_properties.json
  * settings.json
* CODEOWNERS
* CMakeLists.txt    (modified to add SDL2 find tweak and additional cpp files)
* emptyMap.smap     (example empty map to show that food is still generated)
* LICENSE.md
* README.md         (modified - this file)
* snake_game.gif
* src
  * controller.cpp   
  * controller.h     
  * DejaVuSans.ttf   (added - font used for start and death text)
  * game.cpp         (modified - kInitial support for snake pass, MapTile support)
  * game.h           (modified - kInitial support for snake pass, MapTile support)
  * global_share.h   (added - holder for some global vars, E.g. flag to pass snake at start)
  * LeaderBoard.cpp  (added - leaderboard file load/save)
  * LeaderBoard.h    (added - leaderboard file load/save)
  * MapLoader.hpp    (added - factory to load map into MapTile objects)
  * MapLoader.cpp    (added - factory to load map into MapTile objects)
  * MapTile.cpp      (added - tile objects to allow map load and multiple food)
  * MapTile.hpp      (added - tile objects to allow map load and multiple food)
  * main.cpp         (modified - map load, user settings, leaderboard)
  * main.hpp         (modified - map load, user settings, leaderboard)
  * renderer.cpp     (modified - vector of food support)
  * renderer.h       (modified - vector of food support)
  * snake.cpp        (added - kInitial for pause at start)
  * snake.h          (added - kInitial for pause at start)
* testMap.smap       (example map with good values, and other unused numbers to show they are ignored)

### Class structure (changes from fork base)

* MapLoader
  * MapLoader::Load
    * Generated MapTiles and appends to a vector

* MapTile
  * Per map tile (grid) object
  * Getters and Setters for each member variable
  * Only created for non default tiles. E.g. Any non floor tile. If no entry is found, then the tile is assumed to be a floor tile.
  * Data members:
    * x_    : x position of tile        (default 0)
    * y_    : y position of tile        (default 0)
    * ttl_  : Time To Live in seconds   (default to -1)
    * perm_ : Permanent flag            (default depends on lookup of tiletype)

* Leaderboard
  * LeaderBoard(const std::string &filePath);
    * Loads the contents from the file if available
    * Generates a paired list of names and scores
  * void setName(std::string newName);
    * set the player name for a given entry
  * std::string getName();
    * get the player name for the given entry
  * void setScore(unsigned int newScore);
    * set the player score for the given entry
  * unsigned long getScore();
    * get the player score for the given entry
  * void addPlayer(std::string name, unsigned long score);
    * add a new entry to the list of player scores
  * void printScores(std::string const playerName);
    * print all scores loaded, and highlight the target playerName ( prefix a lot of "<|" to make the name stand out)
  * void printScores();
    * print all scores loaded
  * void saveScores(std::string filePath);
    * commit the list to the target file, overwrites if the file exists
  * void loadScores(std::string filePath);
    * load the target file if available

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

## Further Ideas

Multiplayer - multiple users all running their own snake on a single keyboard. (Currently at the back due to the size of the work).

More food types - Different colours to represent different food, E.g. big food, gives more size, poison food, slows snake, anti-food, reduce snake size. (a list of types rather than just single food check entry)

Add barriers - walls that have to be navigated around. (just treat them as stationary bits of snake)

Powerups - E.g. magnetic head to attract food. (An extension of same work that "more food types" would require)

Enemy AI - another snake attempting to eat the food before you. (similar to multiplayer)

Mutex controlled thread for Renderer. (potentially a lot of quirks to make it safe)

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
