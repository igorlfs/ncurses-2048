#include "game.hpp"
#include "msgassert.hpp"

static constexpr int WINDOW_COLS = 6;
static constexpr int WINDOW_ROWS = 6;

void initColor() {
    for (int i = 1; i <= COLOR_CYAN; ++i) {
        init_pair(i, i, -1);
    }
}

void initialize() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    refresh();
    assert(has_colors(), "No color support!");
    start_color();
    use_default_colors();
    initColor();
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
    Game game(gameWindow);

    while (!game.isGameOver()) {
        game.print();
        game.readInput();
        game.update();
    }

    delwin(gameWindow);
    endwin();
}
