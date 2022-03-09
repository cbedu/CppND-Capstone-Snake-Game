#include "LeaderBoard.h"

#include <algorithm>  // std::sort
#include <fstream>    // file I/O
#include <sstream>    // istringstream

/**
 * @brief Construct a new Leader Board object
 * 
 * @param filePath required filepath for the leaderboard file. Created at save if not found for load.
 */
LeaderBoard::LeaderBoard(const std::string &filePath)
{
  loadScores(filePath);
}

/**
 * @brief Set the Name of the player entry
 * 
 * @param newName 
 */
void LeaderBoard::setName(const std::string newName)
{
  _name = newName;
}

/**
 * @brief Get the player Name from this entry
 * 
 * @return std::string 
 */
std::string LeaderBoard::getName()
{
  return _name;
}

/**
 * @brief Set the Score of the player entry
 * 
 * @param newScore 
 */
void LeaderBoard::setScore(const unsigned int newScore)
{
  _score = newScore;
}

/**
 * @brief Get the Score of the player entry
 * 
 * @return unsigned long 
 */
unsigned long LeaderBoard::getScore()
{
  return _score;
}

/**
 * @brief Add a player to the leaderboard object to allow inclusion when saving
 * 
 * @param name player name
 * @param score player score
 */
void LeaderBoard::addPlayer(std::string name, unsigned long score)
{
  _list.emplace_back(name, score);
}

/**
 * @brief Output loaded scoreboard, whilst also highlighting the target playername
 * 
 * @param playerName 
 */
void LeaderBoard::printScores(std::string const playerName)
{
  // from system monitor course
  std::sort(_list.begin(), _list.end(),
    [](auto const &left, auto const &right)
    {
      return left.second > right.second;
    });

  std::cout << "Score\t: Name\n";
  for (auto const &player : _list)
  {
    // score first to reduce the amount of indenting control needed.
    // A large score will offset the name if more than \t worth of digits, but less likely.
    std::cout << player.second << "\t: " << player.first;
    if(player.first == playerName)
      std::cout << "<|<|<|<|<|<|<|<|<|<|";

    std::cout << "\n";
  }
}

/**
 * @brief Output loaded scores for all players to console
 * 
 */
void LeaderBoard::printScores()
{
  this->printScores(NULL);
}

/**
 * @brief Commit the new leaderboard to the file specified by filepath
 * 
 * @param filePath 
 */
void LeaderBoard::saveScores(std::string filePath)
{
  // https://www.cplusplus.com/reference/fstream/ofstream/
  std::ofstream saveFile(filePath);

  if (saveFile.is_open())
  {
    for (auto const &player : _list) {
      saveFile << player.first << ":" << player.second << "\n";
    }
    saveFile.close();
  }
}

/**
 * @brief Open and load the scores from a file
 * 
 * @param filePath 
 */
void LeaderBoard::loadScores(std::string filePath) {
  std::ifstream loadFile(filePath);
  std::string line;

  if (loadFile.is_open())
  {
    while (getline(loadFile, line))
    {
      // https://stackoverflow.com/questions/11719538/how-to-use-stringstream-to-separate-comma-separated-strings
      std::istringstream stream(line);
      std::string name;
      std::string temp;
      unsigned int score;

      // ':' used to allow multiple parts to a name
      std::getline(stream, name, ':');
      std::getline(stream, temp, ':');
      
      // Anything other than a good number will abort the program if not caught.
      try{
        score = std::stoi(temp);
        addPlayer(name, score);
      }
      catch(std::invalid_argument const& ex)
      {
        std::cout << "Bad data in leaderboard file. Silently dropping entry.\n";
      }
    }

    loadFile.close();
  }
}
