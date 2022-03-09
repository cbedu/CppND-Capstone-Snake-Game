#include "MapLoader.hpp"

MapLoader::MapLoader(){};

bool MapLoader::Load(std::vector<MapTile> &tiles, std::string &mapFilePath, size_t &height, size_t &width)
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
        if(tileType == 1)
        {
        std::cout << "Creating tile of type " << tileType << " with position [" << x << "," << y << "]" << std::endl;
        MapTile tempTile = MapTile(tileType, x, y, -1, false);
        tiles.emplace_back(tempTile);
        }

        x++; // we processed an element
    }
    width = x;
    x = 0;
    y++; // we have populated a row
    }
}
if(y > 0)
{
    height = y;
    return true;
}
    
return false;
};
