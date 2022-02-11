#include <iostream>
#include "controller.h"
#include "game.h"
#include "scores.h"
#include "renderer.h"
#include "global_share.h"
#include <climits>

bool global_waitingOnPlayers = true;

int main() {
  std::string garbage;

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  //constexpr std::size_t kScreenWidth{640};
  //constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  std::string kFile{"./.myLeaderboard.txt"};

  int numPlayers;

  std::cout << "\nEnter number of players (Max : 1): ";
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
  
  std::vector<std::string> players;

  for(int i = 1; i <= numPlayers; i++)
  {
    std::string player;
    std::cout << "\nEnter player " << i++ << "'s name: ";
    getline(std::cin, player);

    players.emplace_back(player);
  }
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight); //actual screen
  Controller controller;  // snake??
  Game game(kGridWidth, kGridHeight); // ??
  game.Run(controller, renderer, kMsPerFrame, numPlayers);
  std::cout << "Game has terminated successfully!\n";

  std::cout << "FinalSize\t: PeakSize\t: Score\t: PlayerName\n";
  for(auto player: players)
  {
    std::cout << game.GetSize() << "\t: ";
    std::cout << game.GetSize() << "\t: ";
    std::cout << game.GetScore() << "\t: ";
    std::cout << player << "\n";
  }

// <<TODO>> 2 Write out score details to a leaderboard file
//  Will need to sort the list on score
  LeaderBoard scores(kFile);
  // scores.LoadList(kFile);
  scores.addPlayer(*(players.begin()), game.GetScore());
  scores.printList();
  scores.saveScores(kFile);

  return 0;
}
