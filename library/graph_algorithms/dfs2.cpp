#include <bits/stdc++.h>
using namespace std;
// begin
void dfs (
  int crr
, vector<int>& ckd
, vector<vector<int>>& grh
) {
  ckd[crr] = true;
  for (int nxt : grh[crr]) if (!ckd[nxt]) {
    dfs(nxt, ckd, grh);
  }
}
// end
