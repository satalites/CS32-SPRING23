//eval.cpp
//caitlin 605943983

#include <iostream>
#include <cassert>
#include <string>
#include <stack>
using namespace std;

bool validInfix(string infix);
string makePostfix(string infix, string &postfix);
int precedence(char o);

int evaluate(string infix, string& postfix, bool& result)
{
    // Evaluates a boolean expression:
    //   If infix is a syntactically valid infix boolean expression,
    //   then set postfix to the postfix form of that expression, set
    //   result to the value of the expression, and return zero. If
    //   infix is not a syntactically valid expression, return 1; in
    //   that case, postfix may or may not be changed, but result must
    //   be unchanged.
    if(!validInfix(infix))
    {
        return 1;
    }
    
    stack<bool> resultBools;
    makePostfix(infix, postfix);
    if(postfix.empty())
    {
        return 1;
    }
    for(int i = 0; i < postfix.size(); i++)
    {
        if(postfix.at(i) == 'T')
        {
            resultBools.push(true);
        }
        else if(postfix.at(i) == 'F')
        {
            resultBools.push(false);
        }
        else if(postfix.at(i) == '!')
        {
            bool placehold = resultBools.top();
            resultBools.pop();
            resultBools.push(!placehold);
        }
        else
        {
            //cout << resultBools.top();
            bool placehold1 = resultBools.top();
            resultBools.pop();
//            if(resultBools.empty())
//            {
//                return 1;
//            } //why is it empty
            //cout << resultBools.top();
            bool placehold2 = resultBools.top();
            resultBools.pop();
            if(postfix.at(i) == '^')
            {
                if(((placehold1 == false) && (placehold2 == false)) ||  ((placehold1 == true) && (placehold2 == true)))
                {
                    resultBools.push(false);
                }
                else
                {
                    resultBools.push(true);
                }
            }
            if(postfix.at(i) == '&')
            {
                if(((placehold1 == true) && (placehold2 == true)))
                {
                    resultBools.push(true);
                }
                else
                {
                    resultBools.push(false);
                }
            }
        }
    }
    result = resultBools.top();
    return 0;
}

bool validInfix(string infix)
{
    if(infix == "")
    {
        return false;
    }
    //create a placeholder infix string
    string placeholder;
    //fill with everything that isn't a space
    for(int i = 0; i < infix.size(); i++)
    {
        if(infix.at(i) != ' ')
        {
            placeholder += infix.at(i);
        }
    }
    //count closed and open parantheses
    int openPara = 0;
    int closedPara = 0;
    //now go through placeholder and make sure it's valid with a whole bunch of switch cases
    for(int j = 0; j < placeholder.size(); j++)
    {
        switch(placeholder.at(j))
        {
            case 'F':
                if(j > 0) //make sure we are not out of bounds when we check the one behind the value
                {
                    if(placeholder.at(j-1) == 'F') //F and F can't be next to each other
                        return false;
                    if(placeholder.at(j-1) == 'T') //F and T can't be next to each other
                        return false;
                    if(placeholder.at(j-1) == ')') //it should be (
                        return false;
                }
                if(j < placeholder.size()-1) //making sure not out of bounds
                {
                    if(placeholder.at(j+1) == 'T') //F and T can't be next to each other
                        return false;
                    if(placeholder.at(j+1) == 'F') //F and F can't be next to each other
                        return false;
                    if(placeholder.at(j+1) == '(') //j+1 is last item, meaning there's not room for another closed parentheses
                        return false;
                }
                break;
            case 'T':
                if(j > 0) //make sure we are not out of bounds when we check the one behind the value
                {
                    if(placeholder.at(j-1) == 'F') //F and F can't be next to each other
                        return false;
                    if(placeholder.at(j-1) == 'T') //F and T can't be next to each other
                        return false;
                    if(placeholder.at(j-1) == ')') //it should be (
                        return false;
                }
                if(j < placeholder.size()-1) //making sure not out of bounds
                {
                    if(placeholder.at(j+1) == 'T') //F and T can't be next to each other
                        return false;
                    if(placeholder.at(j+1) == 'F') //F and F can't be next to each other
                        return false;
                    if(placeholder.at(j+1) == '(') //j+1 is last item, meaning there's not room for another closed parentheses
                        return false;
                }
                break;
            case '(':
                if(j > 0)
                {
                    if(placeholder.at(j-1) == 'F') //needs operator ?
                        return false;
                    if(placeholder.at(j-1) == 'T') //needs operator ?
                        return false;
                    if(placeholder.at(j-1) == ')') //needs operator ?
                        return false;
                }
                if(j < placeholder.size()-1) //making sure not out of bounds
                {
                    if(placeholder.at(j+1) == '&') //& has to have T/F before and after
                        return false;
                    if(placeholder.at(j+1) == '^') //^ has to have T/F before and after
                        return false;
                    if(placeholder.at(j+1) == ')') //you can't have ()
                        return false;
                }
                if(j == placeholder.size()-1) //if open parenthese is last item, it won't be closed
                {
                    return false;
                }
                openPara++; //increase open count
                break;
            case ')':
                if(j == 0) //what are you closing if parenthese is first item????
                {
                    return false;
                }
                if(j > 0)
                {
                    if(placeholder.at(j-1) == '&') //needs T/F before closed para
                        return false;
                    if(placeholder.at(j-1) == '(') //can't have ()
                        return false;
                    if(placeholder.at(j-1) == '!') //then ! will be applying to nothing
                        return false;
                    if(placeholder.at(j-1) == '^') //then ^ will be applying to nothing
                        return false;
                }
                if(j < placeholder.size()-1) //making sure not out of bounds
                {
                    if(placeholder.at(j+1) == '(') //then there's no comparison
                        return false;
                    if(placeholder.at(j+1) == 'F')
                        return false;
                    if(placeholder.at(j+1) == 'F')
                        return false;
                    if(placeholder.at(j+1) == '!')
                        return false;
                }
                closedPara++; //increase closed count
                if(closedPara > openPara)
                    return false;
                break;
            case '!':
                if(j > 0) //we are checking within bounds
                {
                    if(placeholder.at(j-1) == 'T') //T can't come before !
                        return false;
                }
                if(j < placeholder.size()-1) //checking within bounds
                {
                    if(placeholder.at(j+1) == '&') //can't have another operator after it
                        return false;
                    if(placeholder.at(j+1) == '^') //can't have another operator after it
                        return false;
                    if(placeholder.at(j+1) == ')') // there has to be a T or F behind it
                        return false;
                }
                if(j == placeholder.size()-1) //if we are at the last item
                    return false; //there's nothing after the !
                break;
            case '&':
                if(j == 0) //can't be the first in the string
                    return false;
                if(j > 0) //within bounds to check item before current item
                {
                    if(placeholder.at(j-1) == '!') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '&') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '^') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '(') //needs a T or F before it
                        return false;
                }
                if(j < placeholder.size()-1)
                {
                    if(placeholder.at(j+1) == '&') //operator can't come before it
                        return false;
                    if(placeholder.at(j+1) == '^') //operator can't come before it
                        return false;
                    if(placeholder.at(j+1) == ')') //cant close parentheses without T or F after &
                        return false;
                }
                if(j == placeholder.size()-1) //can't be last in string
                    return false;
                break;
            case '^':
                if(j == 0) //can't be first in string
                    return false;
                if(j > 0) //within bounds
                {
                    if(placeholder.at(j-1) == '!') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '&') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '^') //operator can't come before it
                        return false;
                    if(placeholder.at(j-1) == '(') //needs a T or F before it
                        return false;
                }
                if(j < placeholder.size()-1) //within bounds
                {
                    if(placeholder.at(j+1) == '&') //operator can't come before it
                        return false;
                    if(placeholder.at(j+1) == '^') //operator can't come before it
                        return false;
                    if(placeholder.at(j+1) == ')') //cant close parentheses without T or F after ^
                        return false;
                }
                if(j == placeholder.size()-1)
                    return false;
                break;
            default:
                return false;
        }
    }
    if(openPara != closedPara)
        return false;
    return true;
}

string makePostfix(string infix, string &postfix)
{
//    Initialize postfix to empty
    postfix = "";
//    Initialize the operator stack to empty
    stack <char> ops;
//    For each character ch in the infix string
    char c;
    for(int i = 0; i < infix.size(); i++)
    {
        c = infix.at(i);
//        Switch (ch)
        switch (c)
        {
            case 'T': //case operand
            case 'F':
                postfix += c; //append c to end of postfix
                break;
            case '(': //case
                ops.push(c); //push
                break;
            case ')':
                while(ops.top() != '(')
                {
                    postfix += ops.top();
                    ops.pop();
                }
                ops.pop();
                break;
            case '!':
            case '&':
            case '^':
                while((!ops.empty()) && (ops.top() != '(') && (precedence(c) <= precedence(ops.top())))
                {
                    if(c == '!')
                    {
                        break;
                    }
                    postfix += ops.top();
                    ops.pop();
                }
                ops.push(c);
                break;
            default:
                break;
        }
    }
    while(!ops.empty())
    {
        postfix += ops.top();
        ops.pop();
    }
    return postfix;
}

int precedence(char op)
{
    switch(op)
    {
        case '!':
            return 3;
        case '&':
            return 2;
        case '^':
            return 1;
        default:
            return -1;
    }
}

int main()
{
    string pf;
    bool answer;
    assert(validInfix("T"));
    assert(validInfix("(!(T))"));
    assert(validInfix("!(((T&F)))"));
    assert(validInfix("!T"));
    assert(validInfix("F"));
    assert(validInfix("!(T&!F) ^!T& !F"));
    assert(validInfix("!!!!T"));
    assert(validInfix("!!T"));
    assert(validInfix("!!!!!T"));
    assert(validInfix("!!(T) & !F ^ T"));
    assert(validInfix("!!!!T"));
    assert(validInfix("T & !!F"));
    assert(validInfix("!( T & !F ^ T)"));
    assert(validInfix("!!( T & !F ^ T)"));
    assert(validInfix("!!!( T & !F ^ T)"));
    assert(validInfix("!!(T) & !F ^ T"));
    assert(validInfix("T^ F"));
    
    assert(makePostfix("T", pf) == "T");
    assert(makePostfix("(!(T))", pf) == "T!");
    assert(makePostfix("!(((T&F)))", pf) == "TF&!");
    assert(makePostfix("!T", pf) == "T!");
    assert(makePostfix("F", pf) == "F");
    assert(makePostfix("!(T&!F) ^!T& !F", pf) == "TF!&!T!F!&^");
    assert(makePostfix("!!!!T", pf) == "T!!!!");
    assert(makePostfix("!!T", pf) == "T!!");
    assert(makePostfix("!!!!T", pf) == "T!!!!");
    assert(makePostfix("T & !!F", pf) == "TF!!&");
    assert(makePostfix("!( T & !F ^ T)", pf) == "TF!&T^!");
    assert(makePostfix("!!( T & !F ^ T)", pf) == "TF!&T^!!");
    assert(makePostfix("!!!( T & !F ^ T)", pf) == "TF!&T^!!!");
    assert(makePostfix("!!(T) & !F ^ T", pf) == "T!!F!&T^");
    
    assert(evaluate("T^ F", pf, answer) == 0  &&  pf == "TF^"  &&  answer);
    assert(evaluate("T^", pf, answer) == 1); //nothing for true to be compared with
    assert(evaluate("F F", pf, answer) == 1); //can't be next to each other
    assert(evaluate("TF", pf, answer) == 1); //can't be next to each other
    assert(evaluate("()", pf, answer) == 1); //parentheses with nothing inside
    assert(evaluate("()T", pf, answer) == 1); //parentheses with nothing inside
    assert(evaluate("T(F^T)", pf, answer) == 1); //no operator between
    assert(evaluate("T(&T)", pf, answer) == 1); //
    assert(evaluate("(T&(F^F)", pf, answer) == 1); //inequal parentheses
    assert(evaluate("T|F", pf, answer) == 1); // | is not valid
    assert(evaluate("", pf, answer) == 1); //empty
    assert(evaluate("F  ^  !F & (T&F) ", pf, answer) == 0 &&  pf == "FF!TF&&^"  &&  !answer);
    assert(evaluate(" F  ", pf, answer) == 0 &&  pf == "F"  &&  !answer);
    assert(evaluate("((T))", pf, answer) == 0 &&  pf == "T"  &&  answer);
        
    cout << "Passed all tests" << endl;
}
