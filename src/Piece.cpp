#include <tetris/Piece.hpp>

Piece::Piece( int u_type )
    :
    type( u_type )
{
    if ( u_type <= 0 || u_type > 7 )
    {
        return;
    }

    init( );
}

void
Piece::init( ) 
{
    // `init` is not responsible for checking whether the initialisation
    // is possible, it shall be done in the board implementation

    switch (type) {
        // rotation center is [2].x [2].y for all of these
        case 1: // O
            coords[0].y = 0;
            coords[0].x = 0;
            coords[1].y = 0;
            coords[1].x = 1;
            coords[2].y = 1;
            coords[2].x = 1;
            coords[3].y = 1;
            coords[3].x = 0;
            break;
        case 2: // I
            coords[0].y = 0;
            coords[0].x = 0;
            coords[1].y = 1;
            coords[1].x = 0;
            coords[2].y = 2;
            coords[2].x = 0;
            coords[3].y = 3;
            coords[3].x = 0;
            break;
        case 3: // Z
            coords[0].y = 0;
            coords[0].x = 0;
            coords[1].y = 0;
            coords[1].x = 1;
            coords[2].y = 1;
            coords[2].x = 1;
            coords[3].y = 1;
            coords[3].x = 2;
            break;
        case 4: // S
            coords[0].y = 1;
            coords[0].x = 0;
            coords[1].y = 0;
            coords[1].x = 1;
            coords[2].y = 1;
            coords[2].x = 1;
            coords[3].y = 0;
            coords[3].x = 2;
            break;
        case 5: // L
            coords[0].y = 0;
            coords[0].x = 0;
            coords[1].y = 2;
            coords[1].x = 0;
            coords[2].y = 1;
            coords[2].x = 0;
            coords[3].y = 2;
            coords[3].x = 1;
            break;
        case 6: // J
            coords[0].y = 0;
            coords[0].x = 1;
            coords[1].y = 2;
            coords[1].x = 1;
            coords[2].y = 1;
            coords[2].x = 1;
            coords[3].y = 2;
            coords[3].x = 0;
            break;
        case 7: // T
            coords[0].y = 1;
            coords[0].x = 0;
            coords[1].y = 0;
            coords[1].x = 1;
            coords[2].y = 1;
            coords[2].x = 1;
            coords[3].y = 1;
            coords[3].x = 2;
            break;
        default: break;
    }
}

static void
back_up( Coordinates* source, Coordinates* target )
{
    for (int i = 0; i < 4; ++i) { // saving current coordinates
        target[i].y = source[i].y;
        target[i].x = source[i].x;
    }
}

void
Piece::rotate( ) 
{
    // `rotate` is not responsible for checking whether the rotation
    // is possible, it shall be done in the board implementation
    if ( type == 1 ) return;

    back_up( coords, previous );

    // rotation happens by first determining rotation center of the piece, and
    // then applying these formulas: `y2 = Cy - Cx + x1` and `x2 = Cx + Cy - y1`
    // to each block of the piece, except for the rotation center itself
    for (int i = 0; i < 4; ++i) {
        if (i != 2) {
            int temp_y = coords[i].y;
            coords[i].y = coords[2].y - coords[2].x + coords[i].x;
            coords[i].x = coords[2].x + coords[2].y - temp_y;
        }
    }
}

void
Piece::move( Direction u_direction ) 
{
    // `move` is not responsible for checking whether the move
    // is possible, it shall be done in the board implementation
    back_up( coords, previous );

    int left_right_increment = 0; // -1 for left, +1 for right

    switch (u_direction) {
        case Down:
            for (int i = 0; i < 4; ++i) {
                coords[i].y += 1;
            }
            break; // not returning here to follow `single exit` practice or whatever
        case Left:
            left_right_increment = -1;
            break;
        case Right:
            left_right_increment = 1;
            break;
        default:
            break;
    }
    if ( left_right_increment ) {
        for (int i = 0; i < 4; ++i) {
            coords[i].x += left_right_increment;
        }
    }
}

void
Piece::revert( )
{
    for (int i = 0; i < 4; ++i) {
        coords[i].y = previous[i].y;
        coords[i].x = previous[i].x;
    }
}
