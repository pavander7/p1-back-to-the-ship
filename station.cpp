// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#include <string>
#include<sstream>
#include "station.h"

using namespace std;

// helpers

bool valid_space(char val) {
    if (val == '.') return true;
    else if (val == '#') return true;
    else if (val == 'S') return true;
    else if (val == 'H') return true;
    else if (val == 'E') return true;
    else return false;
}

struct Node {
    size_t l, r, c;
    char prev;
};

vector<Node> makePath(Vertex* curr) {
    vector<Node> path;
    path.push_back({curr->lev, curr->row, curr->col, 'H'});
    Vertex* prev = curr;
    curr = curr->prev;
    while (curr->prev != nullptr) {
        char p;
        if (prev->lev != curr->lev) p = char(prev->lev);
        else if (prev->row < curr->row) p = 'w';
        else if (prev->row > curr->row) p = 'e';
        else if (prev->col < curr->col) p = 'n';
        else p = 's';
        path.push_back({curr->lev, curr->row, curr->col, p});
        prev = curr;
        curr = curr->prev;
    } return path;
}

// Station

Station::Station(bool mode_in) : searchBot(mode_in) {
    char input_mode;
    size_t levels, N;
    cin >> input_mode >> levels >> N;
    string line;
    if (input_mode == 'M') { // Map input
        this->grid.reserve(levels);
        this->d_grid.reserve(levels);
        for (size_t l = 0; l < levels; l++) {
            vector<vector<char>> temp_level;
            vector<vector<bool>> d_temp_level;
            temp_level.reserve(N);
            d_temp_level.reserve(N);
            for (size_t r = 0; r < N; r++) {
                vector<char> temp_row;
                vector<bool> d_temp_row;
                temp_row.reserve(N);
                d_temp_row.reserve(N);
                getline(cin, line);
                while (line[0] == '/') {
                    getline(cin, line);
                }
                istringstream row_in(line);
                for (size_t c = 0; c < N; c++) {
                    char temp_char;
                    row_in >> temp_char;
                    if (valid_space(temp_char)) {
                        temp_row.push_back(temp_char);
                        d_temp_row.push_back(false);
                        if (temp_char == 'S') {
                            start_l = l;
                            start_r = r;
                            start_c = c;
                        }
                    } else {
                        cerr << "Invalid map character";
                        exit(1);
                    }
                }
                temp_level.push_back(temp_row);
                d_temp_level.push_back(d_temp_row);
            }
            grid.push_back(temp_level);
            d_grid.push_back(d_temp_level);
        }
    } else { // List input
        this->grid.reserve(levels);
        this->d_grid.reserve(levels);
        for (size_t l = 0; l < levels; l++) {
            vector<vector<char>> temp_level;
            vector<vector<bool>> d_temp_level;
            temp_level.reserve(N);
            d_temp_level.reserve(N);
            for (size_t r = 0; r < N; r++) {
                vector<char> temp_row;
                vector<bool> d_temp_row;
                temp_row.reserve(N);
                d_temp_row.reserve(N);
                for (size_t c = 0; c < N; c++) {
                    temp_row.push_back('.');
                    d_temp_row.push_back(false);
                }
                temp_level.push_back(temp_row);
                d_temp_level.push_back(d_temp_row);
            }
            grid.push_back(temp_level);
            d_grid.push_back(d_temp_level);
        }
        while (getline(cin, line)) {
            while (line[0] == '/') {
                getline(cin, line);
            }
            size_t level = 0;
            size_t q = 1;
            while (line[q] != ',') {
                level *= 10;
                level += static_cast<size_t>(line[q] - '0');
                q++;
            } if (level > levels) {
                cerr << "Invalid map level";
                exit(1);
            }
            size_t row = 0;
            while (line[q] != ',') {
                row *= 10;
                row += static_cast<size_t>(line[q] - '0');
                q++;
            } if (row > N) {
                cerr << "Invalid map row";
                exit(1);
            }
            q++;
            size_t col = 0;
            while (line[q] != ',') {
                col *= 10;
                col += static_cast<size_t>(line[q] - '0');
                q++;
            } if (col > N) {
                cerr << "Invalid map column";
                exit(1);
            } q++;
            char val = line[q];
            if (valid_space(val)) {
                grid[level][row][col] = val;
                if (val == 'S') {
                    start_l = level;
                    start_r = row;
                    start_c = col;
                }
            } else {
                cerr << "Invalid map character";
                exit(1);
            }
        }
    }
}

void Station::solve() {
    discover(start_l, start_r, start_c, nullptr);
    while (!searchBot.empty()) {
        auto curr = searchBot.top();
        searchBot.pop();
        backtrace.push_back(curr);
        if (investigate(curr)) break;
    }
}

bool Station::discover(size_t l, size_t r, size_t c, Vertex* p) {
    if (grid[l][r][c] == 'H') {
        Vertex* val = new Vertex({l,r,c,p});
        backtrace.push_back(val);
        return true;
    }
    else if (grid[l][r][c] != '#') {
        Vertex* val = new Vertex({l,r,c,p});
        searchBot.push(val);
        d_grid[l][r][c] = true;
        return false;
    } return false;
}

bool Station::investigate(Vertex* loc) {
    bool end = false;
    if (loc->row > 0) {
        if (discover(loc->lev, loc->row - size_t(1), loc->col, loc)) end = true;
    } if (loc->col < grid[0].size()) {
        if (discover(loc->lev, loc->row, loc->col + size_t(1), loc)) end = true;
    } if (loc->row < grid[0].size()) {
        if (discover(loc->lev, loc->row + size_t(1), loc->col, loc)) end = true;
    } if (loc->col > 0) {
        if (discover(loc->lev, loc->row, loc->col - size_t(1), loc)) end = true;
    } if (grid[loc->lev][loc->row][loc->col] == 'E') {
        for (size_t l = 0; l < grid.size(); l++) {
            if (grid[l][loc->row][loc->col] == 'E') {
                if(discover(l, loc->row, loc->col, loc)) end = true;
            }
        }
    } return end;
}

void Station::listOut() {
    Vertex* curr = backtrace.back();
    vector<Node> path = makePath(curr);
    cout << "//path taken\n";
    for (auto &loc : path) {
        cout << '(' << loc.l << ',' << loc.r << ',' << loc.c << ',' << loc.prev << ')' << endl;
    }
}

void Station::mapOut() {
    Vertex* curr = backtrace.back();
    vector<Node> path = makePath(curr);
    for (auto &loc : path) {
        grid[loc.l][loc.r][loc.c] = loc.prev;
    }
    cout << "Start in level " << start_l << ", row " << start_r << ", column " << start_c << endl;
    for (size_t l = 0; l < grid.size(); l++) {
        cout << "//level " << l << endl;
        for (size_t r = 0; r < grid[l].size(); r++) {
            for (size_t c = 0; c < grid[l][r].size(); c++) {
                cout << grid[l][r][c];
            } cout << endl;
        } 
    }
}

Station::~Station() {
    while (!backtrace.empty()) {
        Vertex* curr = backtrace.front();
        backtrace.pop_front();
        delete curr;
    }
}
