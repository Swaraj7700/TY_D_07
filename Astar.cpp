#include <list>
#include <algorithm>
#include <iostream>

class Point {
public:
    Point(int a = 0, int b = 0) : x(a), y(b) {}
    
    // Comparison operators for points
    bool operator==(const Point& o) const { return o.x == x && o.y == y; }
    bool operator!=(const Point& o) const { return !(*this == o); } // Added
    Point operator+(const Point& o) const { return Point(x + o.x, y + o.y); }
    
    int x, y;
};

class Map {
public:
    Map() {
        // Initialize a sample map (0 = free space, 1 = obstacle)
        char t[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 1, 1, 0},
            {0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 0, 0, 0, 1, 0},
            {0, 0, 1, 1, 1, 1, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
        };
        width = height = 8;
        std::copy(&t[0][0], &t[0][0] + 8*8, &grid[0][0]);
    }

    // Access the map
    int operator()(int x, int y) const { return grid[x][y]; }
    
    char grid[8][8]; // The map grid
    int width, height; // Dimensions of the map
};

class Node {
public:
    Point pos, parent; // Current position and parent position
    int cost; // Cost from start to this node
    int dist; // Estimated distance to end
    
    bool operator==(const Node& o) const { return pos == o.pos; }
    bool operator==(const Point& o) const { return pos == o; }
    bool operator<(const Node& o) const { return (dist + cost) < (o.dist + o.cost); }
};

class AStar {
public:
    AStar() {
        // Define the possible movement directions (8 directions)
        neighbours[0] = Point(-1, -1); neighbours[1] = Point(1, -1);
        neighbours[2] = Point(-1, 1); neighbours[3] = Point(1, 1);
        neighbours[4] = Point(0, -1); neighbours[5] = Point(-1, 0);
        neighbours[6] = Point(0, 1); neighbours[7] = Point(1, 0);
    }

    // Heuristic function: squared Euclidean distance
    int calcDist(const Point& p) {
        int x = end.x - p.x, y = end.y - p.y;
        return (x * x + y * y);
    }

    // Check if the point is within map bounds
    bool isValid(const Point& p) {
        return (p.x >= 0 && p.y >= 0 && p.x < map.width && p.y < map.height);
    }

    // Check if the point exists in open or closed lists with a better cost
    bool existPoint(const Point& p, int cost) {
        auto it = std::find(closed.begin(), closed.end(), p);
        if (it != closed.end()) {
            if ((it->cost + it->dist) < cost) return true;
            closed.erase(it);
        }
        
        it = std::find(open.begin(), open.end(), p);
        if (it != open.end()) {
            if ((it->cost + it->dist) < cost) return true;
            open.erase(it);
        }
        
        return false;
    }

    // Fill the open list with valid neighboring nodes
    bool fillOpen(Node& n) {
        for (int x = 0; x < 8; x++) {
            Point neighbour = n.pos + neighbours[x];

            // If we reached the end, we're done
            if (neighbour == end) return true;

            if (isValid(neighbour) && map(neighbour.x, neighbour.y) != 1) {
                int stepCost = 1 + (x >= 4); // Diagonal cost can be adjusted here
                int newCost = stepCost + n.cost;
                int dist = calcDist(neighbour);

                // Check if the neighbour is already in the open or closed lists
                if (!existPoint(neighbour, newCost + dist)) {
                    Node newNode;
                    newNode.cost = newCost; 
                    newNode.dist = dist; 
                    newNode.pos = neighbour; 
                    newNode.parent = n.pos;
                    open.push_back(newNode);
                }
            }
        }
        return false;
    }

    // A* search algorithm
    bool search(const Point& s, const Point& e, const Map& mp) {
        Node startNode;
        end = e; 
        start = s; 
        map = mp;

        startNode.cost = 0; 
        startNode.pos = s; 
        startNode.parent = Point(); 
        startNode.dist = calcDist(s);
        
        open.push_back(startNode);

        while (!open.empty()) {
            // Sort open list by cost + distance (A*)
            open.sort();
            Node current = open.front();
            open.pop_front();
            closed.push_back(current);

            // Fill open with neighbors
            if (fillOpen(current)) return true; // Found a path
        }
        return false; // No path found
    }

    // Construct the path from start to end
    int path(std::list<Point>& path) {
        path.push_front(end);
        int cost = closed.back().cost + 1; // Path cost
        path.push_front(closed.back().pos);
        Point parent = closed.back().parent;

        // Backtrack through parents to find the full path
        for (auto it = closed.rbegin(); it != closed.rend(); ++it) {
            if (it->pos == parent && it->pos != start) {
                path.push_front(it->pos);
                parent = it->parent;
            }
        }
        path.push_front(start);
        return cost;
    }

    Map map; // The map being used
    Point end, start; // Start and end points
    Point neighbours[8]; // Possible movement directions
    std::list<Node> open, closed; // Open and closed lists for A*
};

int main() {
    Map m; // Create the map
    Point start(0, 0), end(7, 7); // Define start and end points
    AStar as; // Create A* search instance

    // Perform the A* search
    if (as.search(start, end, m)) {
        std::list<Point> path; // To store the resulting path
        int cost = as.path(path); // Get the path
        
        // Output the map and path
        for (int y = -1; y < 9; y++) {
            for (int x = -1; x < 9; x++) {
                if (x < 0 || y < 0 || x > 7 || y > 7 || m(x, y) == 1)
                    std::cout << char(0xdb); // Obstacle
                else if (std::find(path.begin(), path.end(), Point(x, y)) != path.end())
                    std::cout << "x"; // Path
                else
                    std::cout << "."; // Free space
            }
            std::cout << "\n";
        }

        std::cout << "\nPath cost " << cost << ": ";
        for (const auto& p : path) {
            std::cout << "(" << p.x << ", " << p.y << ") "; // Print path points
        }
    }
    std::cout << "\n\n";
    return 0;
}

    