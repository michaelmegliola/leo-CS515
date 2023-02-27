/* CS515 Assignment 0
File: hello.cpp
Name: Leo Megliola
Section: 01R
Collaboration Declaration: 
          none
*/  

#include <iostream> // for cin and cout
#include <string> // for string type
using namespace std;

/**
 * prompts the user for a name and calls self on blank line recursively
 * upon non-blank input, it prints the entire line after a short statement
 */
void askName() {
    string name;
    cout << "What is your name?" << endl;
    getline(cin, name);

    if (name == "")
        askName();
    else {
        cout << "Hello World!" << endl;
        cout << "Welcome to CS515, " << name << "!" << endl;
    }
}

/**
 * main calls askName
 * @param argc argument count (none)
 * @param argv vector of arguments (none)
 * @return 0 upon success
 */
int main(int argc, char ** argv) {
    askName();
    return 0;
}
