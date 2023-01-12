#include <tetris/Game.hpp>

#include <unistd.h>

#ifdef LOCALE
#include <locale.h>
#endif

#include <random>
#include <memory>

Game::Game( )
    :
    board( std::make_unique<Board> ( ) ),
    piece( std::make_unique<Piece> ( get_random() ) )
{
    setup();

    game  = std::thread ( &Game::loop, this );
    print = std::thread ( &Game::print_loop, this );

    game.join();
    print.join();

    endwin();
}

void 
Game::setup( )
{
    initscr( );             // initialize screen
    nodelay( stdscr, 1 );   // don't wait for `getch()`
    noecho( );              // don't repeat characters entered by user
    cbreak( );              // disable line buffering
    curs_set( 0 );          // don't print cursor
    keypad( stdscr, 1 );    // enable arrows

#ifdef LOCALE
    setlocale(LOCALE, "");
#endif
}

void
Game::loop( )
{
    while ( piece != nullptr ) {
        int c = wgetch( stdscr );

        switch ( c ) {
            case KEY_UP:
                board->rotate_piece( *piece );
                break;
            case KEY_DOWN:
                board->move_piece( *piece, Down );
                break;
            case KEY_LEFT:
                board->move_piece( *piece, Left );
                break;
            case KEY_RIGHT:
                board->move_piece( *piece, Right );
                break;
            case ' ':
                while ( board->move_piece( *piece, Down ) ) {
                    usleep(100);
                }
                break;
            case 'q':
                stdscr = NULL;
                return;
                break;
            default:
                if ( !board->move_piece( *piece, Down ) ) {
                    piece.reset( board->new_piece( get_random() ) );
                }

                usleep(200000);
                break;
        }

        usleep(10000);
    }

    stdscr = NULL;
    return;
}

void
Game::print_loop( ) const
{
    while ( printn( *board, stdscr ) ) {
        usleep(100);
    }
}

int
Game::get_random( )
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist7(1,7);

    return dist7(rng);
}
