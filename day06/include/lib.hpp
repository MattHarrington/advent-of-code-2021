#pragma once

#include <vector>

enum class Part
{
	one, two
};

std::vector<int> read_input(const std::string&);

size_t part1(std::vector<int>);

long long part2(const std::vector<int>&);

