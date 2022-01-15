#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day12_sample_input.txt") };
const auto puzzle_input{ read_input("day12_input.txt") };

TEST_CASE("Sample input should contain 6 nodes")
{
    CHECK(sample_input.size() == 6);
}

TEST_CASE("Puzzle input should contain 13 nodes")
{
    CHECK(puzzle_input.size() == 13);
}

TEST_CASE("Part 1 answer with sample data should be 10")
{
    auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 10);
}

TEST_CASE("Part 1 answer with puzzle data should be 3510")
{
    auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 3510);
}

TEST_CASE("Part 2 answer with sample data should be 36")
{
    auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 36);
}

TEST_CASE("Part 2 answer with puzzle data should be 122'880")
{
    auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 122'880);
}
