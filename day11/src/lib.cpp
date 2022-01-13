#include <fstream>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <utility>

#include "lib.hpp"

using Vector10 = Eigen::Array< int, 10, 1 >;

using Point = std::pair<int, int>;

inline bool operator==(const Point& lhs, const Point& rhs) noexcept
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

// https://en.cppreference.com/w/cpp/utility/hash:
struct PointHash
{
    std::size_t operator()(Point const& p) const noexcept
    {
        const std::size_t h1 = std::hash<size_t>{}(p.first);
        const std::size_t h2 = std::hash<size_t>{}(p.second);
        return h1 ^ (h2 << 1); // or use boost::hash_combine
    }
};

Eigen::Matrix<int, 10, 10> read_input(const std::string& filename)
{
    std::fstream in{ filename };
    if (!in) throw std::runtime_error("File not found");

    Eigen::Matrix<int, 10, 10> grid;
    std::string line;

    for (auto r{ 0 }; r < 10; ++r)
    {
        std::getline(in, line);
        std::vector<int> row;
        for (const auto c : line)
        {
            row.push_back(c - '0');
        }
        grid.row(r) = Vector10(row.data());

    }
    return grid;
}

int flash_octopuses(Eigen::Matrix<int, 10, 10>& grid)
{
    // BFS

    std::queue<Point> q;
    std::unordered_map<Point, bool, PointHash> flashed;
    auto flashed_total{ 0 };

    // Put all octopuses which flashed when incrementing onto the queue
    for (auto col{ 0 }; col < grid.cols(); ++col) {
        for (auto row{ 0 }; row < grid.rows(); ++row)
        {
            if (grid(row, col) == 10)
            {
                flashed[{row, col}] = true;
                q.push({ row,col });
            }
        }
    }

    // Process neighbors
    while (!q.empty())
    {
        Point p{ q.front() };
        q.pop();

        ++flashed_total;

        // Neighbors. Some might be out of bounds.
        const auto north{ std::make_pair(p.first - 1, p.second) };
        const auto northeast{ std::make_pair(p.first - 1, p.second + 1) };
        const auto east{ std::make_pair(p.first,     p.second + 1) };
        const auto southeast{ std::make_pair(p.first + 1, p.second + 1) };
        const auto south{ std::make_pair(p.first + 1, p.second) };
        const auto southwest{ std::make_pair(p.first + 1, p.second - 1) };
        const auto west{ std::make_pair(p.first,     p.second - 1) };
        const auto northwest{ std::make_pair(p.first - 1, p.second - 1) };

        // North
        if (north.first >= 0) // Check if out of bounds
        {
            ++grid(north.first, north.second);
            if (!flashed[north] && grid(north.first, north.second) > 9)
            {
                flashed[north] = true;
                q.push(north);
            }
        }

        // Northeast
        if (northeast.first >= 0 && northeast.second < grid.cols())
        {
            ++grid(northeast.first, northeast.second);
            if (!flashed[northeast] && grid(northeast.first, northeast.second) > 9)
            {
                flashed[northeast] = true;
                q.push(northeast);
            }
        }

        // East
        if (east.second < grid.cols())
        {
            ++grid(east.first, east.second);
            if (!flashed[east] && grid(east.first, east.second) > 9)
            {
                flashed[east] = true;
                q.push(east);
            }
        }

        // Southeast
        if (southeast.first < grid.rows() && southeast.second < grid.cols())
        {
            ++grid(southeast.first, southeast.second);
            if (!flashed[southeast] && grid(southeast.first, southeast.second) > 9)
            {
                flashed[southeast] = true;
                q.push(southeast);
            }
        }

        // South
        if (south.first < grid.rows())
        {
            ++grid(south.first, south.second);
            if (!flashed[south] && grid(south.first, south.second) > 9)
            {
                flashed[south] = true;
                q.push(south);
            }
        }

        // Southwest
        if (southwest.first < grid.rows() && southwest.second >= 0)
        {
            ++grid(southwest.first, southwest.second);
            if (!flashed[southwest] && grid(southwest.first, southwest.second) > 9)
            {
                flashed[southwest] = true;
                q.push(southwest);
            }
        }

        // West
        if (west.second >= 0)
        {
            ++grid(west.first, west.second);
            if (!flashed[west] && grid(west.first, west.second) > 9)
            {
                flashed[west] = true;
                q.push(west);
            }
        }

        // Northwest
        if (northwest.first >= 0 && northwest.second >= 0)
        {
            ++grid(northwest.first, northwest.second);
            if (!flashed[northwest] && grid(northwest.first, northwest.second) > 9)
            {
                flashed[northwest] = true;
                q.push(northwest);
            }
        }
    }
    return flashed_total;
}

int part1(Eigen::Matrix<int, 10, 10> grid)
{
    auto flashes{ 0 };

    for (auto step{ 1 }; step <= 100; ++step)
    {
        // Increment energy level
        for (auto col{ 0 }; col < grid.cols(); ++col)
        {
            for (auto row{ 0 }; row < grid.rows(); ++row)
            {
                ++grid(row, col);
            }
        }

        // Flash octopuses
        const auto flashes_per_step{ flash_octopuses(grid) };
        flashes += flashes_per_step;

        // Reset energy levels
        for (auto col{ 0 }; col < grid.cols(); ++col) {
            for (auto row{ 0 }; row < grid.rows(); ++row)
            {
                if (grid(row, col) > 9)
                {
                    grid(row, col) = 0;
                }
            }
        }

    }
    return flashes;
}

int part2(Eigen::Matrix<int, 10, 10> grid)
{
    auto synchronized_step{ -1 };
    auto step{ 1 };

    while (synchronized_step == -1)
    {
        // Increment energy level
        for (auto col{ 0 }; col < grid.cols(); ++col)
        {
            for (auto row{ 0 }; row < grid.rows(); ++row)
            {
                ++grid(row, col);
            }
        }

        // Flash
        const auto flashes_per_step{ flash_octopuses(grid) };
        if (flashes_per_step == 100) synchronized_step = step; // All 100 octopuses flash simultaneously

        // Reset
        for (auto col{ 0 }; col < grid.cols(); ++col) {
            for (auto row{ 0 }; row < grid.rows(); ++row)
            {
                if (grid(row, col) > 9)
                {
                    grid(row, col) = 0;
                }
            }
        }

        ++step;
    }

    return synchronized_step;
}
