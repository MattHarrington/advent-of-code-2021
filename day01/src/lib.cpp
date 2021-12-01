#include <fstream>
#include <sstream>
#include <stdexcept>

#include "lib.hpp"

std::vector<int> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector<int> input;
    std::string line;

    while (getline(in, line))
    {
        input.push_back(std::stoi(line));
    }

    return input;
}

int part1(const std::vector<int>& depths)
{
    int counter{ 0 };

    for (size_t i{ 1 }; i < depths.size(); ++i)
    {
        if (depths.at(i) > depths.at(i - 1))
        {
            ++counter;
        }
    }

    return counter;
}
