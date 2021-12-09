#pragma once

#include <string>
#include <utility>
#include <vector>

enum class Command
{
    forward, down, up
};

std::vector<std::pair<Command,int>> read_input(const std::string&);

int part1(const std::vector<std::pair<Command,int>>&) noexcept;

int part2(const std::vector<std::pair<Command,int>>&) noexcept;
