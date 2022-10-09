#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "lib.hpp"

TEST_CASE("Sample input should have 24 bits", "[part1]")
{
    const auto sample_input{ read_input("day16_sample_input.txt") };
    REQUIRE(sample_input.size() == 24);
}

TEST_CASE("Puzzle input should have 5496 bits", "[part1]")
{
    const auto sample_input{ read_input("day16_input.txt") };
    REQUIRE(sample_input.size() == 5496);
}

TEST_CASE("Sample input in binary should be correct", "[part1][part2]")
{
    // 0xD2FE28 == 13827624 
    const auto sample_input{ read_input("day16_sample_input.txt") };
    const boost::dynamic_bitset answer(4 * 6, 13827624ul);
    REQUIRE(sample_input == answer);
}

TEST_CASE("Part 1 answer with sample data should be XX", "[part1]")
{
    const auto sample_input{ read_input("day16_sample_input.txt") };
    const auto part1_answer{ part1(sample_input) };
    REQUIRE(part1_answer == 0);
}
