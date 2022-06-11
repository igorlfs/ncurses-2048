#include "logic.hpp"
#include "random.hpp"
#include <curses.h>

using std::pair;
using std::swap;

const pair<int, int> INVALID = {-1, -1};

Logic::Logic() {
    this->values.resize(NUM_ROWS);
    for (auto &value : this->values) {
        value.resize(NUM_COLS);
        for (int &i : value) {
            i = 0;
        }
    }
}

bool Logic::spawn() {
    if (!isThereEnoughSpace()) {
        return false;
    }

    // Generate random position
    pair<int, int> p;
    while (true) {
        p = {Random::rng(0, NUM_COLS - 1), Random::rng(0, NUM_ROWS - 1)};
        if (this->values[p.first][p.second] == 0) {
            break;
        }
    }

    // Choose between 1 and 2
    int numberGenerated;
    // 90% of the time should choose 1
    const int ODDS = 9;
    (Random::rng(0, ODDS) == 0) ? numberGenerated = 2 : numberGenerated = 1;

    // Place in position
    this->values[p.first][p.second] = numberGenerated;

    return true;
}

void Logic::move(const int &input) {
    for (int i = 0; i < NUM_ROWS; ++i) {
        for (int j = 0; j < NUM_COLS; ++j) {
            if (positions[i][j] == 0) {
                continue;
            }
            pair<int, int> temp = moveHelper(input, {i, j});
            if (temp != INVALID) {
                swap(positions[temp.first][temp.second], positions[i][j]);
            }
        }
    }
}

pair<int, int> Logic::moveHelper(const int &input, const pair<int, int> &p) {
    pair<int, int> temp = INVALID;
    switch (input) {
        case KEY_UP: {
            for (int k = p.first; k >= 0; --k) {
                if (positions[k][p.second] == 0) {
                    temp = {k, p.second};
                }
            }
            break;
        }
        case KEY_DOWN: {
            for (int k = p.first; k < NUM_ROWS; ++k) {
                if (positions[k][p.second] == 0) {
                    temp = {k, p.second};
                }
            }
            break;
        }
        case KEY_LEFT: {
            for (int k = p.second; k >= 0; --k) {
                if (positions[p.first][k] == 0) {
                    temp = {p.first, k};
                }
            }
            break;
        }
        case KEY_RIGHT: {
            for (int k = p.second; k < NUM_COLS; ++k) {
                if (positions[p.first][k] == 0) {
                    temp = {p.first, k};
                }
            }
            break;
        }
    }
    return temp;
}

bool Logic::isThereEnoughSpace() {
    int space = 0;
    for (auto &value : this->values) {
        for (int &i : value) {
            if (i != 0) {
                space++;
            }
        }
    }
    return space < NUM_ROWS * NUM_COLS;
}
