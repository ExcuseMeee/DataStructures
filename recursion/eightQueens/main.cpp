#include <iostream>

void permutations(std::string& s, const int n, int i);
bool has_char(const std::string& s, const char c, int n);
void combinations(std::string& s, const int n, int i);


int main() {

  // std::string s(3, '0');
  std::string s = "01234";
  combinations(s, s.length(), 0);

  return 0;
}

bool has_char(const std::string& s, const char c, int n) {
  for (int i = 0; i < n; i++) {
    if (s[i] == c) {
      return true;
    }
  }
  return false;
}

void permutations(std::string& s, const int n, int i) {
  if (i == n) {
    std::cout << s << std::endl;
    return;
  }

  while (s[i] <= 'D') {
    permutations(s, n, i + 1);
    s[i]++;
  }

  s[i] = 'A';
}

// todo: every unique non-repeating combination of string of length 5 from '0' to 'Z' 
// ex: very first combination of length 5 is 01234
void combinations(std::string& s, const int n, int i) {


  if (i == n) {
    // bandaid fix... very inefficient makes my laptop mad
    // for (int i = 0; i < s.length(); i++) {
    //   char c = s[i];
    //   std::string chk = s;
    //   chk.erase(i, 1);
    //   if (has_char(chk, c, chk.length())) {
    //     return;
    //   }

    // }
    std::cout << s << std::endl;
    return;
  }


  while (s[i] <= 'Z') {

    // why does this work?
    if (!has_char(s, s[i], i)) {
      combinations(s, n, i + 1);
    }
    char proposed = s[i] == '9' ? 'A' : s[i] + 1;

    s[i] = proposed;
  }
  s[i] = '0';
}