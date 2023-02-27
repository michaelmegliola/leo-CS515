#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <list>
using namespace std;

/**
 * CS515 Assignment 1
 * File: calSpan.cpp
 * Name: Leo Megliola
 * Section: 2L
 * Date: Feb 18, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 */

int main(int argc, char ** argv) {  //because the logic is linear, all code is in main

    const float BAD = 142.0;   //used for corrupt data

    if (argc != 3) {    //handles wrong number of arguments
        cout << "Wrong number of arguments" << endl;
        return 0;
    }

    stringstream s;
    ifstream infile;
    infile.open(argv[1]);
    if (infile.fail()) {    //handles file open error
        cout << "Error opening file" << endl;
        return 0;
    }

    s << infile.rdbuf();    //read entire file
    infile.close();

    string word;        //to store individual words
    list <float> vals;  //temp data storage
    float val;          //to store individual values

    while (s >> word) { //goes through each val in the input stream and puts into vals
        try {
            for (char const &c : word) {    //checks every char in each val is 0-9, '.', or '-'
                if (!(c=='.' || c=='-' || (c-'0'<10 && c-'0'>=0)))
                    throw exception();
            }
            val = stof(word);
        }
        catch (exception &e) {  //if bad char in val, set that val to BAD
            val = BAD;
        }
        if (abs(val) > 100.0)   //checks all data is in range -100 to 100
            val = BAD;
        vals.push_back(val);    //put val on list vals
    }

    float* data_ptr;
    data_ptr = new float[vals.size()];   //create an array from list vals (to allow access by index)
    int i = 0;
    for (float v: vals) {
        data_ptr[i++] = v;
    }

    int min;    //the minute input from user
    try {       //in case: input is invalid
        min = stoi(argv[2]);
    }
    catch (exception &e) {
        cout << "Wrong query input." << endl;
        return 0;
    }

    if (min<0 || min>vals.size()-1) {   //in case: input out of range
        cout << "Query minute out of range." << endl;
        return 0;
    }

    int minhigh = 1;    //count of consecutive minutes are <=  user input index
    int x;              //declared outside of loop for scope so it can be used in output
    for (x = min-1; x >= 0; x--) {  //loop backwards starting at min input
        if (data_ptr[x] == BAD) {   //BAD data exception
            minhigh = 0;
            break;
        }
        if (data_ptr[x] > data_ptr[min])    //break on first higher temperature
            break;
        minhigh++;
    }

    if (minhigh != 0)
        cout << "Data at minute " << min << " is a " << minhigh << " minute(s) high." << endl;
    else
        cout << "Data at minute " << x << " is corrupted." << endl;
    delete[] data_ptr;  //delete only explicit memory allocation
    return 0;
}
