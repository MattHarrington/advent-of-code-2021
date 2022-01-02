#include <cassert>
#include <iostream>

#include "lib.hpp"

int main()
{
	auto puzzle_input{ read_input("day05_input.txt") };

	const auto part1_answer{ solve(puzzle_input, Part::one)};
	std::cout << "Part 1 answer: " << part1_answer << "\n";
	assert(part1_answer == 6564);

	const auto part2_answer{ solve(puzzle_input, Part::two)};
	std::cout << "Part 2 answer: " << part2_answer << "\n";
	assert(part2_answer == 19'172);

	return 0;
}
