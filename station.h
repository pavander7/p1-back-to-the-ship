// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include <vector>
#include "vertex.h"

class Station {
public:
    Station(bool mode);

private:
    bool mode;
    std::vector<std::vector<std::vector<char>>> grid;
    size_t start_l, start_r, start_c;
    class SearchContainer;
};

class Station::SearchContainer {
public:
    SearchContainer(bool mode);
    void push(Vertex*);
    Vertex* top();
    void pop();
private:
    std::deque<Vertex*> container;
    std::deque<Vertex*> backtrace;
    bool mode;
};

#endif