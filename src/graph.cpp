#include "graph.h"

// Constructor to initialize the graph with the given width and height
Graph::Graph(int width, int height) {
    ini_array(width, height);
}

// Function to initialize the grid with the specified width and height
void Graph::ini_array(int width, int height) {
    grid_width = width;
    grid_height = height;
    grid.resize(grid_height, std::vector<std::pair<bool, CellType>>(grid_width, {false, EMPTY}));
}

// Function to set the value of a specific cell
void Graph::set_cell(int x, int y, bool occupied, CellType type) {
    if (x >= 0 && x < grid_width && y >= 0 && y < grid_height) {
        grid[y][x] = {occupied, type};  // Set the cell's occupied status and type
    } else {
        std::cerr << "ERROR: Coordinates out of bounds!" << std::endl;
    }
}

// Function to check if a specific cell is occupied
bool Graph::is_occupied(int x, int y) {
    if (x >= 0 && x < grid_width && y >= 0 && y < grid_height) {
        return grid[y][x].first;  // Return the occupied status of the cell
    }
    return false;
}

// Function to get the type of a specific cell
CellType Graph::get_cell_type(int x, int y) {
    if (x >= 0 && x < grid_width && y >= 0 && y < grid_height) {
        return grid[y][x].second;  // Return the type of the cell
    }
    return EMPTY;
}

// Function to print the grid (for debugging or visualization)
void Graph::print_grid() {
    for (int y = 0; y < grid_height; y++) {
        for (int x = 0; x < grid_width; x++) {
            char symbol = '.';
            switch (grid[y][x].second) {
                case ROAD: symbol = 'R'; break;
                case SPAWN: symbol = 'S'; break;
                case DESPAWN: symbol = 'D'; break;
                case MERGE: symbol = 'M'; break;
                case CROSS: symbol = '+'; break;
                default: break;
            }

            if (grid[y][x].first) {
                std::cout << "[" << symbol << "]";
            } else {
                std::cout << " " << symbol << " ";
            }
        }
        std::cout << std::endl;
    }
}
