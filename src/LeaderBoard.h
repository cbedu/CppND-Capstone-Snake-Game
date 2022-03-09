#ifndef SCORES_H
#define SCORES_H

#include <iostream>
#include <vector>

/**
 * @brief Loads, prints and saves a leaderboard file
 * 
 */
class LeaderBoard {
 
 public:
 /**
  * @brief Construct a new LeaderBoard object
  * 
  * @param filePath required filepath for the leaderboard file. Created at save if not found for load.
  */
  LeaderBoard(const std::string &filePath);
  
  /**
   * @brief Set the Name of the player entry
   * 
   * @param newName 
   */
  void setName(std::string newName);

  /**
   * @brief Get the player Name from this entry
   * 
   * @return std::string 
   */
  std::string getName();

  /**
   * @brief Set the Score of the player entry
   * 
   * @param newScore 
   */
  void setScore(unsigned int newScore);

  /**
   * @brief Get the Score of the player entry
   * 
   * @return unsigned long 
   */
  unsigned long getScore();

  /**
   * @brief Add a player to the leaderboard object to allow inclusion when saving
   * 
   * @param name player name
   * @param score player score
   */
  void addPlayer(std::string name, unsigned long score);

  /**
   * @brief Output loaded scoreboard, whilst also highlighting the target playername
   * 
   * @param playerName 
   */
  void printScores(std::string const playerName);

  /**
   * @brief Output loaded scores for all players to console
   * 
   */
  void printScores();

  /**
   * @brief Commit the new leaderboard to the file specified by filepath
   * 
   * @param filePath 
   */
  void saveScores(std::string filePath);

  /**
   * @brief Open and load the scores from a file
   * 
   * @param filePath 
   */
  void loadScores(std::string filePath);

 private:
  std::string _name;
  unsigned int _score{0};

  // couple playerNames and scores for now, to be replaced with class.
  std::vector<std::pair<std::string, unsigned int>> _list;
};

#endif
