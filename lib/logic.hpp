#pragma once

#include <vector>

using std::vector;

using matrix = vector<vector<int>>;

const int NUM_ROWS = 4;
const int NUM_COLS = 4;

class Logic {
  public:
    /// Constructos
    Logic();

    /// Getters
    matrix getPositions() const { return this->values; }

    /// @brief changes the value of a position to a non-null number
    /// @return whether or not it was possible to change such value
    bool spawn();
    /// @brief moves positions according to input
    void move(const int &input);

  private:
    matrix values;

    /// @brief checks if the all positions are non-null numbers
    /// @return whether or not all positions are non-null numbers
    bool isThereEnoughSpace();

    /// @brief set auxiliary variables to help move
    /// @param input, direction to move
    /// @param n, first coordinate of a given element
    /// @param m, second coordinate of a given element
    void moveHelper(const int &input, const int &n, const int &m);

    /// @brief move a given position
    /// @param n, first coordinate of a given element
    /// @param m, second coordinate of a given element
    /// @param v, possible candidates for moving given current input
    /// @param horizontal, indicates movement direction
    void handleMove(const int &n, const int &m, const vector<int> &v,
                    const bool &horizontal);
};
