#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

std::pair<std::string, std::unordered_map<std::string, char>> read_input(const std::string&);

long long part1(const std::pair<std::string, std::unordered_map<std::string, char>>&);

long long part2(const std::pair<std::string, std::unordered_map<std::string, char>>&);