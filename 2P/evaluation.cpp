// infix expression evaluation
// implemented with STL vector
// evalues expression with multiple digit numbers, * / + - and {} [] () paratheis
// assume the expression is well formatted with balanced braces. 

#include <iostream>
#include <stack>
#include <string>
using namespace std;

//----------------------------------------------------------------
// Generates a stack of string tokens representing postfix
// notation for the input line
void generateRPN(string line, stack<string> &postfix);
//----------------------------------------------------------------
// helper to preform simple repeated read of stack
void pop2(stack<int>& s, int* p1, int* p2);
//----------------------------------------------------------------
// Returns a the result of evaluating the passed postfix token
// stack as a decimal string
string evaluateRPN(stack<string> &postfix)
{
    stack<string> prefix;       //contains tokens in prefix order
    stack<int> rpnstack;        //contains partial results of operations in stack form

    while (!postfix.empty()) {  //reverses postfix --> prefix
        prefix.push(postfix.top());
        postfix.pop();
    }

    rpnstack.push(0);   //allows for unary operations (-5 becomes 0-5 implicitly)

    int a;
    int b;  //operands
    while (!prefix.empty()) {           //loops over all tokens in prefix order
        string token = prefix.top();
        prefix.pop();
        if (token == "+") {             //performs addition on top two operands on rpnstack
            pop2(rpnstack, &a, &b);
            rpnstack.push(a + b);
        }
        else if (token == "-") {        //performs subtraction...
            pop2(rpnstack, &a, &b);
            rpnstack.push(a - b);
        }
        else if (token == "*") {        //performs multiplication...
            pop2(rpnstack, &a, &b);
            rpnstack.push(a * b);
        }
        else if (token == "/") {        //performs division...
            pop2(rpnstack, &a, &b);
            rpnstack.push(a / b);
        }
        else
            rpnstack.push(stoi(token)); //pushes operand onto rpnstack (expected 2 elements min before operations)
    }

    return to_string(rpnstack.top());   //when all operations are complete, the answer will always be on top of rpnstack
}

void pop2(stack<int>& s, int* p1, int* p2)
{
    *p2 = s.top();
    s.pop();
    *p1 = s.top();
    s.pop();        //take top two operands and assign them to *p1 and *p2
}

//----------------------------------------------------------------
int main(int argc, char ** argv)
{
    string line;
    cout << "Expression: ";
    while ( getline(cin, line) )
    {
        if (line == "exit") //break on "exit"
            break;

        // skip empty line
        if (line.length() == 0)
            continue;

        stack<string> postfix;
        generateRPN(line, postfix);

        cout << "Answer: " << evaluateRPN(postfix) << endl;
        line.clear();
        cout << "Expression: ";
    }
    if (line != "exit") //add new line on ctrl-d
        cout << endl;
    return 0;
}
