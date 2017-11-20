#include "stackarr.h"
#include <iostream>
#include <string>

using namespace std;
bool bracketCheck(const string& s) {
     Stack<char>* stack = new Stack<char>();
     int quantity = 0;
     for (int i = 0; i < s.length(); i++) {
         if(s[i] == '(' || s[i] == '[' || s[i] == '{'){
            stack->push(s[i]);
            quantity++;
         }else if(s[i] == ')' || s[i] == ']' || s[i] == '}') {
            if((s[i] == ')' && stack->top() == '(') || (s[i] == ']' && stack->top() == '[') || (s[i] == '}' && stack->top() == '{') && quantity) { 
                stack->pop();
                quantity--;
            } else {
                return false; 
            }
        }
    }
    if(quantity) {
        return false;
    }
    return true;
}
int main() {
    cout << "()[]      " << (bracketCheck("()[]") ? "good" : "not good") << endl;
    cout << "[({}[])]  " << (bracketCheck("[({}[])]") ? "good" :  "not good") << endl;
    cout << "()]       " << (bracketCheck("()]") ? "good" : "not good") << endl;
    cout << "[[]       " << (bracketCheck("[[]") ? "good" : "not good") << endl;
    cout << "({)}      " << (bracketCheck("({)}") ? "good" : "not good") << endl;
    cout << "([abc])ba " << (bracketCheck("([abc])ba") ? "good" : "not good") << endl;
}