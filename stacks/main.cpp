#include <iostream>
#include "Stack.h"
#include "Stack.cpp"

#include <vector>

template<typename T>
void reverse_vec(std::vector<T>& v);
bool check_balance(const std::string& s);

int main() {

  std::string s = "{a{b}{c}string[]}";

  std::cout << "is " << s << " balanced? " << (check_balance(s) ? "Yes" : "No") << std::endl;




  return 0;
};

template<typename T>
void reverse_vec(std::vector<T>& v) {
  StackList::Stack<T> st;
  // push all elements to stack
  for (int i = 0; i < v.size(); i++) {
    st.push(v[i]);
  }
  // pop all elements back to vector, vector will now be reversed
  for (int i = 0; i < v.size(); i++) {
    v[i] = st.top();
    st.pop();
  }
}

bool check_balance(const std::string& s) {
  // if(s.empty()) return false; // if empty string return false
  StackList::Stack<char> st;
  for (char c : s) {
    if (c == '(' || c == '{' || c == '[') {
      // push into stack if opening delimiter
      st.push(c);
    }
    else if(c == ')' || c == ']' || c == '}'){
      char ch;
      // get the top element of stack, will return false if empty
      try {
        ch = st.top();
        st.pop();
      }
      catch (std::string ex) {
        return false;
      }
      
      // check for matching opening delimiter if c is closing delimiter
      switch (c)
      {
      case ')':
        if (ch == '(') continue;
        else return false;
      case '}':
        if (ch == '{') continue;
        else return false;
      case ']':
        if (ch == '[') continue;
        else return false;
      default:
        return false;
      }
    }
  }
  return st.empty();
}


