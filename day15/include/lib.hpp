#pragma once

#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

using Grid = std::vector<std::vector<int>>;

struct Position
{
    size_t x{ 0 };
    size_t y{ 0 };
    int risk_when_queued{ std::numeric_limits<int>::max() }; // Risk at the given moment in time when added to min_q
};

inline bool operator==(const Position& lhs, const Position& rhs) noexcept
{
    // Ignore risk data member when determining equality between Positions
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

inline bool operator!=(const Position& lhs, const Position& rhs) noexcept
{
    return !(lhs == rhs);
}

// https://en.cppreference.com/w/cpp/utility/hash:
struct PositionHash
{
    std::size_t operator()(Position const& p) const noexcept;
};

class Graph
{
public:
    explicit Graph(const Grid&);

    [[nodiscard]] size_t size() const noexcept;

    [[nodiscard]] std::vector<Position> get_neighbors(const Position&) const;

    [[nodiscard]] int get_risk_level(const Position&) const;

    [[nodiscard]] std::vector<Position> get_vertices() const;

private:
    std::unordered_map<Position, std::vector<Position>, PositionHash> adj_list_;
    std::unordered_map<Position, int, PositionHash> risk_level_;
};

Grid read_input(const std::string&);

int part1(const Grid&);

Grid expand_grid(const Grid&);

int part2(const Grid&);
