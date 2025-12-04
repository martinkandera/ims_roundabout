#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>  // Include this for time and sleep functionality
#include <thread>  // Include this for sleep functionality
#include "debug.h"
#include "renderer.h"

Renderer::Renderer(int width, int height) {
    grid_width = width;
    grid_height = height;
    time_step = 0.0;
    time_counter = 0;

    // Initialize the grid with EMPTY as the default type
    grid.resize(grid_height, std::vector<Cell>(grid_width, {false, CellType::EMPTY}));
}

void Renderer::init_render() {
    std::cout << "╔═══════════════════════════════════╗" << std::endl;
    std::cout << "║     IMS projekt 25/26             ║" << std::endl;
    std::cout << "║                                   ║" << std::endl;
    std::cout << "║     Simulacia dopravy v           ║" << std::endl;
    std::cout << "║     dopravnom uzle/križovatke     ║" << std::endl;
    std::cout << "╚═══════════════════════════════════╝" << std::endl;

    std::cout << std::endl;

    std::cout << "Simulovana časť ma rozmery " << grid_width << "x" << grid_height << "." << std::endl;
    std::cout << "Čas: " << time_counter << std::endl;

    print_grid();

	std::cout << "[Pre štart stlačte Enter.]" << std::endl;
}

void Renderer::update_render() {
    clear();
    time_counter++;
    std::cout << "╔═══════════════════════════════════╗" << std::endl;
    std::cout << "║     IMS projekt 25/26             ║" << std::endl;
    std::cout << "║                                   ║" << std::endl;
    std::cout << "║     Simulacia dopravy v           ║" << std::endl;
    std::cout << "║     dopravnom uzle/križovatke     ║" << std::endl;
    std::cout << "╚═══════════════════════════════════╝" << std::endl;

    std::cout << std::endl;

    std::cout << "Simulovana časť ma rozmery " << grid_width << "x" << grid_height << "." << std::endl;
    std::cout << "Čas: " << time_counter << std::endl;
    std::cout << std::endl;

    print_grid();
    std::cout << std::endl;

    std::cout << "[Pre pauzu stlačte Enter.]" << std::endl;
}

void Renderer::change_object(int x, int y, bool occupied, CellType type) {
    if (x >= 0 && x < grid_width && y >= 0 && y < grid_height) {
        grid[y][x].occupied = occupied;
        grid[y][x].type = type;
    }
}


void Renderer::print_grid() {
    draw_grid();
}

void Renderer::clear() {
    std::cout << "[2J[H";  // Clear the terminal screen and move the cursor to the top left.
}

void Renderer::draw_grid() {
    std::cout << "╔";
    for (int i = 0; i < (grid_width * 2 + 1); i++) { std::cout << "═"; }
    std::cout << "╗";
    std::cout << std::endl;

    // Definícia farieb pomocou ANSI escape kódov
    const std::string RESET = "[0m";    // Reset farby
    const std::string ROAD_COLOR = "[34m";  // Modrá pre ROAD
    const std::string SPAWN_COLOR = "[32m"; // Zelená pre SPAWN
    const std::string DESPAWN_COLOR = "[31m"; // Červená pre DESPAWN
    const std::string MERGE_COLOR = "[33m";  // Žltá pre MERGE
    const std::string CROSS_COLOR = "[35m";  // Fialová pre CROSS
    const std::string EMPTY_COLOR = "[37m";  // Biela pre EMPTY

    for (int y = 0; y < grid_height; y++) {
        std::cout << "║ "; // Vytvárame okraj pre každý riadok

        for (int x = 0; x < grid_width; x++) {
            std::string symbol = " ";
            std::string color = EMPTY_COLOR; // Predvolená farba pre prázdne bunky

            if (grid[y][x].occupied) {
                symbol = "●";  // Obsadené bunky
            } else {
                symbol = "○";  // Prázdne bunky
            }

            // Nastavenie farby na základe typu bunky
            switch (grid[y][x].type) {
                case CellType::ROAD:
                    color = ROAD_COLOR;
                    break;
                case CellType::SPAWN:
                    color = SPAWN_COLOR;
                    break;
                case CellType::DESPAWN:
                    color = DESPAWN_COLOR;
                    break;
                case CellType::MERGE:
                    color = MERGE_COLOR;
                    break;
                case CellType::CROSS:
                    color = CROSS_COLOR;
                    break;
                case CellType::EMPTY:
                    symbol = " ";  // Ak je prázdna, necháme symbol prázdny
                    color = EMPTY_COLOR;
                    break;
            }

            // Aplikovanie farby na symbol a jeho výpis
            std::cout << color << symbol << " " << RESET;  // Resetovanie farby po každom symbole
        }

        std::cout << "║";
        std::cout << std::endl;
    }

    std::cout << "╚";
    for (int i = 0; i < (grid_width * 2 + 1); i++) { std::cout << "═"; }
    std::cout << "╝";
    std::cout << std::endl;
}
