#pragma once

#include <boost/dynamic_bitset.hpp>
#include <string>

boost::dynamic_bitset<> read_input(const std::string&);

int part1(const boost::dynamic_bitset<>&);
