#include <bits/stdc++.h>
using namespace std;
// begin
void dfs (
  int crr
, int prt
, vector<vector<int>>& grh
) {
  for (int nxt : grh[crr]) if (nxt != prt) {
    dfs(nxt, crr, grh);
  }
}
// end
