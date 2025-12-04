#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>  // For time and sleep functionality
#include <thread>  // For sleep functionality
#include "debug.h"
#include "renderer.h"
#include <fstream>
#include "nlohmann/json.hpp"


using json = nlohmann::json;  // Nastavenie aliasu pre json

// Funkcia na načítanie JSON súboru a extrahovanie hodnoty grid_width, grid_height a uzlov
void load_grid_dimensions(const std::string& file_path, int& width, int& height, double& time_step, std::vector<json>& nodes) {
    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        std::cerr << "Unable to open file: " << file_path << std::endl;
        exit(1);
    }

    nlohmann::json j;  // Použitie správneho aliasu pre json
    input_file >> j;  // Načíta celý JSON

    // Získaj hodnoty pre šírku, výšku a časový krok
    width = j["visualization"]["grid_width"];
    height = j["visualization"]["grid_height"];
    time_step = j["visualization"]["time_step"];
    data_collest = j["visualization"]["collect_data"];

    // Načítať uzly do vektora
    nodes = j["nodes"];

    std::cout << "Loaded grid dimensions: " << width << "x" << height << ", time_step: " << time_step << std::endl;
}

// Funkcia na zachytenie stavu terminálu pred jeho vyčistením
void capture_terminal_state(const std::string& filename = "terminal_state.txt") {
    std::ofstream out_file(filename);
    if (out_file.is_open()) {
        out_file << "Terminal content before clearing.\n";
        // Capture more content as necessary here
        out_file.close();
    }
}

// Funkcia na vyčistenie terminálu
void clear_terminal() {
    std::cout << "\033[2J\033[H";  // ANSI escape codes to clear the terminal
}

// Funkcia na obnovenie obsahu terminálu zo súboru
void restore_terminal_state(const std::string& filename = "terminal_state.txt") {
    std::ifstream in_file(filename);
    std::string line;
    if (in_file.is_open()) {
        while (std::getline(in_file, line)) {
            std::cout << line << std::endl;
        }
        in_file.close();
    }
}

// Struktúra na uchovávanie argumentov
struct Arguments {
    int timeValue = 0;
    std::string testValue = "";
    std::string filePath = "";
};

// Funkcia na parsovanie argumentov
Arguments parseArguments(int argc, char* argv[]) {
    Arguments args;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-t" && i + 1 < argc) {
            args.timeValue = std::stoi(argv[++i]);
            debugPrint("Time value set to: " + std::to_string(args.timeValue));
        }
        else if (arg == "-test" && i + 1 < argc) {
            args.testValue = argv[++i];
            debugPrint("Test type set to: " + args.testValue);
        }
        else if (arg == "-file" && i + 1 < argc) {
            args.filePath = argv[++i];
            debugPrint("File path set to: " + args.filePath);
        }
        else {
            debugPrint("Unknown argument: " + arg);
        }
    }

    if (args.filePath.empty()) {
        debugPrint("Error: -file argument is required.");
        exit(1);
    }

    return args;
}

int main(int argc, char* argv[]) {
    Arguments args = parseArguments(argc, argv);

    // Získaj veľkosť plochy a uzly z JSON
    int width = 20, height = 20, data_collest = 100;
    double time_step = 0.1;
    std::vector<json> nodes; // Premenná na ukladanie uzlov
    load_grid_dimensions(args.filePath, width, height, time_step, nodes); // Volanie funkcie na načítanie JSON

    capture_terminal_state();
    clear_terminal();

    Renderer renderer(width, height);

    renderer.init_render();

    // Načítať a vykresliť uzly
    for (const auto& node : nodes) {
        int x = node["positon_x"];
        int y = node["position_y"];
        std::string type = node["type"];

        // Urči typ uzla a vykresli ho
        if (type == "spawn") {
            renderer.change_object(x, y, false, SPAWN);  // Vykresli spawn
        } else if (type == "despawn") {
            renderer.change_object(x, y, false, DESPAWN);  // Vykresli despawn
        } else if (type == "road") {
            renderer.change_object(x, y, false, ROAD);  // Vykresli road
        } else if (type == "merge") {
            renderer.change_object(x, y, false, MERGE);  // Vykresli merge
        } else if (type == "cross") {
            renderer.change_object(x, y, false, CROSS);  // Vykresli cross
        }
    }

    // Simulácia každej sekundy (aktualizácia renderovania)

    for (int i = 0; i < args.timeValue ; i++) {
        renderer.update_render();
        std::this_thread::sleep_for(std::chrono::duration<double>(time_step));
    }

    // Obnova obsahu terminálu po skončení simulácie
    restore_terminal_state();

    return 0;
}
