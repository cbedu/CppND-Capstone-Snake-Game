#pragma once

#ifndef GLOBAL_SHARE_H
#define GLOBAL_SHARE_H

extern bool global_waitingOnPlayers;

constexpr std::size_t kTileTypes{4};
enum TILE_TYPES {FLOOR_TILE, FOOD_TILE, POISON_TILE, BARRIER_TILE};

#endif