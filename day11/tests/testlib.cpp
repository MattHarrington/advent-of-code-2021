#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day11_sample_input.txt") };
const auto puzzle_input{ read_input("day11_input.txt") };

TEST_CASE("Sample input should contain 100 values")
{
    CHECK(sample_input.size() == 100);
}

TEST_CASE("Puzzle input should contain 10 values")
{
    CHECK(puzzle_input.size() == 100);
}

TEST_CASE("Part 1 answer with sample input should be 1656")
{
    const auto part1_answer(part1(sample_input));
    CHECK(part1_answer == 1656);
}

TEST_CASE("Part 1 answer with puzzle input should be 1601")
{
    const auto part1_answer(part1(puzzle_input));
    CHECK(part1_answer == 1601);
}

TEST_CASE("Part 2 answer with sample input should be 195")
{
    const auto part2_answer(part2(sample_input));
    CHECK(part2_answer == 195);
}

TEST_CASE("Part 2 answer with puzzle input should be 368")
{
    const auto part2_answer(part2(puzzle_input));
    CHECK(part2_answer == 368);
}
