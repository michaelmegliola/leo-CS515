
#ifndef _mysterysorts_h
#define _mysterysorts_h
#include <vector>
#include <iostream>
#include <ctime>
#include <unistd.h>
#include <sys/time.h>
using namespace std;

/* 
 * Each of these functions will sort a vector of integers into ascending order.
 * Each uses a different sorting algoritm, and therein lies the mystery!
 *
 * The optional second argument is a value that limits the sort to a given
 * amount of processing time. The maxMicroSec argument is expressed in micro seconds.
 * The function will return after that much time has elapsed (approximately), 
 * even if the sorting hasn't been finished. By choosing an appropriate stop, 
 * you can examine the data mid-sort, which allows you to look for patterns in 
 * how the data is being rearranged. The default argument sets maxMicroSec to -1,
 * which indicates the sort should be run to completion. 
 */


void mysterySort1(std::vector<int> &arr, double maxMicroSec = -1);
void mysterySort2(std::vector<int> &arr, double maxMicroSec = -1);
void mysterySort3(std::vector<int> &arr, double maxMicroSec = -1);
void mysterySort4(std::vector<int> &arr, double maxMicroSec = -1);
void mysterySort5(std::vector<int> &arr, double maxMicroSec = -1);

#endif
