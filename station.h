// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include <vector>

class Station {
public:
Station(bool mode);

private:
bool mode;
std::vector<std::vector<std::vector<char>>> grid;
};

#endif