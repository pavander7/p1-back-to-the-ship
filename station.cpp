// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A

#include <string>
#include<sstream>
#include "station.h"

using namespace std;

bool valid_space(char val) {
    if (val == '.') return true;
    else if (val == '#') return true;
    else if (val == 'S') return true;
    else if (val == 'H') return true;
    else if (val == 'E') return true;
    else return false;
}

Station::Station(bool mode) {
    char input_mode;
    size_t levels, N;
    cin >> input_mode >> levels >> N;
    string line;
    if (input_mode == 'M') { // Map input
        this->grid.reserve(levels);
        for (size_t l = 0; l < levels; l++) {
            vector<vector<char>> temp_level;
            temp_level.reserve(N);
            for (size_t r = 0; r < N; r++) {
                vector<char> temp_row;
                temp_row.reserve(N);
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
                        if (temp_char == 'S') {
                            start_l = l;
                            start_r = r;
                            start_c = c;
                        }
                    }
                }
                temp_level.push_back(temp_row);
            }
            grid.push_back(temp_level);
        }
    } else { // List input
        this->grid.reserve(levels);
        for (size_t l = 0; l < levels; l++) {
            vector<vector<char>> temp_level;
            temp_level.reserve(N);
            for (size_t r = 0; r < N; r++) {
                vector<char> temp_row;
                temp_row.reserve(N);
                for (size_t c = 0; c < N; c++) {
                    temp_row.push_back('.');
                }
                temp_level.push_back(temp_row);
            }
            grid.push_back(temp_level);
        }
        while (getline(cin, line)) {
            while (line[0] == '/') {
                getline(cin, line);
            }
            size_t level = line[1];
            size_t q = 3;
            size_t row = 0;
            while (line[q] != ',') {
                row *= 10;
                row += line[q];
                q++;
            } q++;
            size_t col = 0;
            while (line[q] != ',') {
                col *= 10;
                col += line[q];
                q++;
            } q++;
            char val = line[q];
            if (valid_space(val)) {
                grid[level][row][col] = val;
                if (val == 'S') {
                    start_l = level;
                    start_r = row;
                    start_c = col;
                }
            }
        }
    }
}

