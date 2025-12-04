#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <iostream>
#include <string>
enum CellType {
    EMPTY,
    ROAD,
    SPAWN,
    DESPAWN,
    MERGE,
    CROSS
};
class Renderer {
public:
    Renderer(int width, int height);
    void init_render();
    void update_render();
    void change_object(int x, int y, bool occupied, CellType type);  // Ensure CellType is used
    void print_grid();

private:
    int grid_width;
    int grid_height;
    double time_step;
    int time_counter;

    struct Cell {
        bool occupied;
        CellType type;
    };

    std::vector<std::vector<Cell>> grid;

    void clear();
    void draw_grid();
    void display();
};

#endif
