#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day09_sample_input.txt") };
const auto puzzle_input{ read_input("day09_input.txt") };

TEST_CASE("Sample input should contain 7 rows and 12 columns")
{
    const auto rows{ sample_input.size() };
    const auto columns{ sample_input.front().size() };

    CHECK(rows == 7);
    CHECK(columns == 12);
}

TEST_CASE("Puzzle input should contain 102 rows and 102 columns")
{
    const auto rows{ puzzle_input.size() };
    const auto columns{ puzzle_input.front().size() };

    CHECK(rows == 102);
    CHECK(columns == 102);
}

TEST_CASE("Part 1 answer with sample input should be 15")
{
    const auto part1_answer{ part1(sample_input) };
    CHECK(part1_answer == 15);
}

TEST_CASE("Part 1 answer with puzzle input should be 558")
{
    const auto part1_answer{ part1(puzzle_input) };
    CHECK(part1_answer == 558);
}

TEST_CASE("Part 2 answer with sample input should be 1134")
{
    const auto part2_answer{ part2(sample_input) };
    CHECK(part2_answer == 1134);
}

TEST_CASE("Part 2 answer with puzzle input should be 882'942")
{
    const auto part2_answer{ part2(puzzle_input) };
    CHECK(part2_answer == 882'942);
}
