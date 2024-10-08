// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include <vector>
#include "vertex.h"
#include "search.h"

class Station {
public:
    Station(bool mode_in);
    bool solve();

    void mapOut();
    void listOut();
    void blank_mapOut();

    ~Station();
private:
    size_t start_l, start_r, start_c;
    //size_t target_l, target_r, target_c;

    std::vector<std::vector<std::vector<char>>> grid;
    std::vector<std::vector<std::vector<bool>>> d_grid;
    std::deque<Vertex*> backtrace;

    SearchContainer searchBot;

    bool discover(size_t l, size_t r, size_t c, Vertex* p);
    bool investigate(Vertex* loc);
};

#endif