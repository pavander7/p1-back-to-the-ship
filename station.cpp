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
    if (input_mode == 'M') {
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
                    }
                }
                temp_level.push_back(temp_row);
            }
            grid.push_back(temp_level);
        }
    }
}