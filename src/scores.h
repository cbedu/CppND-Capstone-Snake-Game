#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <vector>

class LeaderBoard {
 
 public:
  LeaderBoard(const std::string &filePath);
  
  void setName(std::string newName);
  void setScore(unsigned int newScore);
  void saveScores(std::string filePath);
  
  std::string getName();
  unsigned long getScore();
  void loadScores(std::string filePath);

  void printScores(std::string const playerName);
  void printScores();

  void addPlayer(std::string name, unsigned long score);

 private:
  std::string _name;
  unsigned int _score{0};

  // couple playerNames and scores for now, to be replaced with class.
  std::vector<std::pair<std::string, unsigned int>> _list;
};

#endif
