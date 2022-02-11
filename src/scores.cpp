#include "scores.h"

#include <algorithm>  // std::sort
#include <fstream>    // file I/O
#include <sstream>    // istringstream

LeaderBoard::LeaderBoard(const std::string &filePath)
{
  loadScores(filePath);
}

void LeaderBoard::setName(const std::string newName)
{
  _name = newName;
}

std::string LeaderBoard::getName()
{
  return _name;
}

void LeaderBoard::setScore(const uint32_t newScore)
{
  _score = newScore;
}

unsigned long LeaderBoard::getScore()
{
  return _score;
}

void LeaderBoard::addPlayer(std::string name, unsigned long score)
{
  _list.emplace_back(name, score);
}

void LeaderBoard::printList()
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
    std::cout << player.second << "\t: " << player.first << "\n";
  }
}

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
      uint32_t score;

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
