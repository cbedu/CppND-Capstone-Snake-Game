#pragma once

#ifndef GLOBAL_SHARE_H
#define GLOBAL_SHARE_H

extern bool global_waitingOnPlayers;

// Needs rule of 5 for unique_ptr move semantics
struct tileMap {
    int width{0};
    int height{0};
    std::vector<std::vector<int>> tiles;
};

#endif