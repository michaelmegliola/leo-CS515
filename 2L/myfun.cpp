#include <iostream>
#include <cstdlib>
using namespace std;

/*  Interprets an integer value in a byte string pointed to by str.
    Function discards any whitespace characters until first non-whitespace
    character is found. Then it takes as many characters as possible to
    form a valid integer number representation and converts them to integer value.
    The valid integer value consists of the following parts:
        (optional) plus or minus sign
        numeric digits
 
    Parameters
        str	 -	 pointer to the null-terminated char string to be interpreted 
    
    Return value: Integer value corresponding to the contents of str on success. 
        If the converted value falls out of range of corresponding return type, 
        the return value is undefined. 
        If no conversion can be performed, 0 is returned.
 
*/

int myatoi(const char * ptr){
    while (*ptr) {      //gobbles white space
        if (*ptr==' ')
            ptr++;
        else
            break;
    }

    int n = 0;      //the output number
    int m = 1;      //keeping track of sign (+,-)
    bool sign = false;  //makes sure to allow only one + or - before nums
    bool num = false;   //keeps track of first numeric char (so - after numbers is not counted)
    while (*ptr) {  //loops over remaining string
        char c = *ptr;
        if (c=='-' && !num) {   //handles - signs
            if (sign)
                return 0;
            m = -1;
            sign = true;
        }
        else if (c=='+') {      //handles + signs
            if (sign)
                return 0;
            m = 1;
            sign = true;
        }
        else if (c>='0' && c<='9') {    //handles numbers
            num = true;
            n *= 10;    //shift by one order of magnitude
            n += c-'0'; //int val of numeric char
        }
        else {
            break;
        }
        ptr++;  //next char
    }
    return n*m; //n is magnitude, m is sign (+,-)
}

// DO NOT ADD MAIN() FUNCTION IN THIS FILE