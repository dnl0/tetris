#pragma once

#include "Board.hpp"
#include "Graphics.hpp"

#include <thread>

class Game {
    private:
        std::unique_ptr <Board> board;
        std::unique_ptr <Piece> piece;

        void setup( );
        void loop( );
        void print_loop( ) const;

        int get_random();

        std::thread game;
        std::thread print;
        std::mutex  game_mutex;
        
    public:
        Game();
};
