#include <fstream>
#include <regex>
#include <sstream>
#include <stdexcept>

#include "lib.hpp"

std::vector<std::pair<Command, int>> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::vector < std::pair<Command,int>> input;
    std::string line;
    const std::regex r{ R"((forward|down|up) (\d+))" };

    while (getline(in, line))
    {
        std::smatch sm;
        std::regex_match(line, sm, r);
        Command command;
        if (sm[1] == "forward") command = Command::forward;
        else if (sm[1] == "up") command = Command::up;
        else if (sm[1] == "down") command = Command::down;
        else throw std::invalid_argument("Bad command in input");
        input.push_back(std::make_pair(command, std::stoi(sm[2])));
    }

    return input;
}

int part1(const std::vector<std::pair<Command, int>>& commands) noexcept
{
    int horizontal_position{ 0 };
    int depth{ 0 };
    for (const auto& command : commands)
    {
        if (command.first == Command::forward) horizontal_position += command.second;
        else if (command.first == Command::down) depth += command.second;
        else if (command.first == Command::up) depth -= command.second;
    }

    return horizontal_position * depth;
}

int part2(const std::vector<std::pair<Command, int>>& commands) noexcept
{
    int aim{ 0 };
    int horizontal_position{ 0 };
    int depth{ 0 };
    for (const auto& command : commands)
    {
        if (command.first == Command::forward)
        {
            horizontal_position += command.second;
            depth += aim * command.second;
        }
        else if (command.first == Command::down) aim += command.second;
        else if (command.first == Command::up) aim -= command.second;
    }

    return horizontal_position * depth;
}
