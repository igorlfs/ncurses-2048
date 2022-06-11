#include "game.hpp"

void Game::readInput() {
    int userInputKey = wgetch(this->grid.getWin());
    switch (userInputKey) {
        case QUIT: this->gameOver = true; break;
        default: this->input = userInputKey;
    }
}

void Game::print() const {
    const matrix M = this->gate.getPositions();

    for (unsigned i = 0; i < M.size(); ++i) {
        for (unsigned j = 0; j < M[i].size(); ++j) {
            if (M[i][j] != 0) {
                this->grid.print(i + 1, j + 1, (char)('a' + M[i][j] - 1));
            } else {
                this->grid.print(i + 1, j + 1, ' ');
            }
        }
    }

    wrefresh(this->grid.getWin());
}

void Game::update() {
    this->gate.move(this->input);
    if (!this->gate.spawn()) {
        this->gameOver = true;
        return;
    }
}
