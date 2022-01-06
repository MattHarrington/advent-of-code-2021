#pragma once

#include <deque>
#include <string>
#include <vector>

std::deque<std::vector<int>> read_input(const std::string&);

int part1(const std::deque<std::vector<int>>&);

int part2(const std::deque<std::vector<int>>&);
