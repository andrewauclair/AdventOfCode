#include "day_15.h"

#include <iostream>
#include <fstream>
#include <string>

#include <vector>
#include <map>

#include <algorithm>
#include <sstream>
#include <deque>
#include <set>

struct day15_data
{
	std::vector<std::vector<int>> points{};
};

day15_data read_day_15_strings(std::fstream& input)
{
	day15_data data{};

	std::string str{};

	bool reading_folds{};

	while (getline(input, str))
	{
		std::stringstream ss{ str };

		std::vector<int> points{};
		
		for (size_t i = 0; i < str.size(); i++)
		{
			points.push_back(str.at(i) - 48);
		}
		data.points.push_back(points);
		
	}

	return data;
}

// A C++ Program to implement A* Search Algorithm
#include "math.h"
#include <array>
#include <chrono>
#include <cstring>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <tuple>
using namespace std;

// Creating a shortcut for int, int pair type
typedef pair<int, int> Pair;
// Creating a shortcut for tuple<int, int, int> type
typedef tuple<double, int, int> Tuple;

// A structure to hold the necessary parameters
struct cell {
    // Row and Column index of its parent
    Pair parent;
    // f = g + h
    double f, g, h;
    cell()
        : parent(-1, -1)
        , f(-1)
        , g(-1)
        , h(-1)
    {
    }
};

// A Utility Function to check whether given cell (row, col)
// is a valid cell or not.
bool isValid(const std::vector<std::vector<int>>& grid,
    const Pair& point)
{ // Returns true if row number and column number is in
  // range
        return (point.first >= 0) && (point.first < grid.size())
        && (point.second >= 0)
        && (point.second < grid.size());
}

// A Utility Function to check whether the given cell is
// blocked or not
bool isUnBlocked(const std::vector<std::vector<int>>& grid,
    const Pair& point)
{
    // Returns true if the cell is not blocked else false
    /*return isValid(grid, point)
        && grid[point.first][point.second] == 1;*/
    return true;
}

// A Utility Function to check whether destination cell has
// been reached or not
bool isDestination(const Pair& position, const Pair& dest)
{
    return position == dest;
}

// A Utility Function to calculate the 'h' heuristics.
double calculateHValue(const Pair& src, int src_risk, const Pair& dest, int dest_risk)
{
    // h is estimated with the two points distance formula
    //return sqrt(pow((src.first - dest.first), 2.0)
        //+ pow((src.second - dest.second), 2.0));
    return dest_risk;
}

// A Utility Function to trace the path from the source to
// destination
void tracePath(
    const std::vector<std::vector<cell>>& cellDetails,
    const Pair& dest)
{
    printf("\nThe Path is ");

    stack<Pair> Path;

    int row = dest.second;
    int col = dest.second;
    Pair next_node = cellDetails[row][col].parent;
    do {
        Path.push(next_node);
        next_node = cellDetails[row][col].parent;
        row = next_node.first;
        col = next_node.second;
    } while (cellDetails[row][col].parent != next_node);

    Path.emplace(row, col);
    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();
        printf("-> (%d,%d) ", p.first, p.second);
    }
}

int total_risk_of_path(const std::vector<std::vector<int>>& grid,
    const std::vector<std::vector<cell>>& cellDetails,
    const Pair& dest)
{
    printf("\nThe Path cost is ");

    stack<Pair> Path;

    int total_risk{};

    Path.push(dest);

    Pair next_node = cellDetails[dest.first][dest.second].parent;
    int row = next_node.first;
    int col = next_node.second;

    do {
        Path.push(next_node);
        next_node = cellDetails[row][col].parent;
        row = next_node.first;
        col = next_node.second;
    } while (cellDetails[row][col].parent != next_node);

    //Path.emplace(row, col); // don't need to count the cost of the position we're already in
    while (!Path.empty()) {
        Pair p = Path.top();
        Path.pop();

        int risk = grid.at(p.first).at(p.second);
        total_risk += risk;
        //printf("-> (%d,%d) ", p.first, p.second);
    }
    printf("%d", total_risk);
    return total_risk;
}

// A Function to find the shortest path between a given
// source cell to a destination cell according to A* Search
// Algorithm
int aStarSearch(const std::vector<std::vector<int>>& grid,
    const Pair& src, const Pair& dest, bool allow_diagonals)
{
    // If the source is out of range
    if (!isValid(grid, src)) {
        printf("Source is invalid\n");
        return 0;
    }

    // If the destination is out of range
    if (!isValid(grid, dest)) {
        printf("Destination is invalid\n");
        return 0;
    }

    // Either the source or the destination is blocked
    if (!isUnBlocked(grid, src)
        || !isUnBlocked(grid, dest)) {
        printf("Source or the destination is blocked\n");
        return 0;
    }

    // If the destination cell is the same as source cell
    if (isDestination(src, dest)) {
        printf("We are already at the destination\n");
        return 0;
    }

    // Create a closed list and initialise it to false which
    // means that no cell has been included yet This closed
    // list is implemented as a boolean 2D array
    std::vector<std::vector<bool>> closedList(grid.size());
    for (size_t i = 0; i < grid.size(); i++)
    {
        closedList.at(i).resize(grid.size());
    }
    //memset(closedList, false, sizeof(closedList));

    // Declare a 2D array of structure to hold the details
    // of that cell
    std::vector<std::vector<cell>> cellDetails(grid.size());
    for (size_t i = 0; i < grid.size(); i++)
    {
        cellDetails.at(i).resize(grid.size());
    }

    int i, j;
    // Initialising the parameters of the starting node
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent = { i, j };

    /*
    Create an open list having information as-
    <f, <i, j>>
    where f = g + h,
    and i, j are the row and column index of that cell
    Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    This open list is implemented as a set of tuple.*/
    std::priority_queue<Tuple, std::vector<Tuple>,
        std::greater<Tuple> >
        openList;

    // Put the starting cell on the open list and set its
    // 'f' as 0
    openList.emplace(0.0, i, j);

    // We set this boolean value as false as initially
    // the destination is not reached.
    while (!openList.empty()) {
        const Tuple& p = openList.top();
        // Add this vertex to the closed list
        i = get<1>(p); // second element of tupla
        j = get<2>(p); // third element of tupla

        // Remove this vertex from the open list
        openList.pop();
        closedList[i][j] = true;
        /*
                Generating all the 8 successor of this cell
                        N.W N N.E
                        \ | /
                        \ | /
                        W----Cell----E
                                / | \
                        / | \
                        S.W S S.E

                Cell-->Popped Cell (i, j)
                N --> North     (i-1, j)
                S --> South     (i+1, j)
                E --> East     (i, j+1)
                W --> West         (i, j-1)
                N.E--> North-East (i-1, j+1)
                N.W--> North-West (i-1, j-1)
                S.E--> South-East (i+1, j+1)
                S.W--> South-West (i+1, j-1)
        */
        for (int add_x = -1; add_x <= 1; add_x++) {
            for (int add_y = -1; add_y <= 1; add_y++) {

                if (add_x != 0 && add_y != 0 && !allow_diagonals) continue;

                Pair neighbour(i + add_x, j + add_y);
                // Only process this cell if this is a valid
                // one
                if (isValid(grid, neighbour)) {
                    // If the destination cell is the same
                    // as the current successor
                    if (isDestination(
                        neighbour,
                        dest)) { // Set the Parent of
                                 // the destination cell
                        cellDetails[neighbour.first]
                            [neighbour.second]
                        .parent
                            = { i, j };
                        printf("The destination cell is "
                            "found\n");
                        tracePath(cellDetails, dest);
                        
                        return total_risk_of_path(grid, cellDetails, dest);
                    }
                    // If the successor is already on the
                    // closed list or if it is blocked, then
                    // ignore it.  Else do the following
                    else if (!closedList[neighbour.first]
                        [neighbour.second]
                    && isUnBlocked(grid,
                        neighbour)) {
                        double gNew, hNew, fNew;
                        gNew = cellDetails[i][j].g + grid[neighbour.first][neighbour.second];// +1.0;
                        hNew = calculateHValue(neighbour, grid[neighbour.first][neighbour.second],
                            dest, grid[dest.first][dest.second]);
                        fNew = gNew + hNew;

                        // If it isn’t on the open list, add
                        // it to the open list. Make the
                        // current square the parent of this
                        // square. Record the f, g, and h
                        // costs of the square cell
                        //             OR
                        // If it is on the open list
                        // already, check to see if this
                        // path to that square is better,
                        // using 'f' cost as the measure.
                        if (cellDetails[neighbour.first]
                            [neighbour.second]
                        .f
                            == -1
                            || cellDetails[neighbour.first]
                            [neighbour.second]
                        .f
        > fNew) {
                            openList.emplace(
                                fNew, neighbour.first,
                                neighbour.second);

                            // Update the details of this
                            // cell
                            cellDetails[neighbour.first]
                                [neighbour.second]
                            .g
                                = gNew;
                            cellDetails[neighbour.first]
                                [neighbour.second]
                            .h
                                = hNew;
                            cellDetails[neighbour.first]
                                [neighbour.second]
                            .f
                                = fNew;
                            cellDetails[neighbour.first]
                                [neighbour.second]
                            .parent
                                = { i, j };
                        }
                    }
                }
            }
        }
    }

    // When the destination cell is not found and the open
    // list is empty, then we conclude that we failed to
    // reach the destiantion cell. This may happen when the
    // there is no way to destination cell (due to
    // blockages)
    printf("Failed to find the Destination Cell\n");
    return 0;
}


void dijkstra(const std::vector<std::vector<int>>& G, int n, int startnode) {
	std::vector<std::vector<int>> cost(G.size());

	for (size_t i = 0; i < G.size(); i++)
	{
		cost.at(i).resize(G.size());
	}

	std::vector<int> distance(G.size());
	std::vector<int> pred(G.size());

	std::vector<int> visited(G.size());

	int count{};
	int mindistance{};
	int nextnode{};
	int i{};
	int j{};
	//int cost[max][max], distance[max], pred[max];
	//int visited[max], count, mindistance, nextnode, i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (G[i][j] == 0)
				cost[i][j] = INFINITY;
			else
				cost[i][j] = G[i][j];
	for (i = 0; i < n; i++) {
		distance[i] = cost[startnode][i];
		pred[i] = startnode;
		visited[i] = 0;
	}
	distance[startnode] = 0;
	visited[startnode] = 1;
	count = 1;
	while (count < n - 1) {
		mindistance = INFINITY;
		for (i = 0; i < n; i++)
			if (distance[i] < mindistance && !visited[i]) {
				mindistance = distance[i];
				nextnode = i;
			}
		visited[nextnode] = 1;
		for (i = 0; i < n; i++)
			if (!visited[i])
				if (mindistance + cost[nextnode][i] < distance[i]) {
					distance[i] = mindistance + cost[nextnode][i];
					pred[i] = nextnode;
				}
		count++;
	}
	for (i = 0; i < n; i++)
		if (i != startnode) {
			std::cout << "\nDistance of node" << i << "=" << distance[i];
			std::cout << "\nPath=" << i;
			j = i;
			do {
				j = pred[j];
				std::cout << "<-" << j;
			} while (j != startnode);
		}
}

void Day_15::run_part_1() const
{
	std::cout << "[Day 15] [Part 1]\n";

	std::fstream example_input{ read_input("day_15_example.txt") };
	std::fstream actual_input{ read_input("day_15_actual.txt") };

	std::cout << "Example: " << run_part_1(example_input) << '\n';
	std::cout << "Actual:  " << run_part_1(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_15::run_part_1(std::fstream& input) const
{
	const day15_data data{ read_day_15_strings(input) };

	//dijkstra(data.points, (int)data.points.size(), 0);

    aStarSearch(data.points, Pair{ 0, 0 }, Pair{ data.points.size() - 1, data.points.size() - 1 }, false);


	return "";
}

void Day_15::run_part_2() const
{
	std::cout << "[Day 15] [Part 2]\n";

	std::fstream example_input{ read_input("day_15_example.txt") };
	std::fstream actual_input{ read_input("day_15_actual.txt") };

	std::cout << "Example: " << run_part_2(example_input) << '\n';
	std::cout << "Actual:  " << run_part_2(actual_input) << '\n';
	std::cout << '\n';
}

std::string Day_15::run_part_2(std::fstream& input) const
{
	const day15_data data{ read_day_15_strings(input) };

    std::vector<std::vector<int>> points{};

    for (size_t x = 0; x < data.points.size() * 5; x++)
    {
        std::vector<int> row_points{};

        for (size_t y = 0; y < data.points.size() * 5; y++)
        {
            int risk = data.points[x % data.points.size()][y % data.points.size()];

            int x_mult = x / data.points.size();
            int y_mult = y / data.points.size();

            int mult = x_mult + y_mult;// ? x_mult : y_mult;

            //mult++;

            risk += mult;

            if (risk > 9)
            {
                risk %= 9;
            }

            row_points.push_back(risk);
        }
        points.push_back(row_points);
    }

    aStarSearch(points, Pair{ 0, 0 }, Pair{ points.size() - 1, points.size() - 1 }, false);

	return "";
}
