#include <iostream>
#include <map>
#include <fstream>
#include <sstream>

/**
 * CS515 Lab 12
 * File: wordfreq.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: May 8, 2021
 * Collaboration Declaration:
 * Assistance received from online resources
 * 		c++ docs
 */

using namespace std;

int main(int argc, char** argv) {
    stringstream s;
    ifstream infile;
    infile.open(argv[1]);
    if (infile.fail()) {    //handles file open error
        cout << "error opening " << argv[1] << " for input." << endl;
        return 0;
    }

    s << infile.rdbuf();    //read entire file
    infile.close();

    map<string, map<int, int> > word_map;   //map of <"word", <map of "year", frequency> >
    string a="", b="", c="", d="";
    while (s >> a >> b >> c >> d)
        if (stoi(b) >= 1800)                //ignore all dates before 1800
            word_map[a][stoi(b)] = stoi(c);

    while (!cin.eof()) {    //user interface:
        string q, y;
        cout << "Which word starting which year? ";
        cin >> q >> y;

        if (cin.eof())
            break;

        int start = stoi(y) >= 1800 ? stoi(y) : 1800;   //min year is always 1800
        map<int, int> m = word_map[q];      //m is the inner map for word queue
        map<int, int>::iterator it = m.find(start);
        while (it != m.end()) {             //iterate over the inner map
            cout << it->first << " " << it->second << endl;
            it++;
        }
    }
    cout << endl;
    return 0;
}
