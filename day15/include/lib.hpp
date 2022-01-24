#pragma once

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using Grid = std::vector<std::vector<int>>;

struct Point
{
    size_t x;
    size_t y;
};

inline bool operator==(const Point& lhs, const Point& rhs) noexcept
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

// https://en.cppreference.com/w/cpp/utility/hash:
struct PointHash
{
    std::size_t operator()(Point const& p) const noexcept;
};

class Graph
{
public:
    explicit Graph(const Grid&);

    size_t size() const noexcept;

    std::vector<Point> get_neighbors(const Point&) const;

    int get_risk_level(const Point&) const;

    std::vector<Point> get_vertices() const;

private:
    std::unordered_map<Point, std::vector<Point>, PointHash> adj_list_;
    std::unordered_map<Point, int, PointHash> risk_level_;
};

Grid read_input(const std::string&);

int part1(const Grid&);

int part2(Grid);
