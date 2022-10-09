#include <bitset>
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

Packet::Packet(boost::dynamic_bitset<> bits)
{
    std::stringstream ver_ss;
    for (int i{ 0 }; i < 3; ++i)
    {
        auto back{ bits[bits.size() - 1] };
        if (back)
        {
            // True
            ver_ss << "1";
        }
        else
        {
            ver_ss << "0";
        }
        bits.pop_back();
    }
    version = std::bitset<3>(ver_ss.str()).to_ullong();

    std::stringstream type_ss;

    for (int i{ 0 }; i < 3; ++i)
    {
        auto back{ bits[bits.size() - 1] };
        if (back)
        {
            // True
            type_ss << "1";
        }
        else
        {
            type_ss << "0";
        }
        bits.pop_back();
    }
    type_id = std::bitset<3>(type_ss.str()).to_ullong();

    if (type_id == 4)
    {
        // Literal value
        std::stringstream lit_val_ss;

        auto prefix{ bits[bits.size() - 1] };
        while (prefix)
        {
            bits.pop_back(); // Pop the prefix
            for (int i{ 0 }; i < 4; ++i)
            {
                auto bit{ bits[bits.size() - 1] };
                if (bit)
                {
                    lit_val_ss << "1";
                }
                else
                {
                    lit_val_ss << "0";
                }
                bits.pop_back();
            }
            prefix = bits[bits.size() - 1];
        }
        // Prefix is 0
        bits.pop_back(); // Pop the prefix
        for (int i{ 0 }; i < 4; ++i)
        {
            auto bit{ bits[bits.size() - 1] };
            if (bit)
            {
                lit_val_ss << "1";
            }
            else
            {
                lit_val_ss << "0";
            }
            bits.pop_back();
        }
        auto lit_val_str{ lit_val_ss.str() };
        literal_value = std::stoi(lit_val_str, nullptr, 2);
    }
}

#include <iostream>
int part1(const boost::dynamic_bitset<>& bits)
{
    for (size_t i{ bits.size() - 1 }; i > 0; --i)
    {
        std::cout << bits[i] << "\n";
    }

    auto p{ Packet(bits) };
    return 0;
}
