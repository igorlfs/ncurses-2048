#include "logic.hpp"
#include "random.hpp"
#include <array>
#include <curses.h>

using std::array;
using std::pair;
using std::swap;

Logic::Logic() {
    this->values.resize(NUM_ROWS);
    for (auto &value : this->values) {
        value.resize(NUM_COLS);
        for (int &val : value) {
            val = 0;
        }
    }
}

bool Logic::spawn() {
    if (!isThereEnoughSpace()) {
        return false;
    }

    // Generate random position
    pair<int, int> pair;
    while (true) {
        pair = {Random::rng(0, NUM_COLS - 1), Random::rng(0, NUM_ROWS - 1)};
        if (this->values[pair.first][pair.second] == 0) {
            break;
        }
    }

    // Choose between 1 and 2
    int numberGenerated;
    // 90% of the time should choose 1
    const int ODDS = 9;
    (Random::rng(0, ODDS) == 0) ? numberGenerated = 2 : numberGenerated = 1;

    // Place in position
    this->values[pair.first][pair.second] = numberGenerated;

    return true;
}

void Logic::move(const int &input) {
    array<int, 4> rows = {0, 1, 2, 3};
    array<int, 4> cols = {0, 1, 2, 3};

    if (input == KEY_UP) {
        rows = {3, 2, 1, 0};
    }
    if (input == KEY_LEFT) {
        cols = {3, 2, 1, 0};
    }

    for (const int &i : rows) {
        for (const int &j : cols) {
            if (this->values[i][j] == 0) {
                continue;
            }
            moveHelper(input, i, j);
        }
    }
}

void Logic::moveHelper(const int &input, const int &n, const int &m) {
    // Expect vertical move by default
    bool horizontal = false;
    vector<int> v;

    switch (input) {
        case KEY_UP: {
            for (int i = n - 1; i >= 0; --i) {
                v.push_back(i);
            }
            break;
        }
        case KEY_DOWN: {
            for (int i = n + 1; i < NUM_ROWS; ++i) {
                v.push_back(i);
            }
            break;
        }
        case KEY_RIGHT: {
            for (int i = m + 1; i < NUM_COLS; ++i) {
                v.push_back(i);
            }
            horizontal = true;
            break;
        }
        case KEY_LEFT: {
            for (int i = m - 1; i >= 0; --i) {
                v.push_back(i);
            }
            horizontal = true;
            break;
        }
    }
    handleMove(n, m, v, horizontal);
}

void Logic::handleMove(const int &n, const int &m, const vector<int> &v,
                       const bool &horizontal) {
    int *p = &this->values[n][m];
    int *q = nullptr;

    for (const int &k : v) {
        horizontal ? q = &this->values[n][k] : q = &this->values[k][m];

        if (*q == *p) {
            (*q)++;
            *p = 0;
        }

        if (*q == 0) {
            *q = *p;
            *p = 0;
        }

        break;
    }
}

bool Logic::isThereEnoughSpace() {
    int space = 0;
    for (auto &value : this->values) {
        for (int &val : value) {
            if (val != 0) {
                space++;
            }
        }
    }
    return space < NUM_ROWS * NUM_COLS;
}

chtype Logic::colorizer(const int &value) {
    return ('a' + value - 1) | COLOR_PAIR(value % 6 + 1);
}
