#pragma once

#include <string>
#include <vector>

struct Input
{
    std::vector<std::string> signal_patterns;
    std::vector<std::string> output_values;
};

std::vector<Input> read_input(const std::string&);

long long part1(const std::vector<Input>&);

int part2(std::vector<Input>);
