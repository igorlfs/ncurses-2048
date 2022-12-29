#include "game.hpp"

void Game::readInput() {
    int userInputKey = wgetch(this->grid.getWin());
    switch (userInputKey) {
        case QUIT: this->gameOver = true; break;
        default: this->input = userInputKey;
    }
}

void Game::print() const {
    const matrix POSITIONS = this->gate.getPositions();

    for (unsigned i = 0; i < POSITIONS.size(); ++i) {
        for (unsigned j = 0; j < POSITIONS[i].size(); ++j) {
            if (POSITIONS[i][j] != 0) {
                const chtype CHAR = Logic::colorizer(POSITIONS[i][j]);
                this->grid.print(i + 1, j + 1, CHAR);
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
