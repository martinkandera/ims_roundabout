#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <iostream>
#include <string>

// Define the CellType enum here
enum CellType {
    EMPTY,
    ROAD,
    SPAWN,
    DESPAWN,
    MERGE,
    CROSS
};

class Graph {
public:
    Graph(int width, int height);
    void ini_array(int width, int height);
    void set_cell(int x, int y, bool occupied, CellType type);
    bool is_occupied(int x, int y);
    CellType get_cell_type(int x, int y);
    void print_grid();

private:
    int grid_width;
    int grid_height;
    std::vector<std::vector<std::pair<bool, CellType>>> grid;  // Pair: (occupied, type)
};

#endif
