#include <algorithm>
#include <fstream>
#include <limits>
#include <queue>
#include <stdexcept>

#include "lib.hpp"

std::size_t PointHash::operator()(const Point& p) const noexcept
{
    const std::size_t h1 = std::hash<size_t>{}(p.x);
    const std::size_t h2 = std::hash<size_t>{}(p.y);
    return h1 ^ (h2 << 1); // or use boost::hash_combine
}

size_t Graph::size() const noexcept
{
    return adj_list_.size();
}

Graph::Graph(const Grid& g)
{
    for (size_t y{ 0 }; y < g.size(); ++y)
    {
        for (size_t x{ 0 }; x < g.front().size(); ++x)
        {
            Point p{ x, y };
            risk_level_[p] = g[y][x];
            // North neighbor
            if (y > 0)
            {
                adj_list_[p].emplace_back(Point{ x, y - 1 });
            }
            // East neighbor
            if (x < g.front().size() - 1)
            {
                adj_list_[p].emplace_back(Point{ x + 1, y });
            }
            // South neighbor
            if (y < g.size() - 1)
            {
                adj_list_[p].emplace_back(Point{ x, y + 1 });
            }
            // West neighbor
            if (x > 0)
            {
                adj_list_[p].emplace_back(Point{ x - 1, y });
            }
        }
    }
}

std::vector<Point> Graph::get_vertices() const
{
    std::vector<Point> vertices;
    for (const auto& kv: adj_list_)
    {
        vertices.emplace_back(kv.first);
    }
    return vertices;
}

std::vector<Point> Graph::get_neighbors(const Point& p) const
{
    return adj_list_.at(p);
}

int Graph::get_risk_level(const Point& p) const
{
    return risk_level_.at(p);
}

Grid read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    Grid grid;

    std::string line;
    while (std::getline(in, line))
    {
        std::vector<int> row;
        for (const auto c: line)
        {
            row.push_back(c - '0');
        }
        grid.emplace_back(row);
    }

    return grid;
}

int dijkstra_shortest_path(const Grid& grid)
{
    Graph graph(grid);
    std::unordered_map<Point, int, PointHash> dist;
    std::unordered_map<Point, Point, PointHash> prev;

    auto cmp = [&dist](Point left, Point right)
    { return (dist[left] > dist[right]); };
    std::priority_queue<Point, std::vector<Point>, decltype(cmp)> min_q(cmp);

    for (const auto p: graph.get_vertices())
    {
        dist[p] = std::numeric_limits<int>::max(); // Set all distances to "infinity"
        min_q.push(p);
    }

    dist[Point{ 0, 0 }] = 0; // Starting point
    min_q.push(Point{ 0, 0 });

    while (!min_q.empty())
    {
        auto u{ min_q.top() };
        min_q.pop();
        for (const auto& v: graph.get_neighbors(u))
        {
            if (dist[v] > dist[u] + graph.get_risk_level(v))
            {
                dist[v] = dist[u] + graph.get_risk_level(v);
                prev[v] = u; // Keep track of previous point
                min_q.push(v);
            }
        }
    }

    // Trace path from end to start and accumulate total_risk
    auto total_risk{ 0 };
    auto ending_x{ grid.front().size() - 1 };
    auto ending_y{ grid.size() - 1 };
    Point point_on_path{ ending_x, ending_y };
    while (point_on_path != Point{ 0, 0 })
    {
        total_risk += graph.get_risk_level(point_on_path);
        point_on_path = prev[point_on_path];
    }

    return total_risk;
}

int part1(const Grid& grid)
{
    return dijkstra_shortest_path(grid);
}

int part2(Grid grid)
{
    const auto original_max_x{ grid.front().size() };
    const auto original_max_y{ grid.size() };
    // Expand to the right
    for (size_t y{ 0 }; y < grid.size(); ++y)
    {
        for (auto i{ 0 }; i < 4; ++i)
        {
            auto end{ grid[y].size() };
            auto start{ end - original_max_x };
            for (auto x{ start }; x < end; ++x)
            {
                auto new_value{ grid[y][x] == 9 ? 1 : grid[y][x] + 1 };
                grid[y].push_back(new_value);
            }
        }
    }

    // Expand down
    for (auto i{ 0 }; i < 4; ++i)
    {
        auto end{ grid.size() };
        auto start{ end - original_max_y };
        for (auto y{ start }; y < end; ++y)
        {
            std::vector<int> new_row;
            std::transform(grid.at(y).begin(), grid.at(y).end(), std::back_inserter(new_row), [](int a)
            { return a == 9 ? 1 : a + 1; });
            grid.emplace_back(new_row);
        }
    }
    return dijkstra_shortest_path(grid);
}
