#include <iostream>
#include "controller.h"
#include "game.h"
#include "scores.h"
#include "renderer.h"
#include "global_share.h"
#include <climits>
#include <memory>

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

  std::cout << "\nEnter number of playerNames (Max : 1): ";
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
  
  std::vector<std::string> playerNames;
  Controller controller;  // snake??
  

  for(int i = 1; i <= numPlayers; i++)
  {
    std::string playerStr;
    std::cout << "\nEnter player " << i++ << "'s name: ";
    getline(std::cin, playerStr);

    playerNames.emplace_back(playerStr);
  }
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight); //actual screen
  
  std::unique_ptr<Game> game;

  if(numPlayers > 1)
    ;//game = std::make_unique<Game>(kGridWidth, kGridHeight, playerNames);
  else
    game = std::make_unique<Game>(kGridWidth, kGridHeight);
  
  game->Run(controller, renderer, kMsPerFrame, numPlayers);
  
  std::cout << "Game has terminated successfully!\n";

  std::cout << 
    //"FinalSize\t: PeakSize\t: " << 
    "Score\t: PlayerName\n";
  for(auto playerStr: playerNames)
  {
    //std::cout << game->GetSize() << "\t: ";
    //std::cout << game->GetSize() << "\t: ";
    std::cout << game->GetScore() << "\t: ";
    std::cout << playerStr << "\n";
  }

// <<TODO>> 2 Write out score details to a leaderboard file
//  Will need to sort the list on score
  LeaderBoard scores(kFile);
  // scores.LoadList(kFile);
  scores.addPlayer(*(playerNames.begin()), game->GetScore());
  scores.printList();
  scores.saveScores(kFile);

  return 0;
}
