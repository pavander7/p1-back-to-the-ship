// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#ifndef SEARCH_H
#define SEARCH_H

#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include <vector>
#include "vertex.h"

class SearchContainer {
public:
    SearchContainer(bool mode_in);
    void push(Vertex*);
    void pop();

    Vertex* top();
    bool empty();

    ~SearchContainer();
private:
    std::deque<Vertex*> container;
    bool mode;
};

#endif