#pragma once

#include <functional>
#include <vector>

enum class Part
{
	one, two
};

struct Point
{
	int x;
	int y;
};

inline bool operator==(const Point& lhs, const Point& rhs) noexcept {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

// https://en.cppreference.com/w/cpp/utility/hash:
struct PointHash
{
	std::size_t operator()(Point const& p) const noexcept
	{
		const std::size_t h1 = std::hash<int>{}(p.x);
		const std::size_t h2 = std::hash<int>{}(p.y);
		return h1 ^ (h2 << 1); // or use boost::hash_combine
	}
};

struct Vent
{
	Point start;
	Point end;
};

std::vector<Vent> read_input(const std::string&);

ptrdiff_t solve(const std::vector<Vent>&, const Part);
