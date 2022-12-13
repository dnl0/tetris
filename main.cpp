#include <iostream>
#include <memory>
#include <unistd.h>

#include "Game.hpp"

auto
main() -> int
{
    std::unique_ptr <Game> tetris ( new Game() );

    return 0;
}
