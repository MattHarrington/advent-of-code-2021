#pragma once

#include <Eigen/Dense>
#include <string>
#include <vector>

Eigen::Matrix<int, 10, 10> read_input(const std::string&);

int part1(Eigen::Matrix<int, 10, 10>);

int part2(Eigen::Matrix<int, 10, 10>);
