#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include "lib.hpp"

const auto sample_input{ read_input("day06_sample_input.txt") };
const auto puzzle_input{ read_input("day06_input.txt") };

TEST_CASE("Sample input should contain 5 numbers")
{
    CHECK(sample_input.size() == 5);
}

TEST_CASE("Puzzle input should contain 300 numbers")
{
    CHECK(puzzle_input.size() == 300);
}

TEST_CASE("Part 1 answer with sample input should be 5934")
{
    const auto part1_answer(part1(sample_input));
    CHECK(part1_answer == 5934);
}

TEST_CASE("Part 1 answer with puzzle input should be 350'605")
{
    const auto part1_answer(part1(puzzle_input));
    CHECK(part1_answer == 350'605);
}

TEST_CASE("Part 2 answer with sample input should be 26'984'457'539")
{
    const auto part2_answer(part2(sample_input));
    CHECK(part2_answer == 26'984'457'539LL);
}

TEST_CASE("Part 2 answer with puzzle input should be 1'592'778'185'024")
{
    const auto part2_answer(part2(puzzle_input));
    CHECK(part2_answer == 1'592'778'185'024LL);
}
