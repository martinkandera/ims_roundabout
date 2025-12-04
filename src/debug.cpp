#include "debug.h"

bool DEBUG = true;  // Define DEBUG here

void debugPrint(const std::string& message) {
    if (!DEBUG) return;
    std::cout << "[DEBUG] " << message << std::endl;
}
