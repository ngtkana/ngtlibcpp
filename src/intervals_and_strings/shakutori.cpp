#include <bits/stdc++.h>
using namespace std;
// begin
int l(0), r(0);
for (; l < ${1:n}; l++) {
  while (r < n && ${2:/*[l, r + 1)が妥当*/}) {
    r++;
    ${3:/*[l, r + 1)を訪問*/};
  }
}
// end
