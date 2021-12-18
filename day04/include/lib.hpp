#pragma once

#include <Eigen/Dense>
#include <string>
#include <utility>
#include <vector>

using Board = Eigen::Array<int, 5, 5>;
using Vector5 = Eigen::Array< int, 5, 1 >;

std::pair<std::vector<int>, std::vector<Board>> read_input(const std::string&);

int part1(const std::pair <std::vector<int>, std::vector<Board>>&);

int part2(const std::pair <std::vector<int>, std::vector<Board>>&);
