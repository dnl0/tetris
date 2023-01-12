#pragma once

#include "Piece.hpp"

#include <vector>

#define BOARD_HEIGHT 20
#define BOARD_WIDTH  10

class Board {
    private:
        // i like the approach of board being just a vector and then just
        // printing this vector over and over, since it allows me to not
        // deal with actual screen coordinates and all that. i'm not very
        // sure about the efficiency of this method, but it's good enough
        // for me lol.
        std::vector< std::vector<int> > board;
    public:
        Board( );

        inline int get_value( const int y, const int x ) const { return board[y][x]; }

        bool check_validity( Piece& u_piece, Direction u_direction ) const;

        bool check_row( const int row ) const;
        void destroy_row( const int row );

        Piece *new_piece( const int type );
        void init_piece( const Piece& u_piece, const int fill_value );
        void clear_space( const Piece& u_piece );

        bool move_piece( Piece& u_piece, const Direction u_direction );
        bool rotate_piece( Piece& u_piece );
};
