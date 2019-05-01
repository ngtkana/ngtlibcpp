#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;
const vector<pair<char, string>> dct = {
    {'\t', "\\t"},
    {'\"', "\\\""},
    {'\\', "\\\\"},
};
int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  queue<string> snp;
  int cascade = 0;
  bool is_cascade_determined = false;
  while (true) {
    string s;
    getline(cin, s);
    if (s == "end") {
      break;
    }
    int sp_cnt = 0;
    queue<char> line;
    if (is_cascade_determined) {
      s = s.substr(cascade, s.size());
    }
    for (int i = 0; i < s.length(); i++) {
      if (!is_cascade_determined) {
        if (s[i] == ' ') {
          cascade++;
          continue;
        } else {
          is_cascade_determined = true;
        }
      }
      bool pushed = false;
      char crr = s[i];
      if (crr == ' ') {
        sp_cnt++;
        if (sp_cnt == 2) {
          line.push('\\');
          line.push('t');
          sp_cnt = 0;
        }
        pushed = true;
      } else {
        if (sp_cnt == 1) {
          line.push(' ');
          sp_cnt = 0;
        }
      }
      for (auto p : dct) {
        char key = p.first;
        string value = p.second;
        if (crr == key) {
          for (int i = 0; i < value.length(); i++) {
            line.push(value[i]);
          }
          pushed = true;
          break;
        }
      }
      if (!pushed) {
        line.push(s[i]);
      }
    }
    string t;
    while (!line.empty()) {
      t.push_back(line.front());
      line.pop();
    }
    snp.push(t);
  }
  while (!snp.empty()) {
    string s = snp.front();
    snp.pop();
    s = (string)"\"" + s + "\",";
    cout << s << '\n';
  }
  return 0;
}