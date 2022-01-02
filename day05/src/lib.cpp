#include <algorithm>
#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>
#include <unordered_map>

#include "lib.hpp"

std::vector<Vent> read_input(const std::string& filename)
{
	std::fstream in{ filename };
	if (!in) throw std::runtime_error("File not found");

	const std::regex r{ R"((\d+),(\d+) -> (\d+),(\d+))" };
	std::vector<Vent> vents;
	std::string line;
	while (std::getline(in, line))
	{
		std::smatch sm;
		std::regex_match(line, sm, r);
		Point start{ std::stoi(sm[1]), std::stoi(sm[2]) };
		Point end{ std::stoi(sm[3]), std::stoi(sm[4]) };
		Vent vent{ start,end };
		vents.emplace_back(vent);
	}
	return vents;
}

ptrdiff_t solve(const std::vector<Vent>& vents, const Part part)
{
	std::unordered_map<Point, int, PointHash> map;

	for (const auto& vent : vents)
	{
		// Vents can run in any direction. These deltas are 1
		// if starting position is smaller than ending position and
		// -1 for vice versa.
		const auto x_delta{ vent.start.x < vent.end.x ? 1 : -1 };
		const auto y_delta{ vent.start.y < vent.end.y ? 1 : -1 };

		if (vent.start.x == vent.end.x)
		{
			// Vent runs vertically
			for (int y{ vent.start.y }; y != vent.end.y + y_delta; y += y_delta)
			{
				++map[Point{ vent.start.x, y }];
			}
		}
		else if (vent.start.y == vent.end.y)
		{
			// Vent runs horizontally
			for (int x{ vent.start.x }; x != vent.end.x + x_delta; x += x_delta)
			{
				++map[Point{ x, vent.start.y }];
			}
		}
		else if (part == Part::two)
		{
			// Vent runs diagonally. Ignore for part 1.
			for (int x{ vent.start.x }, y{ vent.start.y }; x != vent.end.x + x_delta; x += x_delta, y += y_delta)
			{
				++map[Point{ x, y }];
			}
		}
	}

	const auto intersections{ std::count_if(map.begin(), map.end(), [](auto m) {return m.second >= 2; }) };
	return intersections;
}
