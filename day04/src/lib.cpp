#include <algorithm>
#include <fstream>
#include <stdexcept>

#include "lib.hpp"

std::pair<std::vector<int>, std::vector<Board>> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<int> numbers;
    std::string line;

    getline(in, line);
    std::istringstream iss(line);
    std::string number;
    while (std::getline(iss, number, ','))
    {
        numbers.push_back(std::stoi(number));
    }

    getline(in, line); // Skip next line

    std::vector<Board> boards;
    while (getline(in, line))
    {
        Board board;
        for (auto i{ 0 }; i < 5; ++i) // Boards are 5 x 5
        {
            std::vector<int> coefficients;
            iss = std::istringstream(line);
            std::vector<std::vector<int>> rows;
            while (std::getline(iss, number, ' '))
            {
                if (number != "") coefficients.push_back(std::stoi(number)); // Handles numbers separated by 2 spaces
            }
            board.row(i) = Vector5(coefficients.data());
            getline(in, line);
        }
        boards.emplace_back(board);
    }

    return std::make_pair(numbers, boards);
}

int get_sum_unmarked_numbers(const Board& board)
{
    int sum{ 0 };
    for (auto col{ 0 }; col < board.cols(); ++col)
    {
        for (auto row{ 0 }; row < board.rows(); ++row)
        {
            if (board(row, col) > 0) // Ignore negative numbers. Those spots were already marked.
            {
                sum += board(row, col);
            }
        }
    }
    return sum;
}

int part1(const std::pair<std::vector<int>, std::vector<Board>>& game)
{
    auto numbers{ game.first };
    auto boards{ game.second };

    for (const auto& number : numbers)
    {
        for (auto& board : boards)
        {
            for (auto col{ 0 }; col < board.cols(); ++col) // Eigen uses column-major order
            {
                for (auto row{ 0 }; row < board.rows(); ++row)
                {
                    if (board(row, col) == number)
                    {
                        board(row, col) = -1; // Sentinel for marked spot
                        if ((board.row(row) < 0).all() || (board.col(col) < 0).all())
                        {
                            // Winner
                            const auto sum{ get_sum_unmarked_numbers(board) };
                            return sum * number;
                        }
                    }
                }
            }
        }
    }
    return -1;
}

int solve_board(Board& board, const std::vector<int>& numbers)
{
    int turn{ 0 };
    for (const auto& number : numbers)
    {
        for (auto col{ 0 }; col < board.cols(); ++col)
        {
            for (auto row{ 0 }; row < board.rows(); ++row)
            {
                if (board(row, col) == number)
                {
                    board(row, col) = -1; // Sentinel for marked spot
                    if ((board.row(row) < 0).all() || (board.col(col) < 0).all())
                    {
                        // Winner
                        return turn;
                    }
                }
            }
        }
        ++turn;
    }
    return -1; // Not solved
}

int part2(const std::pair<std::vector<int>, std::vector<Board>>& game)
{
    auto numbers{ game.first };
    auto boards{ game.second };
    std::vector<int> turns; // Number of turns it takes to solve each board

    for (auto& board : boards)
    {
        turns.push_back(solve_board(board, numbers));
    }

    auto max_turn{ std::max_element(turns.begin(), turns.end()) }; // Highest turn means last winning board
    auto last_number_called{ numbers.at(*max_turn)};

    auto last_winning_board_pos{ max_turn - turns.begin() }; // Position of last winning board
    auto last_board{ boards.at(last_winning_board_pos) };
    
    const auto sum{ get_sum_unmarked_numbers(last_board) };
    
    return last_number_called * sum;
}
