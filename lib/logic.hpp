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

    /// @brief handle input when moving
    pair<int, int> moveHelper(const int &input, const pair<int, int> &p);
};
