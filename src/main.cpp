#include "game.hpp"
#include "msgassert.hpp"

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

// TODO:
// - Merge logic
// - Tests

int main() {
    initialize();

    static constexpr int Y = 6;
    static constexpr int X = 6;
    int yMax;
    int xMax;
    getmaxyx(stdscr, yMax, xMax);
    WINDOW *gameWindow = newwin(Y, X, (yMax - Y) / 2, (xMax - X) / 2);
    Game g(gameWindow);

    while (!g.isGameOver()) {
        g.print();
        g.readInput();
        g.update();
    }

    delwin(gameWindow);
    endwin();
}
