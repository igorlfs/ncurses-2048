#pragma once

#include <curses.h>
#include <vector>

using std::vector;

using matrix = vector<vector<int>>;

const int NUM_ROWS = 4;
const int NUM_COLS = 4;

class Logic {
  public:
    /// Constructos
    Logic();

    /// Setters

    /// @brief sets 'values'
    /// @param m, matrix to use when setting
    void setPositions(const matrix &m) { this->values = m; }

    /// Getters

    /// @brirf returns 'values'
    /// @return matrix with current values
    matrix getPositions() const { return this->values; }

    /// Operations

    /// @brief changes the value of a position to a non-null number
    /// @return whether or not it was possible to change such value
    bool spawn();
    /// @brief moves positions according to input
    /// @param input, direction to move
    void move(const int &input);

    /// @brief turns a value from the matrix into a char with a color
    /// @return colored chtype
    static chtype colorizer(const int &value);

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
