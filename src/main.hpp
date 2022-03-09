#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include "controller.h"
#include "game.h"
#include "scores.h"
#include "renderer.h"
#include "global_share.h"
#include "MapTile.hpp"
#include <climits>
#include <getopt.h>
#include <memory>
#include <mutex>
#include <future>
#include <vector>
#include <thread>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fstream>
#include <algorithm>

std::size_t kScreenWidth{640};
std::size_t kScreenHeight{640};
std::size_t kGridWidth{32};
std::size_t kGridHeight{32};

#endif