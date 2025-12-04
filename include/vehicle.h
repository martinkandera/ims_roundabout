#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

class Vehicle {
public:
    int id;             // id vozidla
    int x, y;           // pozicia
    int direction;      // ktory vychod

    Vehicle(int id, int x, int y, std::string color, int direction)
        : id(id), x(x), y(y), color(color), direction(direction) {}

};

#endif
