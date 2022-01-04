#include <algorithm>
#include <cmath>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <sstream>

#include "lib.hpp"

#include <iostream>

std::vector<int> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<int> positions;
    std::string input;
    std::getline(in, input);

    std::stringstream ss(input); //create string stream from the string
    while (ss.good()) {
        std::string substr;
        std::getline(ss, substr, ','); //get first string delimited by comma
        positions.push_back(std::stoi(substr));
    }
    return positions;
}

int part1(const std::vector<int>& positions)
{
    auto max_position{ std::max_element(positions.begin(), positions.end()) };
    std::vector<int> fuel_required(*max_position + 1); // Fuel required for each position

    for (int i{ 1 }; i < fuel_required.size(); ++i)
    {
        fuel_required.at(i) = std::accumulate(positions.begin(), positions.end(), 0, [i](int a, int b) noexcept {return a + std::abs(i - b); });
    }

    auto minimum_fuel{ std::min_element(fuel_required.begin() + 1, fuel_required.end()) };

    return *minimum_fuel;
}

constexpr int get_triangular_number(int b) noexcept
{
    // Recursive solution, but slow:
    //if (b == 0) return 0;
    //return b + get_triangular_number(b - 1);

    // Triangular number
    // https://math.stackexchange.com/questions/60578/what-is-the-term-for-a-factorial-type-operation-but-with-summation-instead-of-p
    return (b * b + b) / 2;
}

int part2(const std::vector<int>& positions)
{
    auto max_position{ std::max_element(positions.begin(), positions.end()) };
    std::vector<int> fuel_required(*max_position + 1); // Fuel required for each position

    for (int i{ 1 }; i < fuel_required.size(); ++i)
    {
        fuel_required.at(i) = std::accumulate(positions.begin(), positions.end(), 0, [i](int a, int b) noexcept {return a + get_triangular_number(std::abs(i - b)); });
    }

    auto minimum_fuel{ std::min_element(fuel_required.begin() + 1, fuel_required.end()) };

    return *minimum_fuel;
}
