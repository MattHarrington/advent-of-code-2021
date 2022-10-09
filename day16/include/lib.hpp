#pragma once

#include <boost/dynamic_bitset.hpp>
#include <string>
#include <vector>

struct Packet
{
    unsigned long long version;
    unsigned long long type_id;
    int literal_value;
    std::vector<Packet> subpackets;
    Packet(boost::dynamic_bitset<>);
};

boost::dynamic_bitset<> read_input(const std::string&);

int part1(const boost::dynamic_bitset<>&);
