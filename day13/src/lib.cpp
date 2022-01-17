#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <utility>

#include "lib.hpp"

std::pair<Eigen::SparseMatrix<int>, Instructions> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<std::pair<int, int>> points;
    const std::regex r1{ R"((\d+),(\d+))" };
    const std::regex r2{ R"(fold along (x|y)=(\d+))" };
    std::string line;
    auto max_value_in_row{ 0 };
    auto max_value_in_col{ 0 };
    while (std::getline(in, line))
    {
        if (line == "") break;
        std::smatch sm;
        std::regex_match(line, sm, r1);
        auto coord{ std::make_pair(std::stoi(sm[1]), std::stoi(sm[2])) };
        points.emplace_back(coord);
        if (std::stoi(sm[1]) > max_value_in_col) max_value_in_col = std::stoi(sm[1]);
        if (std::stoi(sm[2]) > max_value_in_row) max_value_in_row = std::stoi(sm[2]);
    }

    Eigen::SparseMatrix<int> sparse_m(max_value_in_row + 1, max_value_in_col + 1);
    for (const auto& p : points)
    {
        sparse_m.insert(p.second, p.first) = 1; // (row,col)
    }

    Instructions instructions;
    while (std::getline(in, line))
    {
        std::smatch sm;
        std::regex_match(line, sm, r2);
        instructions.emplace_back(std::make_pair(sm[1], std::stoi(sm[2])));
    }

    return { sparse_m, instructions };
}

int count_points(const Eigen::SparseMatrix<int>& sparse_m)
{
    auto total_points{ 0 };
    for (auto col{ 0 }; col < sparse_m.cols(); ++col)
    {
        for (auto row{ 0 }; row < sparse_m.rows(); ++row)
        {
            if (sparse_m.coeff(row, col) > 0)
            {
                ++total_points;
            }
        }
    }
    return total_points;
}


int part1(const std::pair<Eigen::SparseMatrix<int>, Instructions>& input)
{
    auto sparse_m{ input.first };

    const auto first_instruction{ input.second.front() };
    const auto axis{ first_instruction.second };

    if (first_instruction.first == "x")
    {
        // Fold vertically
        for (auto delta{ 1 }; delta < sparse_m.cols() - axis; ++delta)
        {
            for (auto row{ 0 }; row < sparse_m.rows(); ++row)
            {
                sparse_m.coeffRef(row, axis - delta) += sparse_m.coeff(row, axis + delta);
                sparse_m.coeffRef(row, axis + delta) = 0;
            }
        }
    }

    else if (first_instruction.first == "y")
    {
        // Fold horizontally
        for (auto delta{ 1 }; delta < sparse_m.rows() - axis; ++delta)
        {
            for (auto col{ 0 }; col < sparse_m.cols(); ++col)
            {
                sparse_m.coeffRef(axis - delta, col) += sparse_m.coeff(axis + delta, col);
                sparse_m.coeffRef(axis + delta, col) = 0;
            }
        }
    }

    const auto total_points{ count_points(sparse_m) };
    return total_points;
}

int part2(const std::pair<Eigen::SparseMatrix<int>, Instructions>& input)
{
    auto sparse_m{ input.first };

    std::cout << "Initial size: (" << sparse_m.rows() << "," << sparse_m.cols() << ")\n";

    for (const auto& instruction : input.second)
    {
        const auto axis{ instruction.second };

        if (instruction.first == "x")
        {
            // Fold vertically
            for (auto delta{ 1 }; delta < sparse_m.cols() - axis; ++delta)
            {
                for (auto row{ 0 }; row < sparse_m.rows(); ++row)
                {
                    sparse_m.coeffRef(row, axis - delta) += sparse_m.coeff(row, axis + delta);
                    sparse_m.coeffRef(row, axis + delta) = 0;
                }
            }
            sparse_m.conservativeResize(sparse_m.rows(), axis);
            std::cout << "New size: (" << sparse_m.rows() << "," << sparse_m.cols() << ")\n";
        }

        else if (instruction.first == "y")
        {
            // Fold horizontally
            for (auto delta{ 1 }; delta < sparse_m.rows() - axis; ++delta)
            {
                for (auto col{ 0 }; col < sparse_m.cols(); ++col)
                {
                    sparse_m.coeffRef(axis - delta, col) += sparse_m.coeff(axis + delta, col);
                    sparse_m.coeffRef(axis + delta, col) = 0;
                }
            }
            sparse_m.conservativeResize(axis, sparse_m.cols());
            std::cout << "New size: (" << sparse_m.rows() << "," << sparse_m.cols() << ") " << sparse_m.size() << "\n";
        }
    }

    std::cout << "Ending size: (" << sparse_m.rows() << "," << sparse_m.cols() << ") " << sparse_m.size() << "\n";

    std::cout << "Folded paper:\n" << sparse_m << "\n";

    const auto total_points{ count_points(sparse_m) };
    return total_points;
}
