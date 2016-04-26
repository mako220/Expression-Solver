#include <iostream>
#include <sstream>
#include <stack>
#include <limits>
#include <string>
#include <math.h>
#include <cstdlib>
using namespace std;

int priority(string a) {
    int temp;
    if (a == "^")
        temp = 1;
    else  if (a == "*" || a == "/")
        temp = 2;
    else  if (a == "+" || a == "-")
        temp = 3;
    return temp;
}

string operations(string op1, string op2,string opnd)
{
    int a,b;
    char c;
    string result;

    istringstream (op1) >> a;
    istringstream (op2) >> b;
    istringstream (opnd) >> c;

    cout << a << " " << b << " " << c << endl;

    switch (c)
    {
    case '+':
        a = (a + b);
        break;
    case '-':
        a = (b - a);
        break;
    case '/':
        a = (b / a);
        break;
    case '*':
        a = (a * b);
        break;
    case '^':
        a = (pow(b,a));
        break;
    }


    stringstream ss;
    ss << a;
    result = ss.str();
    return result;
}

int main()
{
    string infix,token;
    cout << "Enter an arithmetic expression: " << endl;
    getline(cin, infix);
    string a,b,c;
    stack<string> operator_stack;
    stack<string> operand_stack;

    istringstream iss(infix);


    while(getline(iss,token,' '))
    {
        if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^")
        {
            while (!operator_stack.empty() && (priority(operator_stack.top()) <= priority(token)))
            {
                a = operand_stack.top();
                operand_stack.pop();
                b = operand_stack.top();
                operand_stack.pop();
                c = operator_stack.top();
                operator_stack.pop();
                operand_stack.push(operations(a,b,c));
            }
            operator_stack.push(token);
        }
        else if (token == "(")
        {
            operator_stack.push(token);
        }
        else if (token == ")")
        {
            while (operator_stack.top() != "(")
            {
                a = operand_stack.top();
                operand_stack.pop();
                b = operand_stack.top();
                operand_stack.pop();
                c = operator_stack.top();
                operator_stack.pop();
                operand_stack.push(operations(a,b,c));
            }
            operator_stack.pop();
        }
        else
        {
            operand_stack.push(token);
        }

    }

    while (!operator_stack.empty())
    {
        a = operand_stack.top();
        operand_stack.pop();
        b = operand_stack.top();
        operand_stack.pop();
        c = operator_stack.top();
        operator_stack.pop();
        operand_stack.push(operations(a,b,c));
    }

    cout << "\n \n";
    cout << "Evaluated result is : " << operand_stack.top() << endl;
    //system ("g++ --version");
    //system("pause");
    return 0;
}
