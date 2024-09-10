// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#include "search.h"

// SearchContainer

SearchContainer::SearchContainer(bool mode_in) : mode(mode_in) {}

bool SearchContainer::empty() {return container.empty();}

void SearchContainer::pop() {container.pop_front();}

Vertex* SearchContainer::top() {return container.front();}

void SearchContainer::push(Vertex* val) {
    if (mode) container.push_front(val);
    else container.push_back(val);
}

SearchContainer::~SearchContainer() {
    while (!container.empty()) {
        Vertex* curr = container.front();
        container.pop_front();
        delete curr;
    }
}