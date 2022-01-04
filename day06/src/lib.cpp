#include <algorithm>
#include <array>
#include <fstream>
#include <numeric>
#include <stdexcept>
#include <sstream>
#include <string>

#include "lib.hpp"

#include <iostream>

std::vector<int> read_input(const std::string& filename)
{
	std::fstream in{ filename };
	if (!in) throw std::runtime_error("File not found");

	std::vector<int> fishes;
	std::string input;
	std::getline(in, input);

	std::stringstream ss(input);
	while (ss.good()) {
		std::string substr;
		std::getline(ss, substr, ',');
		fishes.push_back(std::stoi(substr));
	}
	return fishes;
}

/// <summary>
///	Brute force solution. Runs out of RAM if used for part 2.
/// </summary>
/// <param name="fishes">Days to reproduction for each fish.</param>
/// <returns>Number of fish after 80 days.</returns>
size_t part1(std::vector<int> fishes)
{
	constexpr auto days{ 80 };

	for (auto i{ 0 }; i < days; ++i)
	{
		long long spawned_fish{ 0 };
		for (auto& fish : fishes)
		{
			--fish;
			if (fish == -1)
			{
				fish = 6;
				++spawned_fish;
			}
		}
		for (auto j{ 0LL }; j < spawned_fish; ++j)
		{
			fishes.push_back(8);
		}
	}
	return fishes.size();
}

/// <summary>
///	Place fish into a bin for each of the 9 days. 
/// </summary>
/// <param name="fishes">Days to reproduction for each fish.</param>
/// <returns>Number of fish in each of the 9 days.</returns>
std::array<long long, 9> get_fish_per_day(const std::vector<int>& fishes)
{
	std::array<long long, 9> days{ 0 };

	for (const auto& fish : fishes)
	{
		++days.at(fish);
	}
	
	return days;
}

/// <summary>
///	Quicker solution than part1(). 
/// </summary>
/// <param name="fishes">Days to reproduction for each fish.</param>
/// <returns>Number of fish after 256 days.</returns>
long long part2(const std::vector<int>& fishes)
{
	constexpr auto days{ 256 };
	auto fish_per_day{ get_fish_per_day(fishes) };

	for (auto i{ 0 }; i < days; ++i)
	{
		// Rotate array to simulate passing of each day.
		std::rotate(fish_per_day.begin(), fish_per_day.begin() + 1, fish_per_day.end()); // Rotate left
		// Number of fish at day 8 after rotation equals number of fish at day 0 before rotation.
		// Add that to number of fish at day 6.
		fish_per_day.at(6) = fish_per_day.at(6) + fish_per_day.at(8);
	}

	auto total_fish{ std::accumulate(fish_per_day.begin(), fish_per_day.end(), 0LL) };

	return total_fish;
}
