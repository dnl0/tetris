#include <tetris/Board.hpp>

Board::Board( )
    :
    board ( BOARD_HEIGHT, std::vector<int> (BOARD_WIDTH, 0) ) // 20x10 vector filled with 0
{
}

Piece*
Board::new_piece( int u_type )
{
    Piece *result = new Piece( u_type );

    if ( !check_validity( *result, Down ) ) {
        return nullptr;
    }

    init_piece( *result, result->type );

    return result;
}

bool
Board::check_validity( Piece& u_piece, Direction u_direction ) const
{
    for (int i = 0; i < 4; ++i) {
        if ( u_piece.get_x(i) < 0   || u_piece.get_x(i) >= 10 ) // hits walls
        {
            return false;
        }
        if ( u_piece.get_y(i) == BOARD_HEIGHT ) // hits bottom
        {
            u_piece.kill( );
            return false;
        }
        if ( board[ u_piece.get_y(i) ][ u_piece.get_x(i) ] == -1 ) // hits dead piece
        {
            if ( u_direction == Down ) {
                u_piece.kill( );
            }
            return false;
        }
    }

    return true;
}

bool
Board::check_row( const int row ) const
{
    for (int i = 0; i < BOARD_WIDTH; ++i) {
        if ( board[row][i] != -1 ) {
            return false;
        }
    }

    return true;
}

void
Board::destroy_row( const int row )
{
    for (int i = row; i > 0; --i) {
        board[i] = board[i-1];
    }
}

void
Board::init_piece( const Piece& u_piece, const int fill_type ) 
{
    // put piece on board
    board[ u_piece.get_y(0) ][ u_piece.get_x(0) ] = fill_type;
    board[ u_piece.get_y(1) ][ u_piece.get_x(1) ] = fill_type;
    board[ u_piece.get_y(2) ][ u_piece.get_x(2) ] = fill_type;
    board[ u_piece.get_y(3) ][ u_piece.get_x(3) ] = fill_type;
}

void
Board::clear_space( const Piece& u_piece )
{
    // clear space of the previous position of the piece
    board[ u_piece.get_prev_y(0) ][ u_piece.get_prev_x(0) ] = 0;
    board[ u_piece.get_prev_y(1) ][ u_piece.get_prev_x(1) ] = 0;
    board[ u_piece.get_prev_y(2) ][ u_piece.get_prev_x(2) ] = 0;
    board[ u_piece.get_prev_y(3) ][ u_piece.get_prev_x(3) ] = 0;
}

bool
Board::move_piece( Piece& u_piece, const Direction u_direction )
{
    u_piece.move( u_direction );

    if ( !check_validity( u_piece, u_direction ) ) {
        u_piece.revert( );
        if ( u_piece.is_dead( ) ) {
            init_piece( u_piece, -1 ); // current piece's coordinates become dead cells

            for (int i = 0; i < 4; ++i) {
                if ( check_row( u_piece.get_y(i) ) ) {
                    destroy_row( u_piece.get_y(i) );
                }
            }
        }

        return false;
    }

    clear_space( u_piece );
    init_piece( u_piece, u_piece.type );

    return true;
}

bool
Board::rotate_piece( Piece& u_piece )
{
    u_piece.rotate( );

    if ( !check_validity( u_piece, Down ) ) {
        u_piece.revert( );
        return false;
    }

    clear_space( u_piece );
    init_piece( u_piece, u_piece.type );

    return true;
}
