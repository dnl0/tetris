#pragma once

#include <ncurses.h>

#include "Board.hpp"

#ifndef __APPLE__
#define LOCALE LC_ALL
#endif

bool printn( Board& b, WINDOW* w );
