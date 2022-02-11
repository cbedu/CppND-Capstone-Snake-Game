#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <vector>

class LeaderBoard {
 
 public:
  LeaderBoard(const std::string &filePath);
  
  void setName(std::string newName);
  std::string getName();
  
  void setScore(uint32_t newScore);
  unsigned long getScore();

  void addPlayer(std::string name, unsigned long score);
  void printList(std::string const playerName);
  void printList();
  void saveScores(std::string filePath);
  void loadScores(std::string filePath);

 private:
  std::string _name;
  uint32_t _score{0};
  std::vector<std::pair<std::string, uint32_t>> _list;
};

#endif
