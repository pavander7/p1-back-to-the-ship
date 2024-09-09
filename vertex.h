// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include <vector>

struct Vertex {
    size_t lev, row, col;
    char val;
    Vertex *prev;
};

#endif