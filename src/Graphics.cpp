#include <tetris/Graphics.hpp>

bool
printn( Board& b, WINDOW* w )
{
    if ( w ) {
        clear();
        wprintw(w, "+====================+\n");
        for (int i = 0; i < BOARD_HEIGHT; ++i) {
            wprintw(w, "|");
            for (int o = 0; o < BOARD_WIDTH; ++o) {
                switch ( b.get_value(i, o) ) {
                    case 0:
                        wprintw(w, "  ");
                        break;
#ifdef LOCALE
                    default:
                        wprintw(w, "■ ");
                        break;
#else
                    case -1:
                        wprintw(w, "D ");
                        break;
                    default:
                        wprintw(w, "O ");
                        break;
#endif
                }
            }
            wprintw(w, "|\n");
        }
        wprintw(w, "+====================+\n");
        refresh();

        return 1;
    }

    return 0;
}
