#include "game.hpp"
#include "msgassert.hpp"

static constexpr int WINDOW_COLS = 6;
static constexpr int WINDOW_ROWS = 6;

void initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    assert(has_colors(), "No color support!");
    start_color();
    use_default_colors();
}

WINDOW *centralizeWindow() {
    int yMax;
    int xMax;

    getmaxyx(stdscr, yMax, xMax);

    return newwin(WINDOW_COLS, WINDOW_ROWS, (yMax - WINDOW_COLS) / 2,
                  (xMax - WINDOW_ROWS) / 2);
}

// TODO:
// - Tests

int main() {
    initialize();

    WINDOW *gameWindow = centralizeWindow();
    Game g(gameWindow);

    while (!g.isGameOver()) {
        g.print();
        g.readInput();
        g.update();
    }

    delwin(gameWindow);
    endwin();
}
