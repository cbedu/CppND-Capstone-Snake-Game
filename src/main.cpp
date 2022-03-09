#include "main.hpp"

bool global_waitingOnPlayers = true;

// Class to hold tile information
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
class MapLoader {
  public:
  MapLoader(){}

  bool static Load(std::vector<MapTile> &tiles, std::string &mapFilePath, size_t &height, size_t &width)
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
  }
};

int main(int argc, char * argv[]) {
  std::string garbage;
  std::string leaderboardFile{"./.myLeaderboard.txt"};
  std::string levelFileName;
  int numPlayers{1};
  bool loadingMapFile{false};
  bool mapFileLoaded{false};
  unsigned int scale{0};
//  tileMap barrierMap;
//  std::unqie_ptr<tileMap> barrierMap = std::make_unique<tileMap>
//  std::shared_ptr<tileMap> barrierMap(new tileMap);
  std::future<bool> ftr_barrierMapLoaded;
  bool barrierMapLoaded{false};
  //std::vector<std::vector<MapTile>> tileList(kTileTypes);
  std::vector<MapTile> tileList;

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  //constexpr std::size_t kScreenWidth{640};
  //constexpr std::size_t kScreenHeight{640};
  

  // Get level if set by user
  // https://stackoverflow.com/questions/52467531/using-getopt-in-c-to-handle-arguments
  for(;;)
{
  switch(getopt(argc, argv, "l:x:y:s:h")) // matches order of case entries
  {
    case 'l':
      levelFileName = optarg;
      std::cout << "Level path " << levelFileName << " specified.\n";
      loadingMapFile = true;
      continue; // sidesteps break at end of for block
    
    case 'x':
      try{
        kGridWidth = std::stoi(optarg);
      }
      catch(std::invalid_argument const& ex)
      {
        std::cout << "Bad width [-x] argument.\n";
        return -1;
      }
    continue;

    case 'y':
      try{
        kGridHeight = std::stoi(optarg);
      }
      catch(std::invalid_argument const& ex)
      {
        std::cout << "Bad height [-y] argument.\n";
        return -1;
      }
    continue;

    case 's':
      try{
        scale = std::stoi(optarg);
      }
      catch(std::invalid_argument const& ex)
      {
        std::cout << "Bad height [-s] argument.\n";
        return -1;
      }
    continue;

    case '?':
    case 'h':
      std::cout << "./Snake [-l \"path\"] [-x #] [-y #]\n";
      std::cout << "-h                       \tPrints this help text\n";
      std::cout << "-l \"path_to_level_file\"\tLoads game with optional level file. Automatically adjusts game size to level size.\n";
      std::cout << "-x                       \tWidth of level in grid blocks. Overridden by -l\n";
      std::cout << "-y                       \tHeight of level in grid blocks. Overridden by -l\n";
      std::cout << "\nPlayer1 controls: ArrowKeys = Up Down Left Right\n";
//      std::cout << "General controls in game:\n";
//      std::cout << "r - reset game with existing settings\n";
//      std::cout << "p - print (save) snapshot of current level to 'timestamp'.slevel file";
      std::cout << "\n";
    default :
      break;
  }
  break;
}

if(loadingMapFile == true)
{
  // load the file, then iterate over lines, for each line we append each entry to the inner vector,
  // each line increments the outer vector
  mapFileLoaded = MapLoader::Load(tileList, levelFileName, kGridHeight, kGridWidth);
  
  // adjust our game size to fit the map.
  if(mapFileLoaded == true)
  {
    //kGridHeight = tileList.size();
    //kGridWidth = tileList[0].size();
  }

  std::cout << "Map size is [" << kGridWidth << "," << kGridHeight << "]" << std::endl;
  
  //if no map was loaded then the map is assumed to be all floor tiles
  //the food generation will then kick in and place something regardless.
}

//for(auto tileRow : tileList)
//for(auto tile : tileRow)
for(auto tile : tileList)
//for(auto tile : tileRow)
{
  std::cout << "Tile [" << tile.X() << "," << tile.Y() << "] is of type [" << tile.Type() << "]" << std::endl;
}

if(scale != 0)
{
  kScreenWidth = kGridWidth * scale;
  kScreenHeight = kGridHeight * scale;
}

#if 0 // disabled (partial multiplayer testing)
  // Get number of players
  std::cout << "\nEnter number of players (Max : 1): "; // <<TODO>> add to command line args
  std::cin >> numPlayers;

  // Avoid cin stuck state on non 'int'
  // https://stackoverflow.com/questions/11523569/how-can-i-avoid-char-input-for-an-int-variable
  while (std::cin.fail() || (numPlayers <= 0)){
    if(numPlayers <= 0)
      std::cout << "\nBad player count. Please enter a valid number.\n";
    std::cin.clear(); // clear input buffer to restore cin to a usable state
    std::cin.ignore(INT_MAX, '\n'); // ignore last input
    std::cin >> numPlayers;
  }
  getline(std::cin, garbage); //purge remaining carriage return
#endif

  std::vector<std::string> players;
  
  // Get player names
  for(int i = 1; i <= numPlayers; i++)
  {
    std::string player;
    std::cout << "\nEnter player " << i++ << "'s name: ";
    getline(std::cin, player);

    players.emplace_back(player);
  }

#if 0
  if(loadingMapFile)
  {
    //async load of mapfile into a unique_ptr for the mapTiles object.
    ftr_barrierMap = std::async(loadBarrierMap, levelFileName, barrierMap);
  }

  if(loadingMapFile)
  {
    barrierMapLoaded = ftr_barrierMapLoaded.get();
  }
#endif

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);  // map needs to atleast have a size before here
  Controller controller;  // keyboard input control, one instance, can't easily be multiplexed
  Game game(kGridWidth, kGridHeight, std::move(tileList)); // generates game elements
  game.Run(controller, renderer, kMsPerFrame, numPlayers);

  std::cout << "Game has terminated successfully!\n";
  std::cout <<
    //"FinalSize\t: PeakSize\t: " <<
    "Score\t: PlayerName\n";
  
  for(auto player: players)
  {
  //  std::cout << game.GetSize() << "\t: ";
  //  std::cout << game.GetSize() << "\t: ";
    std::cout << game.GetScore() << "\t: ";
    std::cout << player << "\n\n";
  }

// <<TODO>> 2 Write out score details to a leaderboard file
//  Will need to sort the list on score
  LeaderBoard scores(leaderboardFile);
  // scores.LoadList(leaderboardFile);
  // This section would need to take the array and move through in multiplayer
  scores.addPlayer(players[0], game.GetScore());
  scores.printScores(players[0]);
  scores.saveScores(leaderboardFile);

  return 0;
}
