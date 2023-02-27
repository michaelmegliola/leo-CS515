#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <ios>
#include <algorithm>
using namespace std;

int median(int size, int* vals) {   //returns the median of vals (reorders vals)
    sort(vals, vals+size);

    if (size % 2 == 0)
        return ((vals[size/2] + vals[(size/2) - 1]) / 2);
    else
        return vals[size/2];
}

int main(int argc, char** argv) {
    int depth = argc - 2;           //number of .pgm files
    int*** pixels;                  //3d array represent stacked image files
    bool first_file = true;         //flag
    int width, height, grayscale;

    for (int d = 0; d < depth; d++) {   //read files
        stringstream pgm;
        ifstream infile;
        infile.open(argv[d+1]);
        if (infile.fail()) {            //handles file open error
            cout << "file error" << endl;
            return 0;
        }

        pgm << infile.rdbuf();
        infile.close();

        string word;
        pgm >> word;    //discard letter-containing element (2P)

        if (first_file) {                       //first file makes sure we only read the header once
            pgm >> word; width = stoi(word);    //assumes all files are the same dimensions
            pgm >> word; height = stoi(word);
            pgm >> word; grayscale = stoi(word);

            pixels = new int **[height];    //allocate 3d array
            for (int h = 0; h < height; h++) {
                pixels[h] = new int*[width];
                for (int w = 0; w < width; w++) {
                    pixels[h][w] = new int[depth];
                }
            }

            first_file = false; //remove flag
        }
        else    //if not first file: discard the entire header
            for (int i = 0; i < 3; i++)
                pgm >> word;

        for (int row = 0; row < height; row++) {    //read the file into 3d array
            for (int col = 0; col < width; col++) {
                pgm >> word;
                pixels[row][col][d] = stoi(word);
            }
        }
    }

    ofstream myfile;    //write file using median values
    myfile.open(argv[argc-1], (ios::out | ios::trunc));
    myfile << "P2" << endl << width << " " << height << endl << grayscale << endl;

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            myfile << median(depth, pixels[row][col]) << " ";
        }
        myfile << endl;
    }
    myfile.close();

    for (int h = 0; h < height; h++) {  //deallocate array
        for (int w = 0; w < width; w++) {
            delete[] pixels[h][w];
        }
        delete[] pixels[h];
    }
    delete[] pixels;

    return 0;
}
