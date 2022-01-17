#pragma once

#include <Eigen/Sparse>
#include <string>
#include <vector>

using Instructions = std::vector<std::pair<std::string, int>>;

std::pair<Eigen::SparseMatrix<int>, Instructions> read_input(const std::string&);

int count_points(const Eigen::SparseMatrix<int>&);

int part1(const std::pair<Eigen::SparseMatrix<int>, Instructions>&);

int part2(const std::pair<Eigen::SparseMatrix<int>, Instructions>&);
