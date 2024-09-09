// Project Identifier: 950181F63D0A883F183EC0A5CC67B19928FE896A
#include <iostream>
#include <getopt.h>
#include <queue>
#include <deque>
#include "station.h"

using namespace std;

int main (int argc, char* argv[]) {
    //getoptlong time
    ios_base::sync_with_stdio(false);

    //cout << "good morning \n";

    static struct option long_options[] = {
    {"stack",       no_argument,        NULL,  's'},
    {"queue",       no_argument,        NULL,  'q'},
    {"output",      required_argument,  0,     'o'},
    {"help",        no_argument,        NULL,  'h'},
    {0,             0,                  0,      0 }
    };
    int option_index = 0;

    //variables for input processing
    char routing_mode = 0;
    char output_mode = 0;

    int c = getopt_long(argc, argv, "sqo:h", long_options, &option_index);
    while (c != -1) {
        switch(c) {
            case 'h' :
                cout << "USAGE: ./ship\n" 
                     << "Routing Mode:\n"
                     << "   -s/--stack (DFS)\n"
                     << "   -q/--queue (BFS)\n"
                     << "Output Format:\n"
                     << "   -o/--output (M|L)\n"
                     << "       M: map format (default)\n"
                     << "       L: coordinate list format\n";
                exit(0);
                break;
            case 's' :
                if (routing_mode != 0) {
                    cerr << "Multiple routing modes specified";
                    exit(1);
                } else routing_mode = 's';
                break;
            case 'q' :
                if (routing_mode != 0) {
                    cerr << "Multiple routing modes specified";
                    exit(1);
                } else routing_mode = 'q';
                break;
            case 'o' :
                output_mode = *optarg;
                if (!(output_mode == 'M' || output_mode == 'L')) {
                    cerr << "Invalid output mode specified";
                    exit(1);
                }
                break;
        }
        c = getopt_long(argc, argv, "sqo:h", long_options, &option_index);
    }

    if (routing_mode == 0) {
        cerr << "No routing mode specified";
        exit(1);
    }

    Station station((routing_mode == 's'));

    station.solve();
    
    if (output_mode == 'M') station.mapOut();
    else station.listOut();

    return 0;
}