#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <vector>
#include <fstream>
#include <sstream>
#include "MapTile.hpp"
#include <algorithm>
#include <iostream>

class MapLoader {
  public:
  MapLoader();

  bool static Load(std::vector<MapTile> &tiles, std::string &mapFilePath, size_t &height, size_t &width);
};

//This is slightly different, it was hosting a 2d array to allow seperate rows for each tile type.
/*
class MapLoader {
  public:
  MapLoader(){}

  bool static Load(std::vector<std::vector<MapTile>> &tiles, std::string &mapFilePath)
  {
    bool processedAnything{false};
    std::string line;
    int tileType{0};
    int x{0};
    int y{0};

    std::ifstream filestream(mapFilePath);
    if (filestream.is_open()) {
      while (std::getline(filestream, line)) {
        std::replace(line.begin(), line.end(), ',', ' ');
        std::istringstream linestream(line);
        while (linestream >> tileType)
        {
          if(tileType != 0)
          {
            std::cout << "Creating tile of type " << tileType << " with position [" << x << "," << y << "]" << std::endl;
            MapTile tempTile = MapTile(tileType, x, y);
            tiles[tileType].emplace_back(tempTile);
          }

          x++; // we processed an element
        }
        x = 0;
        y++; // we have populated a row
      }
    }
    if(y > 0)
      return true;
      
    return false;
  }
};
*/


#endif