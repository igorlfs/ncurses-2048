#pragma once

#include "board.hpp"
#include "logic.hpp"
#include <ncurses.h>

class Game {
  public:
    /// Constructors
    Game(WINDOW *win) : grid(win) { this->gate.spawn(); }

    /// Getters
    bool isGameOver() const { return this->gameOver; }

    /// Operations

    /// @brief reads user input
    void readInput();
    /// @brief update game based on input
    void update();
    /// @brief print changes in memory to screen
    void print() const;

  private:
    bool gameOver{false};
    int input;
    Board grid;
    Logic gate;

    static constexpr int QUIT{(int)'x'};
};
