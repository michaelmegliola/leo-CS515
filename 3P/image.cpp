#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <list>
#include <ios>
using namespace std;

/**
 * represents a .pgm file with three member ints and a 2d int[]
 */
class Image {

  public:
    int width, height, grayscale;
    int** pixels;

    Image(char* fname) {        //constructor takes .pgm file name
        stringstream pgm;       //read file
        ifstream infile;
        infile.open(fname);
        if (infile.fail()) {    //handles file open error
            throw invalid_argument(fname);
        }

        pgm << infile.rdbuf();
        infile.close();

        string word;
        pgm >> word;    //discard letter-containing element (2P)
        pgm >> word; width = stoi(word);    //read header separately from pixel values
        pgm >> word; height = stoi(word);
        pgm >> word; grayscale = stoi(word);

        pixels = new int*[height];          //allocate pixel array
        for (int i = 0; i < height; i++)
            pixels[i] = new int[width];

        for (int row = 0; row < height; row++) {    //read pixels into array
            for (int col = 0; col < width; col++) {
                pgm >> word;
                pixels[row][col] = stoi(word);
            }
        }
    }

    ~Image() {
        for (int i = 0; i < height; i++)    //deallocate pixel array
            delete[] pixels[i];
        delete[] pixels;
    }

    void write_negative(char* fname) {  //writes the 'negative' image into .pgm file
        ofstream myfile;
        myfile.open(fname, (ios::out | ios::trunc));
        myfile << "P2" << endl << width << " " << height << endl << grayscale << endl;

        for (int row = 0; row < height; row++) {
            for (int col = 0; col < width; col++) {
                myfile << grayscale - pixels[row][col] << " ";
            }
            myfile << endl;
        }
        myfile.close();
    }

    void write_rotate(char* fname) {    //write rotated image into .pgm file
        ofstream myfile;
        myfile.open(fname, (ios::out | ios::trunc));
        myfile << "P2" << endl << height << " " << width << endl << grayscale << endl;

        for (int col = 0; col < width; col++) {
            for (int row = height-1; row >= 0; row--) {
                myfile << pixels[row][col] << " ";
            }
            myfile << endl;
        }
        myfile.close();
    }
};


int main(int argc, char** argv) {
    if (argc != 4) {    //handles incorrect argument count
        cout << "Usage: ./image <input image> <neg image> <rotate image>" << endl;
        return 0;
    }

    Image *img = nullptr;
    try {
        img = new Image(argv[1]);   //construct image from file
    }
    catch (invalid_argument e) {    //catch file error
        cout << "Can not open " << argv[1] << " for input." << endl;
    }

    if (img != nullptr) {           //write outputs
        img->write_negative(argv[2]);
        img->write_rotate(argv[3]);
        delete img;
    }
    return 0;
}
