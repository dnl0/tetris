#include <memory>

#include <tetris/Game.hpp>

auto
main() -> int
{
    std::unique_ptr <Game> tetris = std::make_unique<Game> ( );
}
