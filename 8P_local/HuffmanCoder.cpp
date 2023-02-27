#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "HuffTree.h"

using namespace std;

/**
 * CS515 Assignment 8
 * File: HuffmanCoder.cpp
 * Name: Leo Megliola
 * Section: L2R
 * Date: Apr 8, 2021
 * Collaboration Declaration: none
 *  Assistance received from online resources
 *      Geeks for Geeks, C++ documents
 */
int main(int argc, char ** argv) {

    stringstream s;                             //open the input file
    ifstream infile;
    infile.open(argv[1]);
    if (infile.fail()) {
        cout << "Error opening file" << endl;
        return 0;
    }

    s << infile.rdbuf();                        //read entire input file
    infile.close();

    int freq[26];                               //allocate array for character frequencies
    for (int i = 0; i < 26; i++)
        freq[i] = 0;

    int bits = -8;                              //accounts for null character at end of file
    while (!s.eof()) {
        bits += 8;                              //each character is 8 bits
         int n = s.get();
         if (n >= 'A' && n <= 'Z') {  //upper case letters
             freq[n-'A']++;
         }
        if (n >= 'a' && n <= 'z') {  //lower case letters
            freq[n-'a']++;
        }
    }

    char c[26];                      //array of entire alphabet for encoder
    for (char i = 0; i < 26; i++)
        c[i] = i+97;

    HuffTree h;
    h.buildTree(c, freq,26);    //build tree for entire alphabet

    s.clear();

    stringstream t;                 //re-read file to encode each character
    ifstream infile_t;
    infile_t.open(argv[1]);
    t << infile_t.rdbuf();
    infile.close();

    int huffbits = -8;
    while (!t.eof()) {
        char c = t.get();
        if (c >= 'A' && c <= 'Z')    //to encode an uppercase letter, change it to lower case
            c += 'a'-'A';
        if (c >='a' && c <= 'z') {
            string s = h.getCode(c);
            huffbits += s.length();  //the length of output would be the length of the resulting string
        } else
            huffbits += 8;           //cannot compress this character
    }

    cout << "original bits: " << bits << endl;
    cout << "bits after compression: " << huffbits << endl;
    double ratio = 100.0 * ((double) (bits-huffbits) / (double) bits);
    cout << "compression rate: " << setprecision(4) << ratio << "%" << endl;
    t.clear();
    return 0;           //only returns after while(true) broken
}
