#include <fstream>
#include <stdexcept>
#include <sstream>

#include "lib.hpp"

boost::dynamic_bitset<> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    std::string line;
    std::getline(in, line);

    std::stringstream ss;
    ss << std::hex << line;
    unsigned n;
    ss >> n;

    boost::dynamic_bitset<> bits(4 * line.size(), n);
    return bits;
}

#include <iostream>
// 00111000000000000110111101000101001010010001001000000000
int part1(const boost::dynamic_bitset<>& bits)
{
    for (size_t i{bits.size() - 1}; i > 0; --i)
    {
        std::cout << bits[i] << "\n";
    }

    return 0;
}
