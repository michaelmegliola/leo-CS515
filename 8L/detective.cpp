/* 
 * This is a sample driver that tests the performace of mysterySort1
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include "mysterysorts.h"
using namespace std;

int main(){
    vector<int> a;
    srand(time(0));
    
    cout << "original:" << endl;
    for( int i = 0; i < 500; i++ ){
        a.push_back(rand()%1000);
        cout << a[i] << " ";
    }
    cout << endl;
    
    clock_t start, finish;
    double elapsed;
    start = clock();
    
    //run sort without interruption
    mysterySort1(a);
    finish = clock();
   	elapsed = double(finish - start) * 1000000 / CLOCKS_PER_SEC;
    cout << "Total elapsed time: " << elapsed << " microseconds." << endl;
    
    
    //interrupt sort after time elapse 15 microseconds
    //mysterySort1(a, 15);
    
    // check current vector content
    cout << "current:" << endl;
    for( int i = 0; i < a.size(); i++ ){
        cout << a[i] << " ";
    }
    cout << endl;
    
	    
}
