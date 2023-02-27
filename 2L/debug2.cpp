#include <iostream>
#include <cstdlib>
using namespace std;

int* initArray(int);
int fillArray(int *, int);
int* doubleArray(int);
void displayArray(int *, int);

/* 
 * The program will create an array of given size
 * populate the array with random number from (0-99)
 * and display the array. Next, the program will double
 * the size of the array, repopulate the array and 
 * display it again.
 */


int main(int argc, char ** argv){
    if (argc != 2){
        cout << "wrong number of arguments" << endl;
        exit(1);
    }
    
    int n = atoi(argv[1]); // get size
    srand(time(0));
    
    // create initial array and display it
    int* ptr = initArray(n);
    fillArray(ptr, n);
    displayArray(ptr, n);
    delete [] ptr;
    
    // create the double sized array and display it
    int* ptr2 = doubleArray(n);
    fillArray(ptr2, 2*n);
    displayArray(ptr2, 2*n);
    delete [] ptr2;
}

// Create an array of size n and return its address
int* initArray(int n){
    int *ptr = new int[n];
    return ptr;
}

// Fill array ptr with n random numbers
int fillArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        ptr[i] = rand() % 100;
    }
    return 0;
}

// Double the size of the array, make sure no memory leak
int* doubleArray(int n){
    int *ptr = new int[n*2];
    return ptr;
}

// Display n array elements
void displayArray(int *ptr, int n){
    for(int i=0; i<n; i++){
        cout << ptr[i] << " ";
    }
    cout << endl;
}